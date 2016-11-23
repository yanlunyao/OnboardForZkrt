#ifndef __USART_H
#define __USART_H
#include "sys.h"

#define USART_BUFFER_SIZE 295 

extern uint16_t usart1_tx_buffer_tail;
extern uint16_t usart1_tx_buffer_head;
																		

void uart_init(void);

void usart1_tx_copyed(const char *str,uint16_t len);
void usart1_tx_DMA(void);

uint8_t usart1_rx_check(void);
uint8_t usart1_rx_byte(void);
#endif


