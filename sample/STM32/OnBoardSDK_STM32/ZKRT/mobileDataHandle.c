/*
 *	File name   : mobile_data_handle.c
 *  Created on  : 
 *  Author      : 
 *  Description :
 *  Version     :
 *  History     : <author>		<time>		<version>		<desc>
 */

#include "sys.h"
#include "adc.h"
#include "usart.h"
#include "zkrt.h"
#include "djiapp.h"
#include "flash.h"
#include "bat.h"
#include "mobileDataHandle.h"

/////////////////////////////////////////////////////////////////////valible define 
uint8_t djidataformmobile[50]= {0};
zkrt_packet_t main_dji_rev;

////////////////////////////////////////////////////////////////////static function define
static void main_dji_recv(void);
static void copydataformmobile(void);

/*
* @brief 将接收到的mobile数据进行解析处理
	mobile数据来源是DJI串口透传数据，经过UART1中断接收解析处理过，拷贝到数组djidataformmobile[]
*/
void mobile_data_process(void)
{
	//获取从地面站软件的数据
	if(djidataformmobile[1]!=0)
	{
		copydataformmobile();
		main_dji_recv();
		djidataformmobile[1] =0;
	}
}
/***********************************************************************
		          中科瑞泰消防无人机函数定义

		函数 名称：接收处理函数
	       函数 功能：
		函数 入参：
		函数返回值：
		说     明：

************************************************************************/
void main_dji_recv(void)
{
	int k;
	//memcpy((void *)&main_dji_rev, (void *)&(Rx_buff[5]), 40);
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

  for(k=0; k<30; k++)
  {
    printf("main_dji_rev.data[%d]=0x %x\r\n",k,main_dji_rev.data[k]);
  }
  printf("main_dji_rev.crc=0x %x\r\n",main_dji_rev.crc);
  printf("main_dji_rev.end_code=0x %x\r\n",main_dji_rev.end_code);

  if (main_dji_rev.UAVID[3] == DEVICE_TYPE_TEMPERATURE) /*设置温度最低值和最高值*/
  {
    printf("&&&&&&&&&&&&&&\r\n");
    glo_tempture_low =  ((main_dji_rev.data[1])<<8)+(main_dji_rev.data[0]);
    glo_tempture_high = ((main_dji_rev.data[3])<<8)+(main_dji_rev.data[2]);
  }
  else if (main_dji_rev.UAVID[3] == DEVICE_TYPE_BAOSHAN)/*设置爆闪灯*/
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
    //CAN1_send_message_fun((uint8_t *)(&main_dji_rev), _TOTAL_LEN, (main_dji_rev.UAVID[3]));/*通过CAN总线发送数据*/
    CAN1_send_message_fun((uint8_t *)(&main_dji_rev), _TOTAL_LEN, 0x6);/*通过CAN总线发送数据*/
  }
}
/* 
* @brief: mobile数组数据 转存到 zkrt_packet_t格式的全局结构体里
*/
void copydataformmobile(void)
{
	u32 j;
  main_dji_rev.start_code=djidataformmobile[0];
  main_dji_rev.ver=djidataformmobile[1];
  main_dji_rev.session_ack=djidataformmobile[2];
  main_dji_rev.padding_enc=djidataformmobile[3];
  main_dji_rev.cmd=djidataformmobile[4];
  main_dji_rev.length=djidataformmobile[5];
  main_dji_rev.seq=djidataformmobile[6];
  main_dji_rev.APPID[0]=djidataformmobile[7];
  main_dji_rev.APPID[1]=djidataformmobile[8];
  main_dji_rev.APPID[2]=djidataformmobile[9];
  for(j=0; j<6; j++)
  {
    main_dji_rev.UAVID[j]=djidataformmobile[10+j];
  }
  main_dji_rev.command=djidataformmobile[17];
  for(j=0; j<30; j++)
  {
    main_dji_rev.data[j]=djidataformmobile[17+j];
  }
  main_dji_rev.crc=djidataformmobile[47];
  main_dji_rev.crc|=djidataformmobile[48]<<8;
  main_dji_rev.end_code=djidataformmobile[49];
}
