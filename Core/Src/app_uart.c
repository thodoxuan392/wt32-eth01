/*
* app_uart.c
* @brief UART: UART1 for log, uart 2 for ethernet
*  Created on: Nov 16, 2022
*      Author: xuanthodo
*/
#include "main.h"
#include "app_uart.h"

#define UART_BUFFER_MAX 2048

UART_HandleTypeDef huart2;

// UART Ethernet
static uint8_t uart_ethernet_interrupt_data;
static uint8_t uart_ethernet_buffer[2048];
static uint8_t uart_ethernet_head = 0;
static uint8_t uart_ethernet_tail = 0;
static uint8_t uart_ethernet_transmit_done_flag = 1;


void UART_Init(){
	// Init UART1
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
	Error_Handler();
	}
	HAL_UART_Receive_IT(&huart2, &uart_ethernet_interrupt_data, 1);


}

uint8_t UART_Ethernet_isAvailable(){
	if(uart_ethernet_head != uart_ethernet_tail){
		return 1;
	}
	return 0;
}
uint8_t UART_Ethernet_ByteRead(){
	uint8_t temp;
	temp = uart_ethernet_buffer[uart_ethernet_tail];
	uart_ethernet_tail = (uart_ethernet_tail + 1) %UART_BUFFER_MAX;
	return temp;
}
void UART_Ethernet_BytesWrite(uint8_t* data , uint16_t data_len){
	while(!uart_ethernet_transmit_done_flag);
	HAL_UART_Transmit_IT(&huart2, data, data_len);
	uart_ethernet_transmit_done_flag = 0;
}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef* uart){
	if(uart->Instance == USART2){
		uart_ethernet_buffer[uart_ethernet_head] = uart_ethernet_interrupt_data;
		uart_ethernet_head = (uart_ethernet_head + 1) % UART_BUFFER_MAX;
		HAL_UART_Receive_IT(&huart2, &uart_ethernet_interrupt_data, 1);
	}

}


void HAL_UART_TxCpltCallback(UART_HandleTypeDef *uart){
	if(uart->Instance == USART2){
		uart_ethernet_transmit_done_flag = 1;
	}
}





