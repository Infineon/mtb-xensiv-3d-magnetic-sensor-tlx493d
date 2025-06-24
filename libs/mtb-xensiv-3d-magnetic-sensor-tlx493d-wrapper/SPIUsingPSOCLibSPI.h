#ifndef SPIUSINGPSOCLIBSPI_H
#define SPIUSINGPSOCLIBSPI_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cyhal.h"

#include "tlx493d_types.h"

/**
 * @brief Initializes SPI communication for the TLx493D sensor using the PSoC HAL SPI library.
 *
 * This function sets up the SPI interface and configures the necessary GPIO pins and clock for communication
 * with the TLx493D sensor. It allows specifying the SPI mode, bit width, and whether the device operates as a slave.
 *
 * @param sensor      Pointer to the TLx493D sensor structure to initialize.
 * @param mSPI        Pointer to the cyhal_spi_t SPI object to be initialized.
 * @param mosi        GPIO pin to be used for MOSI (Master Out Slave In).
 * @param miso        GPIO pin to be used for MISO (Master In Slave Out).
 * @param sclk        GPIO pin to be used for SCLK (Serial Clock).
 * @param cs          GPIO pin to be used for Chip Select (CS).
 * @param clk         Pointer to the clock configuration to be used for SPI.
 * @param bits        Number of bits per SPI frame (e.g., 8 or 16).
 * @param mode        SPI mode (clock polarity and phase) as defined by cyhal_spi_mode_t.
 * @param is_slave    Set to true if the device should operate as an SPI slave, false for master mode.
 *
 * @return true if initialization was successful, false otherwise.
 */
bool tlx493d_initPSOCSPICommunication(TLx493D_t *sensor, cyhal_spi_t *mSPI , cyhal_gpio_t mosi, cyhal_gpio_t miso, cyhal_gpio_t sclk, cyhal_gpio_t cs,
                                       const cyhal_clock_t *clk, uint8_t bits, cyhal_spi_mode_t mode, bool is_slave, bool execute_init);

#endif //SPIUSINGPSOCLIBSPI_H


