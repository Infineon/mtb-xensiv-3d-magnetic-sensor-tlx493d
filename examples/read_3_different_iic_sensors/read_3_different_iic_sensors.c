/* Include project files*/
#include "read_3_different_iic_sensors.h"

void read_3_different_iic_sensors(void)
{
    cyhal_i2c_t mI2C;
    cyhal_i2c_cfg_t mI2C_cfg;

    /** Power and I2C pin configuration */
    const uint8_t POWER_PIN_W2B6 = P6_2;
    const uint8_t POWER_PIN_A2B6 = P6_3;
    const uint8_t POWER_PIN_A1B6 = P9_0;

    const uint8_t SDA_PIN = CYBSP_I2C_SDA;
    const uint8_t SCL_PIN = CYBSP_I2C_SCL;

    /** Declaration of three different sensor objects.
     * 
     *  ATTENTION
     *  All Kit2Go/S2Go boards have pull-up resistors attached to the IIC SCL and SDA lines.
     *  In case of sensors dut2 and dut3 these resistors actually pull-down the SCL/SDA lines while
     *  the sensors are NOT powered. Therefore the pull-up resistors of dut2 and dut3 have to be removed
     *  for this example to work. Otherwise not even dut1 can be initialized properly. Alternatively,
     *  pull-up resistors for all devices are removed and external pull-ups are added to SCL/SDA.
     *  This will have the additional benefit that the order of powering up the devices becomes irrelevant.
     */
    TLx493D_t dut_w2b6;
    TLx493D_t dut_a2b6;
    TLx493D_t dut_a1b6;
    
    /** Declaration of three different board support objects.
     * 
     *  ATTENTION
     *  The board support objects are used to configure the power pins of the sensors.
     *  The power pins are set to output mode and driven high to power the sensors.
     */
    Kit2GoBoardSupport k2go_w2b6;
    Kit2GoBoardSupport k2go_a2b6;
    Kit2GoBoardSupport k2go_a1b6;
    
    TLx493D_W2B6_init(&dut_w2b6);
    TLx493D_A2B6_init(&dut_a2b6);
    TLx493D_A1B6_init(&dut_a1b6);

    tlx493d_initBoardSupport(&dut_w2b6, &k2go_w2b6);
    tlx493d_initBoardSupport(&dut_a2b6, &k2go_a2b6);
    tlx493d_initBoardSupport(&dut_a1b6, &k2go_a1b6);

    bsc_initAttributes(&k2go_w2b6);
	bsc_setPowerPin(&k2go_w2b6, POWER_PIN_W2B6, CYHAL_GPIO_DIR_OUTPUT,
					CYHAL_GPIO_DRIVE_STRONG, true, false, false, 0, 250000, 0, 0);

    bsc_initAttributes(&k2go_a2b6);
	bsc_setPowerPin(&k2go_a2b6, POWER_PIN_A2B6, CYHAL_GPIO_DIR_OUTPUT,
					CYHAL_GPIO_DRIVE_STRONG, true, false, false, 0, 250000, 0, 0);

    bsc_initAttributes(&k2go_a1b6);
	bsc_setPowerPin(&k2go_a1b6, POWER_PIN_A1B6, CYHAL_GPIO_DIR_OUTPUT,
					CYHAL_GPIO_DRIVE_STRONG, true, false, false, 0, 250000, 0, 0);
    
    /** The second generation is critical with respect to interrupts, so you have
     *  to make sure to initialize these sensors first by powering them up one by one
     *  and disabling interrupts in the sensor's begin() method.
     *  Otherwise an interrupt may be triggered on the IIC SCL line stalling the sensor's
     *  communication interface. 
     */
	tlx493d_initPSOCIICCommunication(&dut_w2b6, &mI2C,  &mI2C_cfg, SDA_PIN, SCL_PIN, NULL, TLx493D_IIC_ADDR_A0_e, true);
    bsc_init(&k2go_w2b6, true, false, false);
	tlx493d_setDefaultConfig(&dut_w2b6);
    tlx493d_setIICAddress(&dut_w2b6, TLx493D_IIC_ADDR_A3_e);

    printf("Init of TLx493D_W2B6 successful\n");

    tlx493d_initPSOCIICCommunication(&dut_a2b6, &mI2C,  &mI2C_cfg, SDA_PIN, SCL_PIN, NULL, TLx493D_IIC_ADDR_A0_e, false);
    bsc_init(&k2go_a2b6, true, false, false);
	tlx493d_setDefaultConfig(&dut_a2b6);
    tlx493d_setIICAddress(&dut_a2b6, TLx493D_IIC_ADDR_A2_e);

    printf("Init of TLx493D_A2B6 successful\n");

    tlx493d_initPSOCIICCommunication(&dut_a1b6, &mI2C, &mI2C_cfg, SDA_PIN, SCL_PIN, NULL, TLx493D_IIC_ADDR_A0_e, false);
    bsc_init(&k2go_a1b6, true, false, false);
    tlx493d_setDefaultConfig(&dut_a1b6);

    printf("Init of TLx493D_A1B6 successful\n");

    /** In the loop we're reading out the temperature values as well as the magnetic values in X, Y, Z-direction 
     *  of all three sensors and print them to the console.
     */
    for (;;)
    {
		double x = 0, y = 0, z = 0;
		double temperature = 0;

        printf("Reading from TLx493D_W2B6:\n");
        tlx493d_getMagneticFieldAndTemperature(&dut_w2b6, &x, &y, &z, &temperature);
		tlx493d_printRegisters(&dut_w2b6);

		printf("\nTemperature is: %.2f °C\n", temperature);

		printf("Value X is: %.2f mT\n", x);
		printf("Value Y is: %.2f mT\n", y);
		printf("Value Z is: %.2f mT\n\n", z);

        printf("Reading from TLx493D_A2B6_2:\n");
		tlx493d_getMagneticFieldAndTemperature(&dut_a2b6, &x, &y, &z, &temperature);
		tlx493d_printRegisters(&dut_a2b6);

		printf("\nTemperature is: %.2f °C\n", temperature);

		printf("Value X is: %.2f mT\n", x);
		printf("Value Y is: %.2f mT\n", y);
		printf("Value Z is: %.2f mT\n\n", z);

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