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
#include "osqtmr.h"
#include "ostmr.h"
#include "sram.h"
#include "malloc.h"
#include "lwip_comm.h"	
#include "exfuns.h"
#include "usb_usr_process.h"
}
#endif //__cplusplus


void BSPinit()
{
//	SystemInit(); //modify by yanly
//	RCC_Configuration(); //�������ڲ�ʱ�ӣ���ʱ���Ϊ�ⲿ�����ṩʱ�ӵķ�ʽ //need to modify in the future //todo yanly
	SystickConfig();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	delay_init();
	led_init();
	FSMC_SRAM_Init();
	mymem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
	mymem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
	b_ostmr_init();  //timer3
	b_systmr_init(); //timer4
	lwip_timer_init(); //רΪ����ʹ�õĶ�ʱ��ʱ��
//#ifdef USE_SRAM
//	//todo yanly
//#endif	
//	TIM4_Int_Init();
//	Timer1Config();
//	Timer2Config();
//#ifdef _TEMPTURE_IO_
//	DS18B20_Init();																		
//#endif
//#ifdef USE_IIC	
//	IIC_Init();
//#endif	
//	STMFLASH_Init();
//	Usart_DJI_Config();
	uart_init();
//#ifdef _TEMPTURE_ADC_	
//	ADC1_Init();
//#endif
//#ifdef USE_CAN1
//	CAN1_Mode_Init(CAN_Mode_Normal);
//#endif
 	exfuns_init();			//Ϊfatfs��ر��������ڴ� 
	f_mount(fs[2],"2:",1); 	//����U��
  lwip_comm_init();
  USBH_Init(&USB_OTG_Core,USB_OTG_FS_CORE_ID,&USB_Host,&USBH_MSC_cb,&USR_Callbacks);  //��ʼ��USB����
}
