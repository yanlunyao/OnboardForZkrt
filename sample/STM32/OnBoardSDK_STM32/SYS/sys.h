#ifndef __SYS_H
#define __SYS_H	 

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

#define _Send_Normal  1
//#define _Send_test    2


//#define _TEMPTURE_IO_		1
#define _TEMPTURE_ADC_	    2
																	  
//IO�ڲ����궨��
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO�ڵ�ַӳ��
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40020014
#define GPIOB_ODR_Addr    (GPIOB_BASE+20) //0x40020414 
#define GPIOC_ODR_Addr    (GPIOC_BASE+20) //0x40020814 
#define GPIOD_ODR_Addr    (GPIOD_BASE+20) //0x40020C14 
#define GPIOE_ODR_Addr    (GPIOE_BASE+20) //0x40021014 
#define GPIOF_ODR_Addr    (GPIOF_BASE+20) //0x40021414    
#define GPIOG_ODR_Addr    (GPIOG_BASE+20) //0x40021814   
#define GPIOH_ODR_Addr    (GPIOH_BASE+20) //0x40021C14    
#define GPIOI_ODR_Addr    (GPIOI_BASE+20) //0x40022014     

#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40020010 
#define GPIOB_IDR_Addr    (GPIOB_BASE+16) //0x40020410 
#define GPIOC_IDR_Addr    (GPIOC_BASE+16) //0x40020810 
#define GPIOD_IDR_Addr    (GPIOD_BASE+16) //0x40020C10 
#define GPIOE_IDR_Addr    (GPIOE_BASE+16) //0x40021010 
#define GPIOF_IDR_Addr    (GPIOF_BASE+16) //0x40021410 
#define GPIOG_IDR_Addr    (GPIOG_BASE+16) //0x40021810 
#define GPIOH_IDR_Addr    (GPIOH_BASE+16) //0x40021C10 
#define GPIOI_IDR_Addr    (GPIOI_BASE+16) //0x40022010 
 
//IO�ڲ���,ֻ�Ե�һ��IO��!
//ȷ��n��ֵС��16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����

#define PHout(n)   BIT_ADDR(GPIOH_ODR_Addr,n)  //��� 
#define PHin(n)    BIT_ADDR(GPIOH_IDR_Addr,n)  //����

#define PIout(n)   BIT_ADDR(GPIOI_ODR_Addr,n)  //��� 
#define PIin(n)    BIT_ADDR(GPIOI_IDR_Addr,n)  //����

#define MAVLINK_TX_INIT_VAL 0XFFFFFFFF 	
extern volatile uint32_t TimingDelay;
extern volatile uint32_t usart1_tx_flag;
extern volatile uint32_t usart1_rx_flag;
extern volatile uint32_t can_tx_flag;
extern volatile uint32_t can_rx_flag;
extern volatile uint32_t mavlink_send_flag;
extern volatile uint32_t _160_read_flag;
extern volatile uint32_t posion_recv_flag;
extern volatile uint32_t throw_recv_flag;
extern volatile uint32_t camera_recv_flag;
extern volatile uint32_t _read_count;

extern NVIC_InitTypeDef NVIC_InitStructure;

void RCC_Configuration(void);
void delay_init(void);
void delay_us(uint16_t nus);					//��ഫ��999us
void delay_ms(uint16_t nms);					//��ഫ��65535ms
void NVICX_init(uint8_t pre_prrty, uint8_t sub_prrty);
 void DMAX_init(DMA_Stream_TypeDef *dma_stream, uint32_t dma_channel, uint32_t peripheral_addr, uint32_t memory_addr,uint32_t direction, 
	uint16_t buff_size, uint32_t peripheral_size, uint32_t memory_size, uint32_t dma_mode, uint32_t dma_prrty);

#if defined _TEMPTURE_IO_
#define TEMPTURE_LOW_EXTRA  -550
#define TEMPTURE_HIGH_EXTRA 1250
#define TEMPTURE_DIFF         8
#elif defined _TEMPTURE_ADC_
#define TEMPTURE_LOW_EXTRA  0
#define TEMPTURE_HIGH_EXTRA 10000
#endif

extern short glo_tempture_low;
extern short glo_tempture_high;

extern short last_tempture0;
extern short last_tempture1;

extern short tempture0;
extern short tempture1;

extern uint8_t msg_smartbat_buffer[30];
#endif





