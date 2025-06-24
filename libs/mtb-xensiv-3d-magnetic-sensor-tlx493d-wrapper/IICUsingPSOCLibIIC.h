#ifndef IICUsingPSOCLibIIC_H
#define IICUsingPSOCLibIIC_H

#include <stdint.h> 

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#include "cyhal_hw_resources.h"
#include "cyhal_hw_types.h"
#include "cyhal_i2c.h"
#include "cyhal_psoc6_02_124_bga.h"
#include "PSOCLibIICWrapper.h"
#include "tlx493d_types.h"

/**
 * @brief Initializes I2C communication for the TLx493D sensor using the PSoC I2C library.
 *
 * This function sets up the I2C interface and configures the necessary hardware resources
 * to enable communication with a TLx493D sensor. It initializes the I2C peripheral with the
 * specified configuration and assigns the SDA and SCL pins. The function also sets the I2C
 * address for the sensor.
 *
 * @param sensor      Pointer to the TLx493D sensor structure to be initialized.
 * @param mI2C        Pointer to the I2C peripheral instance to be used for communication.
 * @param mI2C_cfg    Pointer to the I2C configuration structure.
 * @param sda         GPIO pin to be used for the I2C SDA line.
 * @param scl         GPIO pin to be used for the I2C SCL line.
 * @param clk         Pointer to the clock resource to be used by the I2C peripheral.
 * @param iic_addr    I2C address type for the TLx493D sensor.
 *
 * @return true if initialization was successful, false otherwise.
 */
bool tlx493d_initPSOCIICCommunication(TLx493D_t *sensor, cyhal_i2c_t *mI2C, cyhal_i2c_cfg_t *mI2C_cfg, cyhal_gpio_t sda, cyhal_gpio_t scl, const cyhal_clock_t *clk, TLx493D_IICAddressType_t iic_addr, bool execute_init);

#endif //IICUsingPSOCLibIIC_H