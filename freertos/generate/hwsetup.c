/************************************************************************
*
* Device     : RX/RX200/RX210
*
* File Name  : hwsetup.c
*
* Abstract   : Hardware Setup file.
*
* History    : 1.00  (2010-12-17)  [Hardware Manual Revision : 0.10]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2010 Renesas Electronics Corporation.
* and Renesas Solutions Corp.
*
************************************************************************/

#include "iodefine.h"
#include <machine.h>
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"

#ifdef __cplusplus
extern "C" {
#endif
void HardwareSetup(void);

/******************************************************************************
Private global variables and functions
******************************************************************************/
void io_set_cpg(void);
void ConfigurePortPins(void);
void EnablePeripheralModules(void);

extern void _INIT_IOLIB( void );
extern void SCI_Init(int baudrate);

void vApplicationSetupTimerInterrupt( void );
void vApplicationMallocFailedHook( void );
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );
void vApplicationIdleHook( void );
#ifdef __cplusplus
}
#endif

/******************************************************************************
* Function Name: HardwareSetup
* Description  : This function does initial setting for CPG port pins used in
*              : the Demo including the MII pins of the Ethernet PHY connection.
* Arguments    : none
* Return Value : none
******************************************************************************/
void HardwareSetup(void)
{
	/* CPG setting */
	io_set_cpg();

	/* Setup the port pins */
	//ConfigurePortPins();

    /* Enables peripherals */
    //EnablePeripheralModules();

	/* use stdio serial port */
#ifdef USE_SERIAL_CONSOLE
	_INIT_IOLIB();
	SCI_Init(SERIAL_BAUD_RATE);
#endif /*USE_SERIAL_CONSOLE*/
}

/******************************************************************************
* Function Name: EnablePeripheralModules
* Description  : Enables Peripheral Modules before use
* Arguments    : none
* Return Value : none
******************************************************************************
void EnablePeripheralModules(void)
{
	//  Module standby clear
	SYSTEM.PRCR.WORD = 0x0A502;
    SYSTEM.MSTPCRA.BIT.MSTPA15 = 0;             // CMT0
    SYSTEM.PRCR.WORD = 0x0A500;
}
*/

/******************************************************************************
* Function Name: ConfigurePortPins
* Description  : Configures port pins.
* Arguments    : none
* Return Value : none
******************************************************************************
void ConfigurePortPins(void)
{
// Port pins default to inputs. To ensure safe initialisation set the pin states
// before changing the data direction registers. This will avoid any unintentional
// state changes on the external ports.
// Many peripheral modules will override the setting of the port registers. Ensure
// that the state is safe for external devices if the internal peripheral module is
// disabled or powered down.
    // Configure LED 0-4 pin settings
    PORT1.PODR.BIT.B4 = 1;
    PORT1.PODR.BIT.B5 = 1;
    PORT1.PODR.BIT.B6 = 1;
    PORT1.PODR.BIT.B7 = 1;

    PORT1.PDR.BIT.B4 = 1;
    PORT1.PDR.BIT.B5 = 1;
    PORT1.PDR.BIT.B6 = 1;
    PORT1.PDR.BIT.B7 = 1;

}
*/

/******************************************************************************
* Function Name: io_set_cpg
* Description  : Sets up operating speed
* Arguments    : none
* Return Value : none
******************************************************************************/
void io_set_cpg(void)
{
/* Set CPU PLL operating frequencies. Changes to the peripheral clock will require
changes to the debugger and flash kernel BRR settings. */

	/* ==== CPG setting ==== */

	volatile unsigned int i;

	SYSTEM.PRCR.WORD = 0xA507;				/* Protect off 						*/

#if (CLK_SRC_HOCO == 1)
	 /* ---- Set the VRCR register ---- */
	SYSTEM.VRCR = 0x00;

	SYSTEM.HOCOPCR.BYTE = 0x00;				/* HOCO power supply on */
	SYSTEM.HOCOCR2.BYTE = 0x03;				/* Select - 50MHz */
	SYSTEM.HOCOWTCR2.BYTE = 0x03;			/* Set wait time until the HOCO oscillator stabilizes  */
	SYSTEM.HOCOCR.BYTE  = 0x01;				/* HOCO is operating */

    SYSTEM.SCKCR.LONG = 0x10811111;	/* ICLK,PCLKD: no division PCLKB,BCLK,FCLK: divide-by-2 */
    while (0x10811110 != SYSTEM.SCKCR.LONG)
    {
         /* Confirm that the written value can be read correctly. */
    }
    // LSB
	//	SYSTEM.SCKCR.BIT.PCKD 	= 1;			/* PLL/2 = 25MHz		*/
    //  reserve 4bit            = 1
	//	SYSTEM.SCKCR.BIT.PCKB 	= 1;			/* PLL/2 = 25MHz		*/
    //  reserve 4bit            = 1
	//	SYSTEM.SCKCR.BIT.BCK 	= 1;			/* PLL/2 = 25MHz		*/
	//	SYSTEM.SCKCR.BIT.PSTOP1 = 1;//(0x80)	/* BUS CLK OUT Disabled */
	//	SYSTEM.SCKCR.BIT.ICK 	= 0;			/* PLL/1 = 50MHz		*/
	//	SYSTEM.SCKCR.BIT.FCK 	= 1;			/* PLL/2 = 25MHz		*/
    // MSB

    SYSTEM.BCKCR.BYTE = 0x01;	/* ---- Set the BCLK pin output ---- */

    while (0x01 != SYSTEM.BCKCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }

	for(i=0; i<10; i++){					/* wait over 60us */
	}


#else
    /* ---- Set the VRCR register ---- */
    SYSTEM.VRCR = 0x00;
    SYSTEM.MOFCR.BYTE = (0x30);	/* Drive capability : 20 MHz crystal resonator */

	SYSTEM.MOSCWTCR.BYTE = 0x0D;			/* Main Clock Oscillator Wait Control Register */
											/* 131072 cycles (approx. 6.55 ms). */
											/* wait over 2 ms  @20MHz 			*/

	SYSTEM.PLLWTCR.BYTE = 0x0B;				/* PLL Wait Control Register 		*/
											/* 262144 states 					*/
											/* wait over 2.1 ms  @PLL = 80Hz	*/
											/*					(20/2x8*8) 		*/

	SYSTEM.MOSCCR.BYTE = 0x00;				/* EXTAL OFF */
    while (0x00 != SYSTEM.MOSCCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }
    /* ---- Wait processing for the clock oscillation stabilization ---- */
    for(i=0;i<100;i++) {
    }



    SYSTEM.PLLCR.WORD = (0x0901);	/* Division ratio and multiplication factor : divide-by-2, multiply-by-10 */
											/* Input to PLL (EXTAL in) / 2 		*/
											/* Therefore:
													PLL = EXTAL / 2
														= 20M / 2
														= 10MHz
												PLL * 8 = 80Mhz
												PLL *10 = 100MHz */
    SYSTEM.PLLWTCR.BYTE = (0x09);	/* Wait control register : 65536 cycles (approx. 655.36 us) */
    SYSTEM.PLLCR2.BYTE = 0x00;
    /* ---- Wait processing for the clock oscillation stabilization ---- */
    for(i=0;i<100;i++) {
    }

    SYSTEM.SCKCR.LONG = 0x21821211;	/* ICLK,PCLKD: divide-by-2 PCLKB,BCLK,FCLK: divide-by-4 */
    while (0x21821211 != SYSTEM.SCKCR.LONG)
    {
         /* Confirm that the written value can be read correctly. */
    }
    // LSB
	//	SYSTEM.SCKCR.BIT.PCKD 	= 2;			/* PLL/4 = 25MHz		*/
    //  reserve 4bit            = 1
	//	SYSTEM.SCKCR.BIT.PCKB 	= 2;			/* PLL/4 = 25MHz		*/
    //  reserve 4bit            = 1
	//	SYSTEM.SCKCR.BIT.BCK 	= 2;			/* PLL/4 = 25MHz		*/
	//	SYSTEM.SCKCR.BIT.PSTOP1 = 1;			/* 0x80 BUS CLK OUT Disabled */
	//	SYSTEM.SCKCR.BIT.ICK 	= 1;			/* PLL/2 = 50MHz		*/
	//	SYSTEM.SCKCR.BIT.FCK 	= 2;			/* PLL/4 = 25MHz		*/
    // MSB

    SYSTEM.BCKCR.BYTE = 0x01;	/* ---- Set the BCLK pin output ---- */
    while (0x01 != SYSTEM.BCKCR.BYTE)
    {
        /* Confirm that the written value can be read correctly. */
    }
#endif


	while(SYSTEM.OPCCR.BIT.OPCMTSF == 1);
	SYSTEM.OPCCR.BIT.OPCMTSF = 0;			/* High-speed operating mode */
	while(SYSTEM.OPCCR.BIT.OPCMTSF == 1);
#if (CLK_SRC_HOCO == 1)
	SYSTEM.SCKCR3.WORD = 0x0100;			/* LOCO -> HOCO */
#else
	SYSTEM.SCKCR3.WORD = 0x0400;			/* LOCO -> PLL */
#endif
	SYSTEM.PRCR.WORD = 0xA500;				/* Protect on	*/
}

/* This variable is not used by this simple Blinky example.  It is defined
purely to allow the project to link as it is used by the full build
configuration. */
/* volatile unsigned long ulHighFrequencyTickCount = 0UL; */


/* A callback function named vApplicationSetupTimerInterrupt() must be defined
to configure a tick interrupt source, and configTICK_VECTOR set in
FreeRTOSConfig.h to install the tick interrupt handler in the correct position
in the vector table.  This example uses a compare match timer.  It can be
into any FreeRTOS project, provided the same compare match timer is available. */
void vApplicationSetupTimerInterrupt( void )
{
	/* Enable compare match timer 0. */
	SYSTEM.PRCR.WORD = 0x0A502;
	MSTP( CMT0 ) = 0;
	SYSTEM.PRCR.WORD = 0x0A500;
	/* Interrupt on compare match. */
	CMT0.CMCR.BIT.CMIE = 1;

	/* Set the compare match value. */
	CMT0.CMCOR = ( unsigned short ) ( ( ( configPERIPHERAL_CLOCK_HZ / configTICK_RATE_HZ ) -1 ) / 8 );

	/* Divide the PCLK by 8. */
	CMT0.CMCR.BIT.CKS = 0;

	/* Enable the interrupt... */
	_IEN( _CMT0_CMI0 ) = 1;

	/* ...and set its priority to the application defined kernel priority. */
	_IPR( _CMT0_CMI0 ) = configKERNEL_INTERRUPT_PRIORITY;

	/* Start the timer. */
	CMT.CMSTR0.BIT.STR0 = 1;
}
/*-----------------------------------------------------------*/

/* If configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h, then this
function will be called if pvPortMalloc() returns NULL because it has exhausted
the available FreeRTOS heap space.  See http://www.freertos.org/a00111.html. */
void vApplicationMallocFailedHook( void )
{
	for( ;; );
}
/*-----------------------------------------------------------*/

/* If configCHECK_FOR_STACK_OVERFLOW is set to either 1 or 2 in
FreeRTOSConfig.h, then this function will be called if a task overflows its
stack space.  See
http://www.freertos.org/Stacks-and-stack-overflow-checking.html. */
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	for( ;; );
}
/*-----------------------------------------------------------*/

/* If configUSE_IDLE_HOOK is set to 1 in FreeRTOSConfig.h, then this function
will be called on each iteration of the idle task.  See
http://www.freertos.org/a00016.html */
void vApplicationIdleHook( void )
{
	// Just to prevent the variable getting optimised away.
	wait();
}
/*-----------------------------------------------------------*/

