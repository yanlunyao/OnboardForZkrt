#ifndef __LED_H
#define __LED_H
#include "sys.h"	    

/*
PC0��RUN
PC1��ALRM
PC2��H/S
PD0��USART1_TX
PD1��USART1_RX
PD2��USART2_TX
PD3��USART2_RX
PD4��CAN1_RX
PD5��CAN1_TX

PA8����Ӧ5V��ѹ��ʹ�ܡ�0�رգ�1ʹ��
PE2����Ӧ����ģ��1�Ĺ���ʹ�ܡ�0�رգ�1ʹ��
PE9����Ӧ����ģ��2�Ĺ���ʹ�ܡ�0�رգ�1ʹ��
*/

#define	LED_LIGHT                0
#define	LED_DARK                 1

#define _RUN_LED                                  PCout(0)
#define _ALARM_LED                                PCout(1)
#define _HS_LED                                   PCout(2)
#define _DJI_UART_TX_LED                          PDout(0)  
#define _DJI_UART_RX_LED                          PDout(1)
#define _TEST_UART_TX_LED                         PDout(2)
#define _TEST_UART_RX_LED                         PDout(3)
#define _CAN1_RX_LED                              PDout(4)
#define _CAN1_TX_LED                              PDout(5)

void led_init(void);
void led_test(void);

#endif

















