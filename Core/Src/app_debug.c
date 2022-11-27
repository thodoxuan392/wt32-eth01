#include "main.h"
#include "app_debug.h"
#include "string.h"
#include "stdarg.h"

static UART_HandleTypeDef huart1;
static log_level_t level;
static uint8_t log_buffer[MAX_LOG_BUFFER];
static uint8_t message_buffer[MAX_LOG_BUFFER];


static const char * level_str[] = {
		"OFF",
		"FATAL",
		"ERROR",
		"WARN",
		"INFO",
		"DEBUG",
		"TRACE",
		"ALL"
};

static char * level_to_str(log_level_t level){
    return level_str[level];
}

void APPDEBUG_init(log_level_t _level){
    // Init UART2
	huart1.Instance = USART1;
	huart1.Init.BaudRate = 115200;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
	Error_Handler();
	}
    level = _level;
}



void APPDEBUG_log_log(log_level_t _level, const char *file, int line, const char *fmt, ...){
    va_list args;
    if(_level > level){
        return;
    }
    // Time LOG_LEVEL FILE:LINE: [Message]
    va_start(args, fmt);
    va_end(args);
    vsnprintf(message_buffer , MAX_LOG_BUFFER , fmt, args);
    int size = snprintf(log_buffer , MAX_LOG_BUFFER, "%d [%s] %s:%d: %s\r\n" , HAL_GetTick() , level_to_str(_level) , file, line, message_buffer);
    HAL_UART_Transmit(&huart1, log_buffer, size , 0xFF);
}
