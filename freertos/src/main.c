/*
 * FreeRTOS サンプルプログラム
 *
 * マルチタスクを行うためライブラリにはリエントラントにする必要がある
 *
 * 標準ライブラリ構築ツールで-reent オプションを指定して作成したライブラリは、
 * rand、srand 関数およびEC++ ライブラリを除いてすべてリエントラントに実行できます。
 *
 * -reent オプションを指定した場合は、
 * コンパイル時に_REENTRANTを定義しておく必要があります。　-D_REENTRANT オプション
 *
 */
#include <stdio.h>
#include "iodefine.h"
/* Kernel includes. */
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"
#include "FreeRTOS/queue.h"

volatile int waitt = 1000;
void vTask1(void *pvParameters)
{
	while(1) {
		PORTC.PODR.BIT.B0 = ~PORTC.PODR.BIT.B0;
		vTaskDelay(waitt/portTICK_PERIOD_MS);
		//printf("task 1\n");
	}
}

void vTask2(void *pvParameters)
{
	while(1) {
		PORTC.PODR.BIT.B1 = ~PORTC.PODR.BIT.B1;
		vTaskDelay(500/portTICK_PERIOD_MS);
		//printf("task 2\n");
	}
}

void vTask3(void *pvParameters)
{
	while(1) {
		PORTC.PODR.BIT.B2 = ~PORTC.PODR.BIT.B2;
		vTaskDelay(1000/portTICK_PERIOD_MS);
		//printf("task 3\n ");
		printf("input wait time : ");
		scanf("%d",&waitt);
	}
}

void main(void)
{

	/* Turn all LEDs off. */
	PORTC.PDR.BYTE = 0xFF;	//ポートC出力
	PORTC.PODR.BYTE = 0x00;	//初期値

	xTaskCreate(vTask1,"Task1",100,NULL,1,NULL);
	xTaskCreate(vTask2,"Task2",100,NULL,1,NULL);
	xTaskCreate(vTask3,"Task3",200,NULL,1,NULL);

	vTaskStartScheduler();

	for( ;; );
}

