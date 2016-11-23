/*! @file main.cpp
 *  @version 3.1.8
 *  @date Aug 05 2016
 *
 *  @brief
 *  An exmaple program of DJI-onboard-SDK portable for stm32
 *
 *  Copyright 2016 DJI. All right reserved.
 *
 *******************************************************************************
 *                                                                             *
 *          --------               --------                 --------           *
 *         |        |   USART2    |        |    USART3     |        |          *
 *         |   PC   | <---------> | stm32  |  <----------> |  M100  |          *
 *         |        | (USB-TTL)   |        |               |        |          *
 *         |        |             |        |               |        |          *
 *          --------               --------                 --------           *
 *                                                                             *
 *                                                                             *
 *******************************************************************************
 * */

#include "main.h"
#include "stm32f4xx_adc.h"
#include "DJI_API.h"
#include "DJI_Camera.h"
#include "DJI_Type.h"
#include "DJI_VirtualRC.h"
#ifdef __cplusplus
extern "C"
{
#include "sys.h"
#include "adc.h"
#include "usart.h"
#include "zkrt.h"
#include "djiapp.h"
#include "flash.h"
#include "bat.h"
}
#endif //__cplusplus

#undef USE_ENCRYPT
/*-----------------------DJI_LIB VARIABLE-----------------------------*/
using namespace DJI::onboardSDK;

HardDriver* driver = new STM32F4;
CoreAPI defaultAPI = CoreAPI(driver);
CoreAPI *coreApi = &defaultAPI;

Flight flight = Flight(coreApi);

FlightData flightData;
Camera camera=Camera(coreApi);
GimbalSpeedData gimbalSpeedData;
VirtualRC virtualrc = VirtualRC(coreApi);

VirtualRCData myVRCdata =
{ 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024, 1024,
    1024, 1024 };

extern TerminalCommand myTerminal;
extern LocalNavigationStatus droneState;
extern uint8_t myFreq[16];
 zkrt_packet_t main_dji_rev;
uint8_t j=0;
uint8_t djidataformmobile[50]={0};
uint8_t data[50]={0};
uint8_t s=0;

uint8_t msgbuffer[25] = {0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77,0x77};





#ifdef __cplusplus
extern "C" void ADC_SoftwareStartConv(ADC_TypeDef* ADCx);
#endif //__cplusplus


/***********************************************************************
		          �п���̩�������˻���������
		
		���� ���ƣ� ����͸��  
	       ���� ���ܣ�
		���� ��Σ�
		��������ֵ��
		˵     ����

************************************************************************/

extern "C" void sendToMobile(uint8_t *data, uint8_t len)
	   {
             coreApi->sendToMobile(data,  len);//����͸��������վ���
		GPIO_ResetBits(GPIOD, GPIO_Pin_0);
	      usart1_tx_flag = TimingDelay;
           }

extern "C" void sendpoll()
	   {
             coreApi->sendPoll();//
           }


void copydataformmobile()
{
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
for(j=0;j<6;j++)
	{
	main_dji_rev.UAVID[j]=djidataformmobile[10+j];
	}
main_dji_rev.command=djidataformmobile[17];
 for(j=0;j<30;j++)
	{
	main_dji_rev.data[j]=djidataformmobile[17+j];
	}
 main_dji_rev.crc=djidataformmobile[47];
main_dji_rev.crc|=djidataformmobile[48]<<8;

main_dji_rev.end_code=djidataformmobile[49];

  }



int main()
{
  BSPinit();
   delay_nms(20000);
  printf("This is the example App to test DJI onboard SDK on STM32F4Discovery Board! \r\n");
  printf("Refer to \r\n");
  printf("https://developer.dji.com/onboard-sdk/documentation/github-platform-docs/STM32/README.html \r\n");
  printf("for supported commands!\r\n");
  printf("Board Initialization Done!\r\n");


  //! Change the version string to your platform/version as defined in DJI_Version.h
  coreApi->setVersion(versionA3_31);
  delay_nms(200);
  printf("API Version Set Done!\r\n");

  uint32_t runOnce = 1;
  uint32_t next500MilTick;
  uint16_t cm;
  while (1)
  {
    // One time automatic activation
    if (runOnce)
    {
      runOnce = 0;
      coreApi->setBroadcastFreq(myFreq);
      delay_nms(50);

      // The Local navigation example will run in broadcast call back function,
      // immediate after GPS position is updated
      coreApi->setBroadcastCallback(myRecvCallback,(DJI::UserData)(&droneState));

      User_Activate();      
      delay_nms(50);

      next500MilTick = driver->getTimeStamp() + 500;
    }

  //   virtualrc.sendData(myVRCdata);
   // virtualrc.setControl(0,virtualrc.CutOff_ToLogic);

    if (driver->getTimeStamp() >= next500MilTick)
    {
      next500MilTick = driver->getTimeStamp() + 500;

      // Handle user commands from mobile device
      mobileCommandHandler(coreApi, &flight);

      // Handle user commands from serial (USART2)
   //   myTerminal.terminalCommandHandler(coreApi, &flight);
    }

    coreApi->sendPoll();


#if 1
	  //��ȡ�ӵ���վ���������
	if(djidataformmobile[1]!=0)
	{
	copydataformmobile();		 
	  main_dji_recv();
		djidataformmobile[1]	  =0; 	
	 }	 
	main_zkrt_dji_recv();	/*����ģ��ͨ��CAN�������ݣ�����������Ͷ������䵽���������������λ��һ*/

#endif

if (_160_read_flag - TimingDelay >= 160)
	{
		    _160_read_flag = TimingDelay;
			ADC_SoftwareStartConv(ADC1); /*����ADC*/	
	         printf("ADC_SoftwareStartConv!\r\n");	
                  if ((_read_count%2) == 0)									
			{
		
				zkrt_dji_read_heart_tempture();  /*��ȡ�¶ȴ���������*/
				if(((tempture0>0)||(tempture1>0))&&(s==0))
				{
//				printf("####################!\r\n");
	//			coreApi->getObtainControlMobileCMD();

//					printf("111111111111111111111111111!\r\n");
	//			coreApi->getTakeOffMobileCMD();
  //                                printf("2222222222222222222222222!\r\n");
   //                          printf("mobileCommandHandler!\r\n");	
         //                  mobileCommandHandler(coreApi, &flight);
	//					   printf("333333333333333333333!\r\n");
		//				     delay_nms(1000);
			//	coreApi->getObtainControlMobileCMD_dji();
			//	 printf("44444444444444444444444!\r\n");
			//	coreApi->getTakeOffMobileCMD_dji();
	//			 printf("55555555555555555555!\r\n");
                  //          delay_nms(5000);
				virtualrc.setControl(1,virtualrc.CutOff_ToRealRC);
				myVRCdata=virtualrc.getVRCData();

	//		printf("myVRCdata. roll= %d\r\n",myVRCdata.roll);
	//		printf("myVRCdata.pitch= %d\r\n",myVRCdata.pitch);
	//		printf("myVRCdata.throttle= %d \r\n",myVRCdata.throttle);
	//		printf("myVRCdata.yaw= %d\r\n",myVRCdata.yaw);
	//		printf("myVRCdata.gear= %d\r\n",myVRCdata.gear);
	//		printf("myVRCdata.reserved= %d\r\n",myVRCdata.reserved);
	//		printf("myVRCdata.mode= %d\r\n",myVRCdata.mode);
	//		printf("myVRCdata.Channel_07= %d\r\n",myVRCdata.Channel_07);
	//		printf("myVRCdata.Channel_08= %d\r\n",myVRCdata.Channel_08);
	//		printf("myVRCdata.Channel_09= %d\r\n",myVRCdata.Channel_09);
	//		printf("myVRCdata.Channel_10=%d\r\n",myVRCdata.Channel_10);
	//		printf("myVRCdata.Channel_11=%d\r\n",myVRCdata.Channel_11);
	//		printf("myVRCdata.Channel_12= %d\r\n",myVRCdata.Channel_12);
	//		printf("myVRCdata.Channel_13= %d\r\n",myVRCdata.Channel_13);
	//		printf("myVRCdata.Channel_14=  %d\r\n",myVRCdata.Channel_14);
	//		printf("myVRCdata.Channel_15=  %d\r\n",myVRCdata.Channel_15);
                                         myVRCdata.throttle=1500;
	//			printf("myVRCdata.throttle= %d \r\n",myVRCdata.throttle);	
				virtualrc.sendData(myVRCdata);
	//			 printf("777777777777777777777777!\r\n");
	//			coreApi->getReleaseControlMobileCMD();
          //                mobileCommandHandler(coreApi, &flight);
	//			coreApi->getReleaseControlMobileCMD_dji();
		//		s=1;
                            }
				if((tempture0<0)&&(tempture1<0))
					s=1;
				
					if (MAVLINK_TX_INIT_VAL - TimingDelay >= 4000)	
				{					
					dji_zkrt_read_heart_tempture_check();	/*���¶ȴ�����������䵽���������棬���ж������Ƿ�����*/	
				}
			}
			
	if ((_read_count%10) == 0)								
			{
				
				dji_bat_value_roll(); /*��ȡ���ܵ�����ݣ�����䵽���ܵ������������*/
			dji_zkrt_read_heart_vol(); /*��ȡ���ص�ѹ����ֵ*/
			
				if (MAVLINK_TX_INIT_VAL - TimingDelay >= 4000)	
				{
			    dji_zkrt_read_heart_vol_check();	/*�Ե�ǰ���ص�ѹ����ֵ�����жϣ���������Ӧ�������������䵽������*/					
				}
			}
			_read_count++;

		}

		if (MAVLINK_TX_INIT_VAL - TimingDelay >= 5000)	
         {
			if ((mavlink_send_flag-TimingDelay) < 50)		
			{
				GPIO_ResetBits(GPIOC, GPIO_Pin_0);
			}
			else if ((mavlink_send_flag-TimingDelay) < 800)
			{
				GPIO_SetBits(GPIOC, GPIO_Pin_0);
			}
			else if ((mavlink_send_flag-TimingDelay) >= 800)
			{
			     mavlink_send_flag = TimingDelay;
			#if 1
				switch (mavlink_type_flag_dji)									
				{
					case 0:
						mavlink_type_flag_dji = 1; 
						dji_zkrt_read_heart_ack(); /*������յ����ݰ������ҷ��ͳ���*/
						coreApi->sendPoll(); 
						break;
					case 1:
						mavlink_type_flag_dji = 0;
						dji_bat_value_send();  /*�������ܵ�����ݣ��ܹ�32���ֽ�*/
						coreApi->sendPoll();
						break;
				}
                      #endif 
					printf("T1 = %d T2 = %d  ADC1_25_dji=%d  ADC1_5_dji=%d  ADC1_I_dji=%d   LOW_VALUE = %d HIGH_VALUE = %d STA1 = %x STA2 = %x\r\n", 
				tempture0, tempture1, ADC1_25_dji,ADC1_5_dji,ADC1_I_dji,glo_tempture_low, glo_tempture_high, msg_smartbat_dji_buffer[0], 
				msg_smartbat_dji_buffer[3]);
			}			
		}

			if ((usart1_tx_flag-TimingDelay) >= 50)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_0);
		}
		
		if ((usart1_rx_flag-TimingDelay) >= 50)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_1);
		}
		
		if ((can_rx_flag-TimingDelay)  >= 50)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_4);
		}
		
		if ((can_tx_flag-TimingDelay)  >= 50)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_5);
		}
		
		if ((posion_recv_flag-TimingDelay)  >= 5000)				
		{
			memset((void *)(msg_smartbat_dji_buffer+10), 0, 13);
			msg_smartbat_dji_buffer[23] &= 0XEF;					
		}
		 
		if ((throw_recv_flag-TimingDelay)  >= 5000)
		{
			msg_smartbat_dji_buffer[23] &= 0XDF;			
		}
		if ((camera_recv_flag-TimingDelay) >= 5000)
		{
			msg_smartbat_dji_buffer[23] &= 0XF7;	
		}
if ((flash_buffer._tempture_low != glo_tempture_low)||(flash_buffer._tempture_high != glo_tempture_high))//�����ｫ���е�ֵͳһ���£�����flashд��̫ռʱ����ܵ���д�����
		{
		flash_buffer._tempture_low  = glo_tempture_low;				//�����������ñ�����������
		flash_buffer._tempture_high = glo_tempture_high;
			STMFLASH_Write();											//����������дflash
		}

		
		IWDG_Feed();

  }
}

