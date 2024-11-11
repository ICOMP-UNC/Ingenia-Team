/**
 * @file dac.c
 * @brief File to handle the DAC module
 *        Include the generation of a triagular wave thats continuosly coming out of the dac
*/

#include "LPC17xx.h"
#include "lpc17xx_dac.h"

// Definitions
#define NUM_SAMPLES      60 // Total number of samples for the triangular wave
#define WAVE_FREQUENCY   60 // Triangular wave frequency: 60 Hz
#define CLOCK_DAC_MHZ    25 // DAC clock: 25 MHz (CCLK divided by 4)
#define TRUE             1

// Function Prototypes

/**
 * @brief Initialize and configure the DAC.
 */
void setup_dac(void);

/**
 * @brief Create a triangular wave table for the DAC using 60 samples.
 * @param table Pointer to the DAC waveform table
 * @param num_samples Number of samples in the waveform
 */
void create_waveform_table(uint32_t* table, uint32_t num_samples);

void setup_dac(void)
{
    DAC_CONVERTER_CFG_Type DAC_Struct;
    uint32_t update_interval;

    // Configure DAC settings
    DAC_Struct.CNT_ENA = SET; // Enable DAC counter mode (timeout mode)
    DAC_Struct.DMA_ENA = SET; // Enable DAC DMA mode
    DAC_Init(LPC_DAC);        // Initialize the DAC

    // Calculate sample update interval for the desired waveform frequency
    update_interval = (CLOCK_DAC_MHZ * 1000000) / (WAVE_FREQUENCY * NUM_SAMPLES);
    DAC_SetDMATimeOut(LPC_DAC, update_interval); // Set the DAC timeout between samples

    // Apply the DAC configuration
    DAC_ConfigDAConverterControl(LPC_DAC, &DAC_Struct);
}

void create_waveform_table(uint32_t* table, uint32_t num_samples)
{
    uint32_t i;
    uint32_t peak_value = 1023;  // Max DAC value for 3.3V (10 bits)
    uint32_t step = peak_value / (num_samples / 2); // Step size for each sample

    // Fill the table with values for a triangular wave
    for (i = 0; i < num_samples / 2; i++) {
        table[i] = i * step;  // Rising part of the wave
    }
    for (i = num_samples / 2; i < num_samples; i++) {
        table[i] = peak_value - ((i - num_samples / 2) * step); // Falling part of the wave
    }
}
