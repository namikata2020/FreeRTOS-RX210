/*
 * serial.c
 */

/*
 * intprg.c　のSCI1関連の割り込みをコメントアウトすること
 * // SCI1 ERI0
 * //void Excep_SCI1_ERI1(void){ }
 *
 * // SCI1 RXI0
 * //void Excep_SCI1_RXI1(void){ }
 *
 * // SCI1 TXI0
 * //void Excep_SCI1_TXI1(void){ }
 *
 * // SCI1 TEI0
 * //void Excep_SCI1_TEI1(void){ }
 *
 */
/*
 * 割込み優先度を最大に設定してある。
 * これにより、ここ割込みルーチンはFreeRTOSの影響を受けない。
 *
 * FreeRTOSのシステムコールを行うと暴走する。
 */
#include "iodefine.h"
#include <stdio.h>
#include <machine.h>
#include "vect.h"
#include "../FreeRTOS/FreeRTOS.h"

/* printf(),scanf()でシリアル入出力を使用するためのコード */
#ifdef USE_SERIAL_CONSOLE

#define TX_ACTIVE   1	//送信動作中
#define TX_INACTIVE 0	//送信停止中

#define TX_RING_BUFF_SIZE	64	//リングバッファのサイズ
#define RX_RING_BUFF_SIZE	64	//リングバッファのサイズ

//リングバッファ
unsigned char rx_buff[RX_RING_BUFF_SIZE];	//受信用
unsigned char tx_buff[TX_RING_BUFF_SIZE];	//送信用

//データポインタ
volatile int ptr_rx_top,ptr_rx_bottom;
volatile int ptr_tx_top,ptr_tx_bottom;
//送信フラグ データ送信中かどうか
volatile int tx_flag = TX_INACTIVE;

#if USE_SCI_PORT==0
/*
 *  SCI0初期化
 *  baudrate bps: 8bit: stop bit 1: Parity none
 *  PCLK 25MHz
 */
void SCI_Init (int baudrate)
{

    /* ---- SCI interrupt request is disabled ---- */
	IR(SCI0,ERI0) = 0;
	IR(SCI0,RXI0) = 0;
	IR(SCI0,TXI0) = 0;
	IR(SCI0,TEI0) = 0;

    /* ---- Initialization of SCI ---- */

    /* PRCR - Protect Register
    b15:b8 PRKEY    - PRC Key Code  - A5h (The write value should be A5h to permission writing PRCi bit)
    b7:b4  Reserved - The write value should be 0.
    b1     PRC1     - Protect Bit 1 - Write enabled */
    SYSTEM.PRCR.WORD = 0xA502;

    /* The module stop state of SCIn is canceled */
    MSTP(SCI0) = 0;

    /* Enable write protection */
    SYSTEM.PRCR.WORD = 0xA500;

    /* SCR - Serial Control Register
    b7     TIE  - Transmit Interrupt Enable     - A TXI interrupt request is disabled
    b6     RIE  - Receive Interrupt Enable      - RXI and ERI interrupt requests are disabled
    b5     TE   - Transmit Enable               - Serial transmission is disabled
    b4     RE   - Receive Enable                - Serial reception is disabled
    b2     TEIE - Transmit End Interrupt Enable - A TEI interrupt request is disabled */
    SCI0.SCR.BYTE = 0x00;

    while (0x00 != (SCI0.SCR.BYTE & 0xF0))
    {
        /* Confirm that bit is actually 0 */
    }

    /* ---- Set the I/O port functions ---- */

    /* Set port output data - High level */
    PORT2.PODR.BIT.B0 = 1;

    /* Set port direction - TXDn is output port, RXDn is input port */
    PORT2.PDR.BIT.B0 = 1;
    PORT2.PDR.BIT.B1 = 0;

    /* Set port mode - Use pin as general I/O port */
    PORT2.PMR.BIT.B1 = 0;
    PORT2.PMR.BIT.B0 = 0;

    /* PWPR - Write-Protect Register
    b7     B0WI     - PFSWE Bit Write Disable   - Writing to the PFSWE bit is enabled
    b6     PFSWE    - PFS Register Write Enable - Writing to the PFS register is enabled
    b5:b0  Reserved - These bits are read as 0. The write value should be 0. */
    MPC.PWPR.BIT.B0WI  = 0;
    MPC.PWPR.BIT.PFSWE = 1;

    /* PFS - Pin Function Control Register
    b3:b0  PSEL - Pin Function Select - RXDn, TXDn */
    MPC.P20PFS.BYTE = 0x0A;
    MPC.P21PFS.BYTE = 0x0A;

    /* Enable write protection */
    MPC.PWPR.BIT.PFSWE = 0;
    MPC.PWPR.BIT.B0WI  = 1;

    /* Use pin as I/O port for peripheral functions */
    PORT2.PMR.BIT.B1 = 1;
    PORT2.PMR.BIT.B0 = 1;

    /* ---- Initialization of SCI ---- */

    /* Select an On-chip baud rate generator to the clock source */
    SCI0.SCR.BIT.CKE = 0;

    /* SMR - Serial Mode Register
    b7     CM   - Communications Mode   - Asynchronous mode
    b6     CHR  - Character Length      - Selects 8 bits as the data length
    b5     PE   - Parity Enable         - When transmitting : Parity bit addition is not performed
                                          When receiving    : Parity bit checking is not performed
    b3     STOP - Stop Bit Length       - 1 stop bits
    b2     MP   - Multi-Processor Mode  - Multi-processor communications function is disabled
    b1:b0  CKS  - Clock Select          - PCLK clock (n = 0) */
    SCI0.SMR.BYTE = 0x00;

    /* SCMR - Smart Card Mode Register
    b6:b4  Reserved - The write value should be 1.
    b3     SDIR     - Transmitted/Received Data Transfer Direction - Transfer with LSB-first
    b2     SINV     - Transmitted/Received Data Invert  - TDR contents are transmitted as they are.
                                                          Receive data is stored as it is in RDR.
    b1     Reserved - The write value should be 1.
    b0     SMIF     - Smart Card Interface Mode Select  - Serial communications interface mode */
    SCI0.SCMR.BYTE = 0xF2;

    /* SEMR - Serial Extended Mode Register
    b7:b6  Reserved - The write value should be 0.
    b5     NFEN     - Digital Noise Filter Function Enable  - Noise cancellation function
                                                              for the RXDn input signal is disabled.
    b4     ABCS     - Asynchronous Mode Base Clock Select   - Selects 16 base clock cycles for 1-bit period
    b3:b1  Reserved - The write value should be 0. */
    SCI0.SEMR.BYTE = 0x00;

    /* BRR - Bit Rate Register
    Bit Rate: (25MHz/(64*2^(-1)*57600bps))-1=12.56 */
    //SCI0.BRR = 13;	/* 57600bps */
    //SCI0.BRR = 40;	/* 19200bps */
    SCI0.BRR = configPERIPHERAL_CLOCK_HZ / 32UL / (unsigned long)baudrate - 1;

    /* ---- Initialization of SCI interrupt ---- */

    /* SCI interrupt priority level is 15 */
    IPR(SCI0, ) = 15;

    /* Interrupt request is cleared (Edge interrupt) */
    IR(SCI0,RXI0) = 0;
    IR(SCI0,TXI0) = 0;

    /* 割り込みの許可 */
	IEN(SCI0, RXI0) = 1;
	IEN(SCI0, ERI0) = 1;
	IEN(SCI0, TXI0) = 1;
	IEN(SCI0, TEI0) = 1;

	/* リングバッファの初期化 */
	ptr_rx_top = ptr_rx_bottom = 0;
	ptr_tx_top = ptr_tx_bottom = 0;

	/* 送受信許可 */
    SCI0.SCR.BIT.RIE = 1;	//受信割込み
    SCI0.SCR.BIT.TIE = 1;	//送信割込み
    SCI0.SCR.BIT.RE = 1;	//受信動作開始
    SCI0.SCR.BIT.TE = 0;

}

/*
 * 受信エラー割り込み
 */
/* SSR - Serial Status Register
b7:b6  Reserved - The read value is undefined. The write value should be 1.
b5     ORER     - Overrun Error Flag    - An overrun error has occurred
b4     FER      - Framing Error Flag    - A framing error has occurred
b3     PER      - Parity Error Flag     - A parity error has occurred */
#define SSR_ERROR_FLAGS     (0x38)
void  Excep_SCI0_ERI0(void)
{
	volatile char c;

	c = SCI0.RDR;	//ダミーリード
	SCI0.SSR.BYTE = (SCI0.SSR.BYTE & ~SSR_ERROR_FLAGS) | 0xC0;	//エラーフラグクリア
}

/*
 * 受信バッファフル割込み
 */
void  Excep_SCI0_RXI0(void)
{

	/* Read data */
	rx_buff[ptr_rx_top] = SCI0.RDR;
	ptr_rx_top++;
	ptr_rx_top = ptr_rx_top % RX_RING_BUFF_SIZE;
}

/*
 * 送信バッファエンプティ割込み
 */
void  Excep_SCI0_TXI0(void)
{

	if( ptr_tx_bottom == ptr_tx_top ) { //送信するデータがない
		SCI0.SCR.BIT.TEIE = 1;			//送信終了割り込みの発生を待つ
	} else {
	/* Write the character out */
		SCI0.TDR = tx_buff[ptr_tx_bottom];
		ptr_tx_bottom++;
		ptr_tx_bottom = ptr_tx_bottom % TX_RING_BUFF_SIZE;
	}
}

/*
 * 送信終了割り込み
 */
void Excep_SCI0_TEI0(void)
{
    SCI0.SCR.BIT.TE = 0;	//送信停止
	IR(SCI0,TXI0) = 0;		//割り込みフラグクリア
    SCI0.SCR.BIT.TEIE = 0;	//送信完了割込み停止
    tx_flag = TX_INACTIVE;	//送信回路フラグを停止に
}

/*
 * データの送信
 */
void SCI_put(unsigned char output_char)
{
	int tmp;
	tmp = ptr_tx_top + 1;
	tmp = tmp % TX_RING_BUFF_SIZE;
	while(tmp == ptr_tx_bottom) ;	//バッファに空きができるまで待つ

	tx_buff[ptr_tx_top] = output_char;
	ptr_tx_top++;
	ptr_tx_top = ptr_tx_top % TX_RING_BUFF_SIZE;
	if(tx_flag == TX_INACTIVE) {
		tx_flag = TX_ACTIVE;	//送信回路フラグを動作に
		SCI0.SCR.BIT.TE = 1;	//送信割込み許可
	    SCI0.SCR.BIT.TEIE = 0;	//送信完了割込み停止
	}
}

#else /* USE_SCI_PORT */

/*
 *  SCI1初期化
 *  baudrate bps: 8bit: stop bit 1: Parity none
 *  PCLK 25MHz
 */
void SCI_Init(int baudrate)
{

    /* ---- SCI interrupt request is disabled ---- */
	IR(SCI1,ERI1) = 0;
	IR(SCI1,RXI1) = 0;
	IR(SCI1,TXI1) = 0;
	IR(SCI1,TEI1) = 0;

    /* ---- Initialization of SCI ---- */

    /* PRCR - Protect Register
    b15:b8 PRKEY    - PRC Key Code  - A5h (The write value should be A5h to permission writing PRCi bit)
    b7:b4  Reserved - The write value should be 0.
    b1     PRC1     - Protect Bit 1 - Write enabled */
    SYSTEM.PRCR.WORD = 0xA502;

    /* The module stop state of SCIn is canceled */
    MSTP(SCI1) = 0;

    /* Enable write protection */
    SYSTEM.PRCR.WORD = 0xA500;

    /* SCR - Serial Control Register
    b7     TIE  - Transmit Interrupt Enable     - A TXI interrupt request is disabled
    b6     RIE  - Receive Interrupt Enable      - RXI and ERI interrupt requests are disabled
    b5     TE   - Transmit Enable               - Serial transmission is disabled
    b4     RE   - Receive Enable                - Serial reception is disabled
    b2     TEIE - Transmit End Interrupt Enable - A TEI interrupt request is disabled */
    SCI1.SCR.BYTE = 0x00;

    while (0x00 != (SCI1.SCR.BYTE & 0xF0))
    {
        /* Confirm that bit is actually 0 */
    }

    /* ---- Set the I/O port functions ---- */

    /* Set port output data - High level */
    PORT2.PODR.BIT.B6 = 1;

    /* Set port direction - TXDn is output port, RXDn is input port */
    PORT2.PDR.BIT.B6 = 1;
    PORT3.PDR.BIT.B0 = 0;

    /* Set port mode - Use pin as general I/O port */
    PORT3.PMR.BIT.B0 = 0;
    PORT2.PMR.BIT.B6 = 0;

    /* PWPR - Write-Protect Register
    b7     B0WI     - PFSWE Bit Write Disable   - Writing to the PFSWE bit is enabled
    b6     PFSWE    - PFS Register Write Enable - Writing to the PFS register is enabled
    b5:b0  Reserved - These bits are read as 0. The write value should be 0. */
    MPC.PWPR.BIT.B0WI  = 0;
    MPC.PWPR.BIT.PFSWE = 1;

    /* PFS - Pin Function Control Register
    b3:b0  PSEL - Pin Function Select - RXDn, TXDn */
    MPC.P26PFS.BYTE = 0x0A;
    MPC.P30PFS.BYTE = 0x0A;

    /* Enable write protection */
    MPC.PWPR.BIT.PFSWE = 0;
    MPC.PWPR.BIT.B0WI  = 1;

    /* Use pin as I/O port for peripheral functions */
    PORT3.PMR.BIT.B0 = 1;
    PORT2.PMR.BIT.B6 = 1;

    /* ---- Initialization of SCI ---- */

    /* Select an On-chip baud rate generator to the clock source */
    SCI1.SCR.BIT.CKE = 0;

    /* SMR - Serial Mode Register
    b7     CM   - Communications Mode   - Asynchronous mode
    b6     CHR  - Character Length      - Selects 8 bits as the data length
    b5     PE   - Parity Enable         - When transmitting : Parity bit addition is not performed
                                          When receiving    : Parity bit checking is not performed
    b3     STOP - Stop Bit Length       - 1 stop bits
    b2     MP   - Multi-Processor Mode  - Multi-processor communications function is disabled
    b1:b0  CKS  - Clock Select          - PCLK clock (n = 0) */
    SCI1.SMR.BYTE = 0x00;

    /* SCMR - Smart Card Mode Register
    b6:b4  Reserved - The write value should be 1.
    b3     SDIR     - Transmitted/Received Data Transfer Direction - Transfer with LSB-first
    b2     SINV     - Transmitted/Received Data Invert  - TDR contents are transmitted as they are.
                                                          Receive data is stored as it is in RDR.
    b1     Reserved - The write value should be 1.
    b0     SMIF     - Smart Card Interface Mode Select  - Serial communications interface mode */
    SCI1.SCMR.BYTE = 0xF2;

    /* SEMR - Serial Extended Mode Register
    b7:b6  Reserved - The write value should be 0.
    b5     NFEN     - Digital Noise Filter Function Enable  - Noise cancellation function
                                                              for the RXDn input signal is disabled.
    b4     ABCS     - Asynchronous Mode Base Clock Select   - Selects 16 base clock cycles for 1-bit period
    b3:b1  Reserved - The write value should be 0. */
    SCI1.SEMR.BYTE = 0x00;

    /* BRR - Bit Rate Register
    Bit Rate: (25MHz/(64*2^(-1)*57600bps))-1=12.56 */
    //SCI1.BRR = 13;	/* 57600bps */
    //SCI1.BRR = 40;	/* 19200bps */
    SCI1.BRR = configPERIPHERAL_CLOCK_HZ / 32UL / (unsigned long)baudrate - 1;

    /* ---- Initialization of SCI interrupt ---- */

    /* SCI interrupt priority level is 15 */
    IPR(SCI1, ) = 15;

    /* Interrupt request is cleared (Edge interrupt) */
    IR(SCI1,RXI1) = 0;
    IR(SCI1,TXI1) = 0;

    /* 割り込みの許可 */
	IEN(SCI1, RXI1) = 1;
	IEN(SCI1, ERI1) = 1;
	IEN(SCI1, TXI1) = 1;
	IEN(SCI1, TEI1) = 1;

	/* リングバッファの初期化 */
	ptr_rx_top = ptr_rx_bottom = 0;
	ptr_tx_top = ptr_tx_bottom = 0;

	/* 送受信許可 */
    SCI1.SCR.BIT.RIE = 1;	//受信割込み
    SCI1.SCR.BIT.TIE = 1;	//送信割込み
    SCI1.SCR.BIT.RE = 1;	//受信動作開始
    SCI1.SCR.BIT.TE = 0;

}

/*
 * 受信エラー割り込み
 */
/* SSR - Serial Status Register
b7:b6  Reserved - The read value is undefined. The write value should be 1.
b5     ORER     - Overrun Error Flag    - An overrun error has occurred
b4     FER      - Framing Error Flag    - A framing error has occurred
b3     PER      - Parity Error Flag     - A parity error has occurred */
#define SSR_ERROR_FLAGS     (0x38)
void  Excep_SCI1_ERI1(void)
{
	volatile char c;

	c = SCI1.RDR;	//ダミーリード
	SCI1.SSR.BYTE = (SCI1.SSR.BYTE & ~SSR_ERROR_FLAGS) | 0xC0;	//エラーフラグクリア
}

/*
 * 受信バッファフル割込み
 */
void  Excep_SCI1_RXI1(void)
{

	/* Read data */
	rx_buff[ptr_rx_top] = SCI1.RDR;
	ptr_rx_top++;
	ptr_rx_top = ptr_rx_top % RX_RING_BUFF_SIZE;
}

/*
 * 送信バッファエンプティ割込み
 */
void  Excep_SCI1_TXI1(void)
{

	if( ptr_tx_bottom == ptr_tx_top ) { //送信するデータがない
		SCI1.SCR.BIT.TEIE = 1;			//送信終了割り込みの発生を待つ
	} else {
	/* Write the character out */
		SCI1.TDR = tx_buff[ptr_tx_bottom];
		ptr_tx_bottom++;
		ptr_tx_bottom = ptr_tx_bottom % TX_RING_BUFF_SIZE;
	}
}

/*
 * 送信終了割り込み
 */
void Excep_SCI1_TEI1 (void)
{
    SCI1.SCR.BIT.TE = 0;	//送信停止
	IR(SCI1,TXI1) = 0;		//割り込みフラグクリア
    SCI1.SCR.BIT.TEIE = 0;	//送信完了割込み停止
    tx_flag = TX_INACTIVE;	//送信回路フラグを停止に
}

/*
 * データの送信
 */
void SCI_put(unsigned char output_char)
{
	int tmp;
	tmp = ptr_tx_top + 1;
	tmp = tmp % TX_RING_BUFF_SIZE;
	while(tmp == ptr_tx_bottom) ;	//バッファに空きができるまで待つ

	tx_buff[ptr_tx_top] = output_char;
	ptr_tx_top++;
	ptr_tx_top = ptr_tx_top % TX_RING_BUFF_SIZE;
	if(tx_flag == TX_INACTIVE) {
		tx_flag = TX_ACTIVE;	//送信回路フラグを動作に
		SCI1.SCR.BIT.TE = 1;	//送信割込み許可
	    SCI1.SCR.BIT.TEIE = 0;	//送信完了割込み停止
	}
}
#endif /* USE_SCI_PORT */


/* データの受信　バッファに受信したデータがなければ受信するまで待つ */
unsigned int SCI_get(void)
{
	unsigned int c;

	while(ptr_rx_bottom == ptr_rx_top); //データを受信するまで待つ
	c = rx_buff[ptr_rx_bottom];
	ptr_rx_bottom++;
	ptr_rx_bottom = ptr_rx_bottom % RX_RING_BUFF_SIZE;
	return c;
}

/*
 *  printf関数で使用
 */
void charput(unsigned char c)
{
	if(c=='\r' || c=='\n') {
		SCI_put('\r');
		SCI_put('\n');
	} else {
		SCI_put(c);
	}
}

/*
 * scanf関数で使用
 */
unsigned char charget(void)
{
	unsigned int c;
	c = SCI_get();
	charput(c);	/* エコーバック */
     return c;
}

#endif /* USE_SERIAL_CONSOLE */

