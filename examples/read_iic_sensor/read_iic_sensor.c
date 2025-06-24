/* Include project files*/
#include "read_iic_sensor.h"

void read_iic_sensor(void)
{
    cyhal_i2c_t mI2C;
    cyhal_i2c_cfg_t mI2C_cfg;

	/** Power and I2C pin configuration */
	const uint8_t POWER_PIN = P6_2;

	const uint8_t SDA_PIN = CYBSP_I2C_SDA;
	const uint8_t SCL_PIN = CYBSP_I2C_SCL;

	TLx493D_t dut;

	Kit2GoBoardSupport k2go;

	/** Initialize the sensor object in this case the third generation of the I2C sensor */
	TLx493D_P3B6_init(&dut);

	tlx493d_initBoardSupport(&dut, &k2go);

	bsc_initAttributes(&k2go);

	/** Power pin configuration. The pin is needed because the Kit2Go contains both sensors, the SPI and I2C variant
	 *  of the TLx493D. The power pin is used to power up the I2C sensor only.
	 */
	bsc_setPowerPin(&k2go, POWER_PIN, CYHAL_GPIO_DIR_OUTPUT,
					CYHAL_GPIO_DRIVE_STRONG, false, true, false, 0, 250000, 0, 0);

	bsc_init(&k2go, true, false, false);

	tlx493d_initPSOCIICCommunication(&dut, &mI2C,  &mI2C_cfg, SDA_PIN, SCL_PIN, NULL, TLx493D_IIC_ADDR_A0_e, true);

	TLx493D_P3B6_setDefaultConfig(&dut);

	/** Set the trigger mode for the sensor, otherwise the sensor will not update its register values. */
	tlx493d_setTrigger(&dut, TLx493D_ADC_ON_READ_e);
	
	/**
	 *  In the loop we're reading out the temperature value as well as the magnetic values in X, Y, Z-direction
	 *  of the sensor and print them to the console.
	 */
    for (;;)
    {
		double x = 0, y = 0, z = 0;
		double temperature = 0;

		tlx493d_getMagneticFieldAndTemperature(&dut, &x, &y, &z, &temperature);
		tlx493d_printRegisters(&dut);

		printf("\nTemperature is: %.2f °C\n", temperature);

		printf("Value X is: %.2f mT\n", x);
		printf("Value Y is: %.2f mT\n", y);
		printf("Value Z is: %.2f mT\n\n", z);

		cyhal_gpio_toggle(CYBSP_USER_LED);
		cyhal_system_delay_ms(1000);
    }
}