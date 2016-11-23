#ifndef __ADC_H
#define __ADC_H	
#include "sys.h" 

#if defined _TEMPTURE_IO_
#define ADC_BUFFER_SIZE   30 
#elif defined _TEMPTURE_ADC_
#define ADC_BUFFER_SIZE   50 
#endif

#define _25V_value 0
#define _5V_value  1
#define _5A_value  2
#define _T1_value  3
#define _T2_value  4

void ADC1_Init(void); 				//ADC通道初始化
uint16_t ADC1_get_value(uint8_t read_type);

#endif 















