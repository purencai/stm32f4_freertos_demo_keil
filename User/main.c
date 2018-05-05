#include "system.h"
#include "usertask.h" 

#include "delay.h"
#include "usart.h"

int main(void)
{ 
    //NVIC_SetVectorTable( NVIC_VectTab_FLASH, 0x20000 );
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    //portENABLE_INTERRUPTS();
    delay_init();
    debug_usart_init(921600);

	AppTaskCreate();

    vTaskStartScheduler();

    while(1)
    {  
    } 		
}
