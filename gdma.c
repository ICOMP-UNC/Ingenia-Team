/**
 * @file gdma.c
 * @brief Configuración de DMA para trabajar con ADC, DAC y UART en LPC1769.
 */

#include "LPC17xx.h"
#include "lpc17xx_gpdma.h"
#include "dac.h"
#include "uart.h"

/* Definitions */
#define DMA_BUFFER_SIZE 60  // Tamaño de buffer ajustado a la tabla de onda

/* Global Variables */
static uint32_t dac_waveform_table[DMA_BUFFER_SIZE]; /* Tabla de onda triangular para el DAC */
static uint16_t adc_dma_buffer[DMA_BUFFER_SIZE];     /* Buffer para datos de ADC */

/* Function declarations */
void dma_setup(void);
void transfer_adc_to_uart(uint8_t channel);

/**
 * @brief Configura el DMA para transferencias de ADC a memoria y DAC.
 */
void dma_setup(void)
{
    /* Inicializa la tabla de onda para el DAC */
    create_waveform_table(dac_waveform_table, DMA_BUFFER_SIZE);

    /* Inicializa el controlador de DMA */
    GPDMA_Init();

    /* Configura el DMA para transferencia de onda triangular al DAC */
    GPDMA_Channel_CFG_Type dma_dac_config;
    dma_dac_config.ChannelNum = 1;
    dma_dac_config.SrcMemAddr = (uint32_t)dac_waveform_table;
    dma_dac_config.DstMemAddr = 0;
    dma_dac_config.TransferSize = DMA_BUFFER_SIZE;
    dma_dac_config.TransferWidth = 0;
    dma_dac_config.TransferType = GPDMA_TRANSFERTYPE_M2P;
    dma_dac_config.SrcConn = 0;
    dma_dac_config.DstConn = GPDMA_CONN_DAC;
    dma_dac_config.DMALLI = 0;

    GPDMA_Setup(&dma_dac_config);
    GPDMA_ChannelCmd(1, ENABLE);

    /* Configura el DMA para transferencia desde el ADC canal 0 a memoria */
    GPDMA_Channel_CFG_Type dma_adc_config;
    dma_adc_config.ChannelNum = 0;
    dma_adc_config.SrcMemAddr = 0;
    dma_adc_config.DstMemAddr = (uint32_t)adc_dma_buffer;
    dma_adc_config.TransferSize = DMA_BUFFER_SIZE;
    dma_adc_config.TransferWidth = 0;
    dma_adc_config.TransferType = GPDMA_TRANSFERTYPE_P2M;
    dma_adc_config.SrcConn = GPDMA_CONN_ADC;
    dma_adc_config.DstConn = 0;
    dma_adc_config.DMALLI = 0;

    GPDMA_Setup(&dma_adc_config);
    GPDMA_ChannelCmd(0, ENABLE);
}

/**
 * @brief Transfiere datos del ADC al UART.
 * @param channel Canal de ADC para lectura y envío (0 o 1).
 */
void transfer_adc_to_uart(uint8_t channel)
{
    uint16_t data_to_send = adc_dma_buffer[channel];
    uart_send(data_to_send);  // Envía el dato por UART
}
