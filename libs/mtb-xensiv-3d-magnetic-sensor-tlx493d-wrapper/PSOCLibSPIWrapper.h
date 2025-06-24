#ifndef PSOCLIBSPIWRAPPER_H_
#define PSOCLIBSPIWRAPPER_H_

#include <stdbool.h>
#include <stdint.h>

#include "tlx493d_types.h"

#define SPI_FREQ 1000000 // 1MHz

/**
 * @brief Initializes the SPI interface for the TLx493D sensor.
 *
 * This function sets up the SPI communication parameters and prepares the
 * specified TLx493D sensor instance for SPI communication.
 *
 * @param sensor Pointer to a TLx493D_t structure representing the sensor to initialize.
 * @return true if the SPI initialization was successful, false otherwise.
 */
bool tlx493d_psoc_initSPI(TLx493D_t *sensor);

/**
 * @brief Deinitializes the SPI interface for the TLx493D sensor.
 *
 * This function releases any resources and performs necessary cleanup
 * to properly deinitialize the SPI communication with the specified TLx493D sensor.
 *
 * @param sensor Pointer to the TLx493D_t structure representing the sensor instance.
 * @return true if the deinitialization was successful, false otherwise.
 */
bool tlx493d_psoc_deinitSPI(TLx493D_t *sensor);

/**
 * @brief Transfers data over SPI for the TLx493D sensor using the PSOC SPI wrapper.
 *
 * This function sends data from the provided transmit buffer (txBuffer) and receives data into the receive buffer (rxBuffer)
 * using the SPI interface. The lengths of the transmit and receive operations are specified by txLen and rxLen, respectively.
 *
 * @param sensor   Pointer to the TLx493D sensor structure.
 * @param txBuffer Pointer to the buffer containing data to transmit.
 * @param txLen    Number of bytes to transmit.
 * @param rxBuffer Pointer to the buffer to store received data.
 * @param rxLen    Number of bytes to receive.
 * @return true if the SPI transfer was successful, false otherwise.
 */
bool tlx493d_psoc_transferSPI(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen);

/**
 * @brief Sets the I2C read address for the TLx493D sensor via SPI.
 *
 * This function configures the TLx493D sensor to use the specified I2C address
 * for subsequent read operations, communicating through the SPI interface.
 *
 * @param sensor Pointer to the TLx493D_t sensor structure.
 * @param address The 7-bit I2C address to set for read operations.
 */
void tlx493d_psoc_setReadAddressSPI(TLx493D_t *sensor, uint8_t address);

#endif /* PSOCLIBSPIWRAPPER_H_ */
