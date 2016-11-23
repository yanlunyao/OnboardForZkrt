/*! @file BspUsart.cpp
 *  @version 3.1.7
 *  @date Jul 01 2016
 *
 *  @brief
 *  Usart helper functions and ISR for board STM32F4Discovery
 *
 *  Copyright 2016 DJI. All right reserved.
 *
 * */

#include "BspUsart.h"
#include "DJI_API.h"
#include "DJI_HardDriver.h"
#include "DJI_Flight.h"

#ifdef __cplusplus
extern "C"
{
#include "zkrt.h"
#include "tempture.h"
#include "djiapp.h"
#include "sys.h"
}
#endif //__cplusplus


extern int Rx_Handle_Flag;
int k=0;
using namespace DJI::onboardSDK;
extern CoreAPI defaultAPI;
extern CoreAPI *coreApi;
extern Flight flight;
extern FlightData flightData;

 unsigned char come_data;
extern unsigned char Rx_length;
extern int Rx_adr;
extern int Rx_Handle_Flag;
extern unsigned char Rx_buff[];
extern zkrt_packet_t main_dji_rev;


extern "C" void DMAX_init(DMA_Stream_TypeDef *dma_stream, uint32_t dma_channel, uint32_t peripheral_addr, uint32_t memory_addr,uint32_t direction, 
	uint16_t buff_size, uint32_t peripheral_size, uint32_t memory_size, uint32_t dma_mode, uint32_t dma_prrty);
extern "C" void NVICX_init(uint8_t pre_prrty, uint8_t sub_prrty);
#if 1
/***********************************************************************
		         �п���̩�������˻���������
		
		���� ���ƣ��󽮴��ڳ�ʼ������     
	       ���� ���ܣ�
		���� ��Σ�
		��������ֵ��
		˵     ����

************************************************************************/

#if 1

void USART1_Config(void)
{
	/*************��GPIO������*****************/
         GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//ʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��

	//USART�˿�����
       GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //�PPA9��PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ���PPA9��PA10

	
	//����ӳ������
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_USART1);//GPIOA9 ����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);//GPIOA10����ΪUSART1

	//USART1�ĳ�ʼ������
	USART_InitStructure.USART_BaudRate = 230400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	
	/***********����1**********/
	USART_Init(USART1, &USART_InitStructure); //��ʼ������
	 USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET)
    ;
	
}
void USARTxNVIC_Config()
{
  NVIC_InitTypeDef NVIC_InitStructure;
 
 // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStructure);


}

void Usart_DJI_Config()
{
  USART1_Config();
  USARTxNVIC_Config();
}


#endif


#endif
/***********************************************************************
		          �п���̩�������˻���������
		
		���� ���ƣ�   
	       ���� ���ܣ�
		���� ��Σ�
		��������ֵ��
		˵     ����

************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

void USART1_IRQHandler(void)
{
  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
  {
  come_data=USART_ReceiveData(USART1);
    coreApi->byteHandler(come_data); //Data from M100 were committed to "byteHandler"
  //  if (come_data==0x55)
  //   printf("0x %x   ",come_data);
  }

}
#ifdef __cplusplus
}
#endif //__cplusplus









/***********************************************************************
		          �п���̩�������˻���������
		
		���� ���ƣ����մ�����
	       ���� ���ܣ�
		���� ��Σ�
		��������ֵ��
		˵     ����

************************************************************************/

void main_dji_recv(void)
{
	//	memcpy((void *)&main_dji_rev, (void *)&(Rx_buff[5]), 40); 

printf("***************main_dji_revdata_form_mobile************************\r\n");

printf("main_dji_rev.start_code=0x %x\r\n",main_dji_rev.start_code);
printf("main_dji_rev.ver=0x %x\r\n",main_dji_rev.ver);
printf("main_dji_rev.session_ack=0x %x \r\n",main_dji_rev.session_ack);
printf("main_dji_rev.padding_enc=0x %x\r\n",main_dji_rev.cmd);
printf("main_dji_rev.cmd=0x %x\r\n",main_dji_rev.ver);
printf("main_dji_rev.length=0x %x\r\n",main_dji_rev.length);
printf("main_dji_rev.seq=0x %x\r\n",main_dji_rev.seq);
printf("main_dji_rev.APPID[0]=0x %x \r\n",main_dji_rev.APPID[0]);
printf("main_dji_rev.APPID[1]=0x %x \r\n",main_dji_rev.APPID[1]);
printf("main_dji_rev.APPID[2]=0x %x \r\n",main_dji_rev.APPID[2]);
printf("main_dji_rev.UAVID[0]=0x %x \r\n",main_dji_rev.UAVID[0]);
printf("main_dji_rev.UAVID[1]=0x %x\r\n",main_dji_rev.UAVID[1]);
printf("main_dji_rev.UAVID[2]=0x %x\r\n",main_dji_rev.UAVID[2]);
printf("main_dji_rev.UAVID[3]=0x %x\r\n",main_dji_rev.UAVID[3]);
printf("main_dji_rev.UAVID[4]=0x %x\r\n",main_dji_rev.UAVID[4]);
printf("main_dji_rev.UAVID[5]=0x %x\r\n",main_dji_rev.UAVID[5]);
printf("main_dji_rev.command=0x %x \r\n",main_dji_rev.command);

  for(k=0;k<30;k++)
	{
	printf("main_dji_rev.data[%d]=0x %x\r\n",k,main_dji_rev.data[k]);
	}

printf("main_dji_rev.crc=0x %x\r\n",main_dji_rev.crc);
printf("main_dji_rev.end_code=0x %x\r\n",main_dji_rev.end_code);

		if (main_dji_rev.UAVID[3] == DEVICE_TYPE_TEMPERATURE) /*�����¶����ֵ�����ֵ*/																				
		{
		printf("&&&&&&&&&&&&&&\r\n");
		glo_tempture_low =  ((main_dji_rev.data[1])<<8)+(main_dji_rev.data[0]);				
		glo_tempture_high = ((main_dji_rev.data[3])<<8)+(main_dji_rev.data[2]);
		}
		else if (main_dji_rev.UAVID[3] == DEVICE_TYPE_BAOSHAN)/*���ñ�����*/																	
		{
		printf("###############\r\n");
		if (main_dji_rev.data[0] == 0X00)		
		{
			GPIO_ResetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_9);	
			delay_ms(1000);											
			msg_smartbat_dji_buffer[24] &= 0XF7;			
		}
		else if (main_dji_rev.data[0] == 0X01)	
		{
			GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_9);	
			delay_ms(1000);
			msg_smartbat_dji_buffer[24] |= 0X08;			
		}
		}
		else
		{
		printf("CAN1_send_message_fun\r\n");
		//CAN1_send_message_fun((uint8_t *)(&main_dji_rev), _TOTAL_LEN, (main_dji_rev.UAVID[3]));/*ͨ��CAN���߷�������*/
		CAN1_send_message_fun((uint8_t *)(&main_dji_rev), _TOTAL_LEN, 0x6);/*ͨ��CAN���߷�������*/
		}
			

}




