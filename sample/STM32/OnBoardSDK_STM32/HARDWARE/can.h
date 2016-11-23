#ifndef __CAN_H
#define __CAN_H

#include "sys.h"	    

#define CAN_BUFFER_SIZE 250  

uint8_t CAN1_Mode_Init(uint8_t mode);
    
void CAN1_RX0_IRQHandler(void);

uint8_t CAN1_rx_check(uint8_t device_type);
uint8_t CAN1_rx_byte(uint8_t can1_rx_type);

uint8_t CAN1_send_msg(uint8_t* msg, uint8_t len, uint8_t id);					
uint8_t CAN1_send_message_fun(uint8_t *message, uint8_t len, uint8_t id);
#endif

















