/*
* app_uart.h
*
*  Created on: Nov 16, 2022
*      Author: xuanthodo
*/

#ifndef INC_APP_UART_H_
#define INC_APP_UART_H_

void UART_Init();

uint8_t UART_Logger_isAvailable();
uint8_t UART_Logger_ByteRead();
void UART_Logger_BytesWrite(uint8_t* data , uint16_t data_len);



uint8_t UART_Ethernet_isAvailable();
uint8_t UART_Ethernet_ByteRead();
void UART_Ethernet_BytesWrite(uint8_t* data , uint16_t data_len);

#endif /* INC_APP_UART_H_ */
