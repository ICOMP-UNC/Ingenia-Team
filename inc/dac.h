/*
 * dac.h
 *
 *  Created on: 14 nov. 2024
 *      Author: juanp
 */

#ifndef DAC_H_
#define DAC_H_

#define NUM_SAMPLES      100   // Total number of samples for the triangular wave
#define WAVE_FREQUENCY   60   // Triangular wave frequency: 60 Hz
#define CLOCK_DAC_MHZ    25   // DAC clock: 25 MHz (CCLK divided by 4)

void setup_dac(void);
//void create_waveform_table(uint32_t* table, uint32_t num_samples);

#endif /* DAC_H_ */
