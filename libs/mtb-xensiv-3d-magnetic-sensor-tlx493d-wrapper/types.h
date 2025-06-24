#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>

#include "cyhal_hw_resources.h"
#include "cyhal_hw_types.h"
#include "cyhal_i2c.h"
#include "cyhal_psoc6_02_124_bga.h"

#include "IICUsingPSOCLibIIC.h"
#include "pal.h"
#include "tlx493d_enums.h"
#include "tlx493d_types.h"
#include "Kit2GoBoardSupport.h"

/**
 * @struct TLx493D_I2CObject_t
 * @brief Structure representing an I2C object for TLx493D sensor communication.
 *
 * This structure encapsulates the configuration and handles required to interface
 * with a TLx493D sensor over I2C using the Cypress HAL (cyhal) library.
 */
typedef struct TLx493D_I2CObject_t {
    cyhal_i2c_t *mI2C;
    cyhal_i2c_cfg_t *mI2C_config;
    cyhal_gpio_t sda;
    cyhal_gpio_t scl;
} TLx493D_I2CObject_t;

/**
 * @struct TLx493D_SPIObject_t
 * @brief Structure representing an SPI object for TLx493D sensor communication.
 *
 * This structure encapsulates the configuration and handles required to interface
 * with a TLx493D sensor over SPI using the Cypress HAL (cyhal) library.
 */
typedef struct TLx493D_SPIObject_t {
    cyhal_spi_t *mSPI;
    cyhal_gpio_t mosi;
    cyhal_gpio_t miso;
    cyhal_gpio_t sclk;
    cyhal_gpio_t cs;
    cyhal_clock_t *clk;
    uint8_t bits;
    cyhal_spi_mode_t mode;
    bool is_slave;
} TLx493D_SPIObject_t;

/**
 * @struct TLx493D_Kit2GoBoardSupportObject_t
 * @brief Structure representing the Kit2Go board support for TLx493D sensor.
 *
 * This structure encapsulates the Kit2Go board support object and a flag indicating
 * whether the object is to be deleted.
 */
typedef struct TLx493D_Kit2GoBoardSupportObject_t {
    Kit2GoBoardSupport *k2go;
    bool isToBeDeleted;
} TLx493D_Kit2GoBoardSupportObject_t;

#endif // TYPES_H_