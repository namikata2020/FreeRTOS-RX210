# FreeRTOS for Renesas RX210 MPU

ルネサスエレクトロニクス製MPU RX210用のFreeRTOSの実装です。

## OSバージョン

　v10.4.1
 
## ターゲットボード

　[秋月電子通商製](https://akizukidenshi.com/catalog/default.aspx)マイコンボード[AE-RX210](https://akizukidenshi.com/catalog/g/gK-08207/)　

## 開発環境

　IDE　　　　[e2-studio](https://www.renesas.com/jp/ja/products/software-tools/tools/ide/e2studio.html)　Version: 2020-07 (20.7.0)
　githubの更新は[EGit](https://www.eclipse.org/egit/)を使用しています。[e2-studioでの使用方法](https://ja-support.renesas.com/knowledgeBase/18674128)
 
　Compiler　 Renesas [CC-RX](https://www.renesas.com/jp/ja/products/software-tools/tools/compiler-assembler/compiler-package-for-rx-family.html) V2.08.01

### IDE設定


ライブラリはリエントラントに作成する必要があります。

標準ライブラリ構築ツールで-reent オプションを指定して作成したライブラリは、rand、srand 関数およびEC++ ライブラリを除いてすべてリエントラントに実行できます。

-reent オプションを指定した場合は、コンパイル時に_REENTRANTを定義しておく必要があります。`#define _REENTRANT` コンパイル時の -D_REENTRANT オプション


## 追加機能

シリアルポートを利用して標準入出力(stdio.h,printf(),scanf())関数が動作します。設定は"FreeRTOS/FreeRTOSConfig.h"ファイルを書き換えて行います。

```
FreeRTOSConfig.h抜粋

/* Board specifics. */
/* use serial console */
#define		USE_SERIAL_CONSOLE

#ifdef USE_SERIAL_CONSOLE
/* serial port SCI0 or SCI1 */
#define		USE_SCI_PORT	0

/* serial baud rate
   8bit: stop bit 1: Parity none
*/
#define		SERIAL_BAUD_RATE	38400

#endif /* USE_SERIAL_CONSOLE */
```

`#define		USE_SERIAL_CONSOLE` をコメントアウトすると標準入出力の機能が使えなくなる。(使用できるROM領域が増える)

`#define		USE_SCI_PORT	0` でSCI0(RS232C)を使うのかSCI1(USB)を使うのか設定する。

`#define		SERIAL_BAUD_RATE	38400` で通信速度を設定します。

## その他

'hwsetup.c'ファイル内にFreeRTOSのコードの一部が入っています。

* void vApplicationSetupTimerInterrupt( void )
* void vApplicationMallocFailedHook( void )
* void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
* void vApplicationIdleHook( void )
