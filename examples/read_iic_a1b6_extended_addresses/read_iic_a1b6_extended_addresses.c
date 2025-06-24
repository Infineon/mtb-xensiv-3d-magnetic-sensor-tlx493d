/* Include project files*/
#include "read_iic_a1b6_extended_addresses.h"

void read_iic_a1b6_extended_addresses(void)
{
    cyhal_i2c_t mI2C;
    cyhal_i2c_cfg_t mI2C_cfg;

    /** Power and address pins for the sensor */
    const uint8_t POWER_PIN = P6_2;
    const uint8_t SDA_ADDRESS_PIN = P6_3;

    TLx493D_t dut_a1b6;
    
    Kit2GoBoardSupport k2go_a1b6;
    
    TLx493D_A1B6_init(&dut_a1b6);

    tlx493d_initBoardSupport(&dut_a1b6, &k2go_a1b6);

    bsc_initAttributes(&k2go_a1b6);

    /** Power pin configuration. The delay is needed, because first we have to pull down the address pin (SDA pin)
     *  before we can power up the sensor to enable the extended addresses. The datasheet of the TLx493D_A1B6
     *  states that the address pin has to be pulled down for at least 200 us before powering up the sensor.
     */
    bsc_setPowerPin(&k2go_a1b6, POWER_PIN, CYHAL_GPIO_DIR_OUTPUT,
                    CYHAL_GPIO_DRIVE_STRONG, true, false, false, 200, 250000, 0, 0);

    bsc_setAddrPin(&k2go_a1b6, SDA_ADDRESS_PIN, CYHAL_GPIO_DIR_OUTPUT,
                         CYHAL_GPIO_DRIVE_STRONG, false, true, false, 0, 0, 0, 0);

    /** With the extended address feature enabled the sensor's addresses changes to A4 */
	tlx493d_initPSOCIICCommunication(&dut_a1b6, &mI2C,  &mI2C_cfg, CYBSP_I2C_SDA, CYBSP_I2C_SCL, NULL, TLx493D_IIC_ADDR_A4_e, true);

    /** Make sure to enable the extended address feature */
    bsc_init(&k2go_a1b6, true, false, true);
	tlx493d_setDefaultConfig(&dut_a1b6);
    tlx493d_setIICAddress(&dut_a1b6, TLx493D_IIC_ADDR_A7_e);
    
    /** In the loop we're reading out the temperature value as well as the magnetic values in X, Y, Z-direction 
     *  of the sensor and print them to the console.
     */
    for (;;)
    {
		double x = 0, y = 0, z = 0;
		double temperature = 0;

        printf("Reading from TLx493D_A1B6:\n");
        tlx493d_getMagneticFieldAndTemperature(&dut_a1b6, &x, &y, &z, &temperature);
		tlx493d_printRegisters(&dut_a1b6);

		printf("\nTemperature is: %.2f °C\n", temperature);

		printf("Value X is: %.2f mT\n", x);
		printf("Value Y is: %.2f mT\n", y);
		printf("Value Z is: %.2f mT\n\n", z);

		cyhal_gpio_toggle(CYBSP_USER_LED);
		cyhal_system_delay_ms(1000);
    }
}