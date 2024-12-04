/*
 * uart.h
 *
 *  Created on: 14 nov. 2024
 *      Author: juanp
 */

#ifndef UART_H_
#define UART_H_

void uart_init(void);
void uart_send(uint16_t data);
void transfer_adc_to_uart(void);

#endif /* UART_H_ */
