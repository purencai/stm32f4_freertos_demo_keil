#include "system.h"
#include "usertask.h"
#include "uarttask.h"

#define USART_TASK_PRIORITY      3

#define USART_TASK_STACK_DEPTH      512

void AppTaskCreate()
{
	create_queue_semaphore();
	xTaskCreate( (TaskFunction_t)usart_task, /* Pointer to the function that implements the task. */
                 "vUsart",   /* Text name for the task.  This is to facilitate debugging only.    */
                 USART_TASK_STACK_DEPTH,        /* Stack depth in words.                         */
                 NULL,       /* We are not using the task parameter.                             */
                 USART_TASK_PRIORITY,          /* This task will run at priority 1.              */
                 NULL );     /* We are not using the task handle.                                */
}
