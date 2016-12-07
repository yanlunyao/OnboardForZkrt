#include "led.h"
/*
PC0：RUN
PC1：ALRM
PC2：H/S
PD0：USART1_TX
PD1：USART1_RX
PD2：USART2_TX
PD3：USART2_RX
PD4：CAN1_RX
PD5：CAN1_TX

PA8：对应5V电压的使能。0关闭，1使能
PE2：对应爆闪模块1的供电使能。0关闭，1使能
PE9：对应爆闪模块2的供电使能。0关闭，1使能
*/

void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); //yanly test
	
	
 	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd   = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA, GPIO_Pin_8);
	
	delay_ms(500);										
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOD, &GPIO_InitStructure);		  

	GPIO_SetBits(GPIOC, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
	GPIO_SetBits(GPIOD, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_9;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_9);
	
	//test yanly
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_9;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOF, GPIO_Pin_10 | GPIO_Pin_9);
}

/*
@brief: 所有LED灯一秒闪速一次
*/
void led_test(void)
{
	while(1)
	{
		delay_ms(500);
//		_RUN_LED = !_RUN_LED;
//		_ALARM_LED = !_ALARM_LED;
//		_HS_LED = !_HS_LED;
//		_DJI_UART_TX_LED = !_DJI_UART_TX_LED;
//		_DJI_UART_RX_LED = !_DJI_UART_RX_LED;
//		_TEST_UART_TX_LED = !_TEST_UART_TX_LED;
//		_TEST_UART_RX_LED = !_TEST_UART_RX_LED;
//		_CAN1_RX_LED  =!_CAN1_RX_LED;
//		_CAN1_TX_LED = !_CAN1_TX_LED;	
		PFout(9) = ! PFout(9);
		PFout(10) = ! PFout(10);
	}
}	
