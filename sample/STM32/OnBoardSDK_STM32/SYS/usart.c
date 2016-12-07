#include <stdio.h>
#include <string.h>
#include "usart.h"	
#include "sbus.h"

/*********USART1************/
volatile uint8_t usart1_tx_buffer[USART_BUFFER_SIZE];//tx缓冲器
volatile uint8_t usart1_rx_buffer[USART_BUFFER_SIZE];//rx缓冲器
uint16_t usart1_tx_buffer_tail = 0;
uint16_t usart1_tx_buffer_head = 0;		 
uint16_t usart1_rx_buffer_pos = 0; 
															

/*********USART2************/
volatile uint8_t usart2_tx_buffer[USART_BUFFER_SIZE];
volatile uint8_t usart2_rx_buffer[USART_BUFFER_SIZE];
uint16_t usart2_tx_buffer_tail = 0;
uint16_t usart2_tx_buffer_head = 0;
uint16_t usart2_rx_buffer_pos = 0;


/*********USART3************/
volatile uint8_t usart3_tx_buffer[USART_BUFFER_SIZE];
volatile uint8_t usart3_rx_buffer[USART_BUFFER_SIZE];
uint16_t usart3_tx_buffer_tail = 0;
uint16_t usart3_tx_buffer_head = 0;
uint16_t usart3_rx_buffer_pos = 0;


/*********USART4************/
volatile uint8_t uart4_tx_buffer[USART_BUFFER_SIZE];
volatile uint8_t uart4_rx_buffer[USART_BUFFER_SIZE];
uint16_t uart4_tx_buffer_tail = 0;
uint16_t uart4_tx_buffer_head = 0;
uint16_t uart4_rx_buffer_pos = 0;


//初始化串口
void uart_init(void)
{
	/*************对GPIO的配置*****************/
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//时钟配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB,ENABLE); //使能GPIOA、GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB1Periph_USART3|RCC_APB1Periph_UART4,ENABLE);//使能USART2、USART3、UART4时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); //test yanly
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);	 //for USART2/3
	
//////test yan	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
//	
//	//usart1tx dma
//	DMAX_init(DMA2_Stream7,DMA_Channel_4, (uint32_t)&USART1->DR, (uint32_t)usart1_tx_buffer, DMA_DIR_MemoryToPeripheral, 
//	USART_BUFFER_SIZE, DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_High);
//	
//	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream7_IRQn;
//	NVICX_init(1,4);
//	DMA_ITConfig(DMA2_Stream7, DMA_IT_TC, ENABLE);
//	
//	DMA_SetCurrDataCounter(DMA2_Stream7, 0);
//	
//	//usart1rx dma
//	DMAX_init(DMA2_Stream5, DMA_Channel_4, (uint32_t)&USART1->DR, (uint32_t)usart1_rx_buffer, DMA_DIR_PeripheralToMemory, 
//	USART_BUFFER_SIZE, DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Circular, DMA_Priority_VeryHigh);

//	DMA_Cmd(DMA2_Stream5, ENABLE);                      
//	usart2_rx_buffer_pos = DMA_GetCurrDataCounter(DMA2_Stream5);

//	//串口1对应引脚复用映射
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
//	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
//	//USART1端口配置
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
//	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10
//	   //USART1 初始化设置
//	USART_InitStructure.USART_BaudRate = 115200;//波特率设置
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
//	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
//  USART_Init(USART1, &USART_InitStructure); //初始化串口1
//  USART_Cmd(USART1, ENABLE);  //使能串口1 
//	USART_ClearFlag(USART1, USART_FLAG_TC);
//	
//	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
//////	
	
	//usart2tx dma
	DMAX_init(DMA1_Stream6, DMA_Channel_4, (uint32_t)&USART2->DR, (uint32_t)usart2_tx_buffer, DMA_DIR_MemoryToPeripheral, 
	USART_BUFFER_SIZE, DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_High);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
	NVICX_init(1,1);
	DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);
	
	DMA_SetCurrDataCounter(DMA1_Stream6, 0);
	
	//usart2rx dma
	DMAX_init(DMA1_Stream5, DMA_Channel_4, (uint32_t)&USART2->DR, (uint32_t)usart2_rx_buffer, DMA_DIR_PeripheralToMemory, 
	USART_BUFFER_SIZE, DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Circular, DMA_Priority_VeryHigh);

	DMA_Cmd(DMA1_Stream5, ENABLE);                      
	usart2_rx_buffer_pos = DMA_GetCurrDataCounter(DMA1_Stream5);
	
	//usart3tx dma
	DMAX_init(DMA1_Stream3, DMA_Channel_4, (uint32_t)&USART3->DR, (uint32_t)usart3_tx_buffer, DMA_DIR_MemoryToPeripheral, 
	USART_BUFFER_SIZE, DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_High);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;
	NVICX_init(1,2);
	DMA_ITConfig(DMA1_Stream3, DMA_IT_TC, ENABLE);
	
	DMA_SetCurrDataCounter(DMA1_Stream3, 0);
	
	//usart3rx dma
	DMAX_init(DMA1_Stream1, DMA_Channel_4, (uint32_t)&USART3->DR, (uint32_t)usart3_rx_buffer, DMA_DIR_PeripheralToMemory, 
	USART_BUFFER_SIZE, DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Circular, DMA_Priority_VeryHigh);

	DMA_Cmd(DMA1_Stream1, ENABLE);                     
	usart3_rx_buffer_pos = DMA_GetCurrDataCounter(DMA1_Stream1);
	
	//usart4tx dma
	DMAX_init(DMA1_Stream4, DMA_Channel_4, (uint32_t)&UART4->DR, (uint32_t)uart4_tx_buffer, DMA_DIR_MemoryToPeripheral, 
	USART_BUFFER_SIZE, DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_High);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream4_IRQn;
	NVICX_init(1,3);
	DMA_ITConfig(DMA1_Stream4, DMA_IT_TC, ENABLE);
	
	DMA_SetCurrDataCounter(DMA1_Stream4, 0);
	
	//usart4rx dma
	DMAX_init(DMA1_Stream2, DMA_Channel_4, (uint32_t)&UART4->DR, (uint32_t)uart4_rx_buffer, DMA_DIR_PeripheralToMemory, 
	USART_BUFFER_SIZE, DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Circular, DMA_Priority_VeryHigh);

	DMA_Cmd(DMA1_Stream2, ENABLE);                     
	uart4_rx_buffer_pos = DMA_GetCurrDataCounter(DMA1_Stream2);
	
	//USART端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 ; //PA0、PA1、PA2、PA3、PA9、PA10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 ; //test yanly
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0，PA1，PA2，PA3，PA9，PA10
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//复用映射配置
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9, GPIO_AF_USART1); //test yanly
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10, GPIO_AF_USART1); //test yanly
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0, GPIO_AF_UART4);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1, GPIO_AF_UART4);
	
	//USART1、USART2、USART3的初始化设置
	USART_InitStructure.USART_BaudRate = 57600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
	
	
	/***********串口1*********/ //test by yanly
	USART_Init(USART1, &USART_InitStructure);
//	USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE);
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
	
	/***********串口2*********/
	USART_Init(USART2, &USART_InitStructure);
	USART_DMACmd(USART2,USART_DMAReq_Tx,ENABLE);
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
	USART_Cmd(USART2, ENABLE);
	USART_ClearFlag(USART2, USART_FLAG_TC);
	
	/***********串口3*************/
	USART_Init(USART3, &USART_InitStructure);
	USART_DMACmd(USART3,USART_DMAReq_Tx,ENABLE);
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);
	USART_Cmd(USART3, ENABLE);
	USART_ClearFlag(USART3, USART_FLAG_TC);
	
	/***********串口4*************/
	USART_Init(UART4, &USART_InitStructure);
	USART_DMACmd(UART4,USART_DMAReq_Tx,ENABLE);
	USART_DMACmd(UART4,USART_DMAReq_Rx,ENABLE);
	USART_Cmd(UART4, ENABLE);
	USART_ClearFlag(UART4, USART_FLAG_TC);
}

void usart1_tx_copyed(const char *str,uint16_t len)
{
	uint16_t count;
	
	for (count = 0; count < len; count++) 
	{                                     
		usart1_tx_buffer[usart1_tx_buffer_head]= (uint8_t)str[count];
		
		usart1_tx_buffer_head++;
		if (usart1_tx_buffer_head == USART_BUFFER_SIZE)
		{
			usart1_tx_buffer_head = 0;
		}
	}
}

//////test yan
//volatile u8 usart1_txing = 0;
//void usart1_tx_send_msg(uint8_t* msg, uint16_t msg_size)
//{
//	u16 i;
//	while(usart1_txing);
//	DMA_Cmd(DMA2_Stream7, DISABLE);                      //关闭DMA传输 
//	for(i=0; i<msg_size; i++)
//		usart1_tx_buffer[i] = msg[i];
//	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE) //确保DMA可以被设置
//	DMA_SetCurrDataCounter(DMA2_Stream7,msg_size); //数据传输量  
//	DMA_Cmd(DMA2_Stream7, ENABLE);                      //开启DMA传输 
//	usart1_txing = 1;
//}
//void DMA2_Stream7_IRQHandler(void)
//{
//	if(DMA_GetITStatus(DMA2_Stream7,DMA_IT_TCIF7) != RESET)   
//	{
//		DMA_ClearITPendingBit(DMA2_Stream7,DMA_IT_TCIF7); 
//		DMA_Cmd(DMA2_Stream7,DISABLE);
//		usart1_txing = 0;
//	}
//}
#if 0
void usart1_tx_DMA(void)
{
	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE)
	{
	}
	
	DMA2_Stream7->M0AR = (uint32_t)&usart1_tx_buffer[usart1_tx_buffer_tail];
	
	if(usart1_tx_buffer_tail < usart1_tx_buffer_head)
	{
		DMA_SetCurrDataCounter(DMA2_Stream7, usart1_tx_buffer_head - usart1_tx_buffer_tail);
		usart1_tx_buffer_tail = usart1_tx_buffer_head;
	}
	else                    
	{
		DMA_SetCurrDataCounter(DMA2_Stream7, USART_BUFFER_SIZE - usart1_tx_buffer_tail);
		usart1_tx_buffer_tail = 0;
	}

	DMA_ClearFlag(DMA2_Stream7,DMA_FLAG_TCIF7);				
	
	DMA_Cmd(DMA2_Stream7, ENABLE);              
}
 

void DMA2_Stream7_IRQHandler(void)
{
	DMA_Cmd(DMA2_Stream7, DISABLE);
	
	while (DMA_GetCmdStatus(DMA2_Stream7) != DISABLE)	
	{
	}
	
	if (usart1_tx_buffer_tail != usart1_tx_buffer_head)
		usart1_tx_DMA();
	
	DMA_ClearITPendingBit(DMA2_Stream7,DMA_IT_TCIF7);
	
	GPIO_ResetBits(GPIOD, GPIO_Pin_0);
	usart1_tx_flag = TimingDelay;			
}

uint8_t usart1_rx_check(void)
{
	if (usart1_rx_buffer_pos == DMA_GetCurrDataCounter(DMA2_Stream5))
		return 0;
	else
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_1);
		usart1_rx_flag = TimingDelay;			
		
		return 1;
	}
}


#endif
uint8_t usart1_rx_byte(void)
{
	uint8_t ch;	
	
	ch = usart1_rx_buffer[USART_BUFFER_SIZE - usart1_rx_buffer_pos];
	
	usart1_rx_buffer_pos--;
	if (usart1_rx_buffer_pos == 0)
	{
		usart1_rx_buffer_pos = USART_BUFFER_SIZE;
	}

	return ch;
}

//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x)
{ 
	x = x; 
}
int fputc(int ch, FILE *f)
{
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
    ;
  USART_SendData(USART1, (unsigned char) ch);

  return (ch);
}
#endif
