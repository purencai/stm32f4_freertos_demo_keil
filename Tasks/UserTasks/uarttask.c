#include "system.h"
#include "uarttask.h"

void usart_task(void *pvParameters)
{
    while(1)
    {
        LOG("uart_task\r\n");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
