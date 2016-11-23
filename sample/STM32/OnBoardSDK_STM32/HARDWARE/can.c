#include "can.h"
#include "zkrt.h"						

volatile uint8_t can1_rx_buff[DEVICE_NUMBER][CAN_BUFFER_SIZE];

volatile uint16_t can1_rx_buff_store[DEVICE_NUMBER];

uint16_t can1_rx_buff_get[DEVICE_NUMBER];

uint8_t CAN1_Mode_Init(uint8_t mode)
{
	GPIO_InitTypeDef 			 GPIO_InitStructure; 
	CAN_InitTypeDef        CAN_InitStructure;
	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
	
	//使能相关时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                  											 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	//初始化GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化PA11,PA12

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); 
	
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
	
	//配置过滤器
	CAN_FilterInitStructure.CAN_FilterNumber=0;	  
	CAN_FilterInitStructure.CAN_FilterMode=CAN_FilterMode_IdMask; 
	CAN_FilterInitStructure.CAN_FilterScale=CAN_FilterScale_32bit; 
	CAN_FilterInitStructure.CAN_FilterIdHigh=0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh=~(0XF0<<5);
	CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xFFFF;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
	CAN_FilterInitStructure.CAN_FilterActivation=ENABLE; 
	CAN_FilterInit(&CAN_FilterInitStructure);//滤波器初始化
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVICX_init(0,3);
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);//FIFO0消息挂号中断允许.		    
	
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
	
	GPIO_ResetBits(GPIOD, GPIO_Pin_4);
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
  while((CAN_TransmitStatus(CAN1, mbox)!=CAN_TxStatus_Ok)&&(i<0XFFF))i++;	
printf("33333333333333333333333!\r\n");	
	if(i>=0XFFF)//返回1失败
	{
	printf("4444444444444444444444444!\r\n");
		CAN1_Mode_Init(CAN_Mode_Normal);
		return 1;
	}
	printf("555555555555555555!\r\n");
	GPIO_ResetBits(GPIOD, GPIO_Pin_5);//点亮CAN_TX
	can_tx_flag = TimingDelay;				
	
  return 0;//返回0成功
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













