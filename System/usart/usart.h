#ifndef __USART_H
#define __USART_H

#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 

#define DEBUG_USART  USART1

void debug_usart_init(uint32_t bound);
void uart_putchar(USART_TypeDef* USARTn,char ch);
void uart_putstr(USART_TypeDef* USARTn,const char *fmt,...);
void uart_puts(USART_TypeDef* USARTn,const char *buff,uint16_t length);

#endif
