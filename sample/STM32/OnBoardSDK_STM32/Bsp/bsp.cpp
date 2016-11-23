/*! @file bsp.cpp
 *  @version 3.1.8
 *  @date Aug 05 2016
 *
 *  @brief
 *  Helper functions for board STM32F4Discovery
 *
 *  Copyright 2016 DJI. All right reserved.
 *
 * */

#include "bsp.h"
#include "main.h"
#include "BspUsart.h"
#ifdef __cplusplus
extern "C"
{
#include "sys.h"
#include "adc.h"
#include "usart.h"
#include "timer_zkrt.h"
#include "led.h"
#include "iic.h"
#include "flash.h"
#include "can.h"
#include "ds18b20.h"
}
#endif //__cplusplus


void BSPinit()
{
 SystemInit ();
 RCC_Configuration();
  SystickConfig();
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
delay_init();
led_init();
  TIM4_Int_Init();
  Timer1Config();
  Timer2Config();
#if defined _TEMPTURE_IO_
	DS18B20_Init();																		
#endif
  IIC_Init();
  STMFLASH_Init();
  Usart_DJI_Config();
    uart_init();
  ADC1_Init();
  CAN1_Mode_Init(CAN_Mode_Normal);
}
