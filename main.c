/**
 * \name main.c
 * \author Infineon Technologies AG
 * \copyright Copyright (c) 2023 Infineon Technologies AG
 * \brief This file contains the main function and example selection for the
 * XENSIV™ 3D Magnetic Sensor library.
 * \details See README.md for more details.
 */

#include "examples/read_iic_sensor/read_iic_sensor.h"
#include "examples/read_iic_sensor_with_wakeup/read_iic_sensor_with_wakeup.h"
#include "examples/read_3_equal_iic_sensors/read_3_equal_iic_sensors.h"
#include "examples/read_3_different_iic_sensors/read_3_different_iic_sensors.h"
#include "examples/read_iic_a1b6_extended_addresses/read_iic_a1b6_extended_addresses.h"
#include "examples/read_spi_sensor/read_spi_sensor.h"

/** Enumeration of available examples */
enum examples_t {
	READ_IIC_SENSOR = 0,
	READ_IIC_SENSOR_WITH_WAKEUP,
	READ_3_EQUAL_IIC_SENSORS,
	READ_3_DIFFERENT_IIC_SENSORS,
	READ_IIC_A1B6_EXTENDED_ADDRESSES,
	READ_SPI_SENSOR
};

/** Selected example */
#define EXAMPLE		READ_IIC_SENSOR

int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init();
    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS) {
		CY_ASSERT(0);
    }

    /* Initialize retarget-io for uart logs */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                                 CY_RETARGET_IO_BAUDRATE);
    /* Retarget-io init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS) {
		CY_ASSERT(0);
	}

    /* Initialize the User LED */
	result = cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT,
							 CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

	/* GPIO init failed. Stop program execution */
	if (result != CY_RSLT_SUCCESS) {
		CY_ASSERT(0);
	}

	/** Switch case for example selection */
	switch (EXAMPLE)
	{
		case READ_IIC_SENSOR:
			printf("\nRunning example: Simple I2C\n");
			read_iic_sensor();
			break;

		case READ_IIC_SENSOR_WITH_WAKEUP:
			printf("\nRunning example: Read I2C Sensor with Wakeup\n");
			read_iic_sensor_with_wakeup();
			break;

		case READ_3_EQUAL_IIC_SENSORS:
			printf("\nRunning example: Read 3 equal I2C sensors\n");
			read_3_equal_iic_sensors();
			break;
		
		case READ_3_DIFFERENT_IIC_SENSORS:
			printf("\nRunning example: Read 3 different I2C sensors\n");
			read_3_different_iic_sensors();
			break;

		case READ_IIC_A1B6_EXTENDED_ADDRESSES:
			printf("\nRunning example: Read I2C Sensor with A1B6 Extended Addresses\n");
			read_iic_a1b6_extended_addresses();
			break;
		
		case READ_SPI_SENSOR:
			printf("\nRunning example: Read SPI Sensor\n");
			read_spi_sensor();
			break;
		
		default:
			printf("Unknown example selected.\n");
			CY_ASSERT(0);
			break;
	}
}

/* [] END OF FILE */