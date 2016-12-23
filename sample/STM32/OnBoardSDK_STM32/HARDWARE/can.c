/**
  ******************************************************************************
  * @file    can.c
  * @author  ZKRT
  * @version V0.0.1
  * @date    13-December-2016
  * @brief   CAN����
  *           + .. 
  *           + [2] CAN1TX��PA12�޸�ΪPB9, CAN1RX��PA11�޸�ΪPB8(��ΪоƬ��100pin��VET6����144pin��ZET6); --161213 by yanly
  *         
  ******************************************************************************
  * @attention
  *
  * ...
  *
  ******************************************************************************  
  */ 
#include "can.h"
#include "zkrt.h"		
#include "led.h"

volatile uint8_t can1_rx_buff[DEVICE_NUMBER][CAN_BUFFER_SIZE];
volatile uint16_t can1_rx_buff_store[DEVICE_NUMBER]; //�����ﱣ��ÿ��CAN�豸�������ݵ��ֽ��������ܵ����ݺ�can1_rx_buff_store[type]++һֱ�ۼӣ�����CAN_BUFFER_SIZE������0�����ۼ�
uint16_t can1_rx_buff_get[DEVICE_NUMBER]; //ÿ����һ��can1_rx_buff[type][can1_rx_buff_store[type]]��can1_rx_buff_get++�ۼӣ�ѭ���ۼ�

uint8_t CAN1_Mode_Init(uint8_t mode)
{
	GPIO_InitTypeDef 			 GPIO_InitStructure; 
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	//ʹ�����ʱ��
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   //old pin config, modify by yanly for(2)
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	//��ʼ��GPIO
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12; //old pin config, modify by yanly for(2)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9| GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_CAN1); 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_CAN1); 
	
	CAN_DeInit(CAN1);
	CAN_InitStructure.CAN_TTCM=DISABLE;
	CAN_InitStructure.CAN_ABOM=DISABLE;
	CAN_InitStructure.CAN_AWUM=DISABLE;
	CAN_InitStructure.CAN_NART=DISABLE;	
	CAN_InitStructure.CAN_RFLM=DISABLE;	
	CAN_InitStructure.CAN_TXFP=DISABLE;
	CAN_InitStructure.CAN_Mode= mode;	 
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS2_3tq;
	CAN_InitStructure.CAN_Prescaler=7;
	CAN_Init(CAN1, &CAN_InitStructure);   
	
	//���ù�����
	CAN_FilterInitStructure.CAN_FilterNumber=0;	  
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=~(0XF0<<5);
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xFFFF;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVICX_init(NVIC_PPRIORITY_CAN, NVIC_SUBPRIORITY_CAN);
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0��Ϣ�Һ��ж�����    
	
	return 0;
}   

void CAN1_RX0_IRQHandler(void)
{
	uint8_t i;
	uint8_t can1_rx_type;
	CanRxMsg RxMessage;
	
	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	can1_rx_type = ((RxMessage.StdId)>>4) - 1;
	
	for (i = 0; i < RxMessage.DLC; i++)
	{
		can1_rx_buff[can1_rx_type][can1_rx_buff_store[can1_rx_type]] = RxMessage.Data[i];
		
		can1_rx_buff_store[can1_rx_type]++;
		if (can1_rx_buff_store[can1_rx_type] == CAN_BUFFER_SIZE)
		{
			can1_rx_buff_store[can1_rx_type] = 0;
		}
	}
	
//	GPIO_ResetBits(GPIOD, GPIO_Pin_4);   //modify by yanly
	_CAN1_RX_LED = 0;
	can_rx_flag = TimingDelay;				
}


uint8_t CAN1_rx_check(uint8_t can1_rx_type)
{
	can1_rx_type--;
	if (can1_rx_buff_store[can1_rx_type] == can1_rx_buff_get[can1_rx_type])
		return 0;
	else 
		return 1;
}


uint8_t CAN1_rx_byte(uint8_t can1_rx_type)
{
	uint8_t ch;	
	can1_rx_type--;
	ch = can1_rx_buff[can1_rx_type][can1_rx_buff_get[can1_rx_type]];
	
	can1_rx_buff_get[can1_rx_type]++;
	if (can1_rx_buff_get[can1_rx_type] == CAN_BUFFER_SIZE)
	{
		can1_rx_buff_get[can1_rx_type] = 0;
	}

	return ch;
}

uint8_t CAN1_send_msg(uint8_t* msg,uint8_t len,uint8_t id)
{	
  uint8_t mbox;
  uint16_t i=0;
  CanTxMsg TxMessage;
  TxMessage.StdId=id;	 
  TxMessage.ExtId=0x00;	 
  TxMessage.IDE=CAN_Id_Standard;		 
  TxMessage.RTR=CAN_RTR_Data;		  
  TxMessage.DLC=len;							
  for(i=0;i<len;i++)
		TxMessage.Data[i]=msg[i];				           
  mbox= CAN_Transmit(CAN1, &TxMessage);
  printf("2222222222222222222222!\r\n");
  i=0;
  while((CAN_TransmitStatus(CAN1, mbox)!=CAN_TxStatus_Ok)&&(i<0XFFF))
		i++;	
	printf("33333333333333333333333!\r\n");	
	if(i>=0XFFF)//����1ʧ��
	{
	printf("4444444444444444444444444!\r\n");
		CAN1_Mode_Init(CAN_Mode_Normal);
		return 1;
	}
	printf("555555555555555555!\r\n");
//	GPIO_ResetBits(GPIOD, GPIO_Pin_5);//����CAN_TX //modify by yanly
	_CAN1_TX_LED = 0;
	
	can_tx_flag = TimingDelay;				
	
  return 0;//����0�ɹ�
}


uint8_t CAN1_send_message_fun(uint8_t *message, uint8_t len, uint8_t id)
{
	uint8_t count;		              
	uint8_t time;
	
	time = len/8;            
	printf("1111111111111111111111\r\n");
	for (count = 0; count < time; count++)
	{
		CAN1_send_msg(message, 8, id);
		message += 8;
	}
	if (len%8)                          
	{
		CAN1_send_msg(message, len%8, id);
	}
	
	return 0;
}

