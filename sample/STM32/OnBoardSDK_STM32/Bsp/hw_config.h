#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H 

#include "stm32f4xx.h"

////////////////////////////////////////////////////////////////////////////////////////////hardware control
//#define USE_IIC                 1
#define USE_SRAM                  1
//#define USE_CAN1                1
//#define _TEMPTURE_IO_        1
//#define _TEMPTURE_ADC_	     2
#define _TEMPTURE_NONE            3


////////////////////////////////////////////////////////////////////////////////////////////clk label
#define SYSTEM_CLK	     168
#define APB1_CLK		     42
#define APB2_CLK         84
#define APB1_TIMER_CLK	 84
#define APB2_TIMER_CLK   168

////////////////////////////////////////////////////////////////////////////////////////////pin config
//////timer config marco
//fast timer task
#define	RCC_TIMER_1ST																RCC_APB1Periph_TIM3
#define	TIMER_CHANNEL_1ST														TIM3
#define	TIMER_IRQ_CHANNEL_1ST												TIM3_IRQn
#define	NVIC_TIMER_PreemptionPriority_1ST						2
#define	NVIC_TIMER_SubPriority_1ST									1
//quick fast timer task
#define	RCC_TIMER_2ND																RCC_APB1Periph_TIM4
#define	TIMER_CHANNEL_2ND														TIM4
#define	TIMER_IRQ_CHANNEL_2ND												TIM4_IRQn
#define	NVIC_TIMER_PreemptionPriority_2ND						2     //中断优先级最高
#define	NVIC_TIMER_SubPriority_2ND									0
//lwip timer 
#define	RCC_TIMER_LWIP															RCC_APB1Periph_TIM2
#define	TIMER_CHANNEL_LWIP													TIM2
#define	TIMER_IRQ_CHANNEL_LWIP											TIM2_IRQn
#define	NVIC_TIMER_PreemptionPriority_LWIP					2     //中断优先级最高
#define	NVIC_TIMER_SubPriority_LWIP									2
//network nvic
#define NVIC_PPRIORITY_NETWORK											0
#define NVIC_SUBPRIORITY_NETWORK                    0
//can nvic
#define NVIC_PPRIORITY_CAN											    0
#define NVIC_SUBPRIORITY_CAN                        3
//dji usart nvic
#define NVIC_PPRIORITY_DJIUSART											3
#define NVIC_SUBPRIORITY_DJIUSART	                  2
//usart2 nvic 
#define NVIC_PPRIORITY_UART2											  1
#define NVIC_SUBPRIORITY_UART2                      1
//usart3 nvic 
#define NVIC_PPRIORITY_UART3											  1
#define NVIC_SUBPRIORITY_UART3                      2
//usart4 nvic 
#define NVIC_PPRIORITY_UART4											  1
#define NVIC_SUBPRIORITY_UART4                      3


#endif
