#include "sys.h"
#include "usart.h"	
#include "stdarg.h"	 
#include "string.h"

//DEBUG串口 USART1  PA8/9

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	DEBUG_USART->DR = (u8) ch;    
    while((DEBUG_USART->SR&0X40)==0);//循环发送,直到发送完毕  
	return ch;
}

void debug_usart_init(uint32_t bound)
{

    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

    USART_DeInit(USART1);

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
	
    USART_Cmd(USART1, ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
__forceinline void uart_putchar(USART_TypeDef* USARTn, char ch)
{
	while( (USARTn->SR & 0X40) == 0 );
	USARTn->DR = ch;
}
char usart_tx_buf[1024];
void uart_putstr(USART_TypeDef* USARTn,const char *fmt,...)
{
	uint16_t i = 0;
    uint16_t j = 0;
	va_list ap;
	va_start(ap, fmt);
	vsprintf(usart_tx_buf, fmt,ap);
	va_end(ap);
	i=strlen((const char*)usart_tx_buf);
	for(j=0;j<i;j++)
	{
        uart_putchar(USARTn, usart_tx_buf[j]);
	}    
}
void uart_puts(USART_TypeDef* USARTn, const char *buff, uint16_t length)
{
	uint16_t i = 0;
	for(i=0;i<length;i++)
	{
        uart_putchar(USARTn,buff[i]);
	}
}
void USART1_IRQHandler(void)
{
   if ( USART_GetITStatus( USART1, USART_IT_RXNE ) != RESET )
   {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
   } 
}
