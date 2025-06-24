#ifndef PSCO_LIB_IIC_WRAPPER_H_
#define PSCO_LIB_IIC_WRAPPER_H_

#include "tlx493d_types.h"

/**
 * @brief Initializes the I2C interface for the TLx493D sensor.
 *
 * This function sets up the necessary I2C configuration and prepares the TLx493D sensor
 * for communication over the I2C bus. It should be called before any other operations
 * involving the sensor.
 *
 * @param sensor Pointer to a TLx493D_t structure representing the sensor instance.
 * @return true if initialization was successful, false otherwise.
 */
bool tlx493d_psoc_initIIC(TLx493D_t *sensor);

/**
 * @brief Deinitializes the I2C interface for the specified TLx493D sensor.
 *
 * This function releases any resources and performs necessary cleanup
 * to properly deinitialize the I2C communication for the given TLx493D sensor instance.
 *
 * @param sensor Pointer to the TLx493D_t sensor structure to deinitialize.
 * @return true if the deinitialization was successful, false otherwise.
 */
bool tlx493d_psoc_deinitIIC(TLx493D_t *sensor);

/**
 * @brief Transfers data over I2C for the TLx493D sensor using the PSOC IIC wrapper.
 *
 * This function handles both transmitting and receiving data to/from the TLx493D sensor
 * via the I2C interface. It sends the data in txBuffer and receives data into rxBuffer.
 *
 * @param sensor   Pointer to the TLx493D sensor structure.
 * @param txBuffer Pointer to the buffer containing data to transmit.
 * @param txLen    Number of bytes to transmit from txBuffer.
 * @param rxBuffer Pointer to the buffer to store received data.
 * @param rxLen    Number of bytes to receive into rxBuffer.
 * @return true if the transfer was successful, false otherwise.
 */
bool tlx493d_psoc_transferIIC(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen);

/**
 * @brief Sets the I2C read address for the TLx493D sensor.
 *
 * This function configures the specified TLx493D sensor instance to use the provided
 * I2C address for subsequent read operations. It is typically used when multiple sensors
 * are present on the same I2C bus or when the sensor's address needs to be changed dynamically.
 *
 * @param sensor Pointer to the TLx493D_t sensor structure to configure.
 * @param address The 7-bit I2C address to set for read operations.
 */
void tlx493d_psoc_setReadAddressIIC(TLx493D_t *sensor, uint8_t address) ;

#endif // PSCO_LIB_IIC_WRAPPER_H_
