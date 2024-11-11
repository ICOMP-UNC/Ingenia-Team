/**
 * @file uart.c
 * @brief Configuración de UART para transmisión de datos en LPC1769.
 */

#include "LPC17xx.h"
#include "lpc17xx_uart.h"

/**
 * @brief Inicializa el UART0 para la comunicación.
 */
void uart_init(void)
{
    UART_CFG_Type uartConfigStruct;
    UART_FIFO_CFG_Type uartFIFOConfigStruct;

    UART_ConfigStructInit(&uartConfigStruct);
    uartConfigStruct.Baud_rate = 9600;  // Configuración de baudrate

    UART_Init(LPC_UART0, &uartConfigStruct);
    UART_FIFOConfigStructInit(&uartFIFOConfigStruct);
    UART_FIFOConfig(LPC_UART0, &uartFIFOConfigStruct);
    UART_TxCmd(LPC_UART0, ENABLE);  // Habilita transmisión
}

/**
 * @brief Envía un valor por UART.
 * @param data Valor de 16 bits a enviar.
 */
void uart_send(uint16_t data)
{
    char buffer[10];
    sprintf(buffer, "%d\n", data);
    UART_Send(LPC_UART0, (uint8_t *)buffer, strlen(buffer), BLOCKING);
}