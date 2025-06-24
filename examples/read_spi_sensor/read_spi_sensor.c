#include "read_spi_sensor.h"

void read_spi_sensor(void)
{
    cyhal_spi_t mSPI;

	/** Power and SPI pin configuration */
	const uint8_t POWER_PIN = P9_4;

	const uint8_t MOSI_PIN = P9_0;
	const uint8_t MISO_PIN = P9_1;
	const uint8_t SCK_PIN = P9_2;
	const uint8_t CS_PIN = P9_3;

	TLx493D_t dut;

	TLx493D_P3I8_init(&dut);

	static Kit2GoBoardSupport k2go;

	tlx493d_initBoardSupport(&dut, &k2go);

	bsc_initAttributes(&k2go);

	/** Power pin configuration */
	bsc_setPowerPin(&k2go, POWER_PIN, CYHAL_GPIO_DIR_OUTPUT,
						 CYHAL_GPIO_DRIVE_STRONG, false, true, false, 0, 0, 0, 0);

	/** Chip select pin configuration */
	bsc_setSelectPin(&k2go, CS_PIN, CYHAL_GPIO_DIR_OUTPUT,
					 CYHAL_GPIO_DRIVE_STRONG, false, true, true, 0, 0, 0 ,0);

	bsc_init(&k2go, true, true, false);

	tlx493d_initPSOCSPICommunication(&dut, &mSPI, MOSI_PIN, MISO_PIN, SCK_PIN, NC,
									NULL, 8, CYHAL_SPI_MODE_10_MSB, false, true);
	
	TLx493D_P3I8_setDefaultConfig(&dut);
	
	/** In the loop we're reading out the temperature values as well as the magnetic values in X, Y, Z-direction 
     *  of the sensor and print them to the console.
     */
    for (;;)
    {
		double x = 0, y = 0, z = 0;
		double temperature = 0;

		cyhal_gpio_toggle(CYBSP_USER_LED);
		cyhal_system_delay_ms(1000);

		dut.functions->getMagneticFieldAndTemperature(&dut, &x, &y, &z, &temperature);
		printf("Magnetic values are in X: %.3f in Y: %.3f in Z: %.3f\n", x, y, z);
		printf("Temperature is: %.2f°C\n", temperature);
    }
}

/* [] END OF FILE */