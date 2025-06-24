/* Include project files*/
#include "read_3_equal_iic_sensors.h"

void read_3_equal_iic_sensors(void)
{
    cyhal_i2c_t mI2C;
    cyhal_i2c_cfg_t mI2C_cfg;

    /** Power and I2C pin configuration */
    const uint8_t POWER_PIN_1 = P6_2;
    const uint8_t POWER_PIN_2 = P6_3;
    const uint8_t POWER_PIN_3 = P9_0;

    const uint8_t SDA_PIN = CYBSP_I2C_SDA;
    const uint8_t SCL_PIN = CYBSP_I2C_SCL;

    /** Declaration of three sensor objects with the same default address (A0).
     * 
     *  ATTENTION
     *  All Kit2Go/S2Go boards have pull-up resistors attached to the IIC SCL and SDA lines.
     *  In case of sensors dut2 and dut3 these resistors actually pull-down the SCL/SDA lines while
     *  the sensors are NOT powered. Therefore the pull-up resistors of dut2 and dut3 have to be removed
     *  for this example to work. Otherwise not even dut1 can be initialized properly. Alternatively,
     *  pull-up resistors for all devices are removed and external pull-ups are added to SCL/SDA.
     */
    TLx493D_t dut_a2b6_1;
    TLx493D_t dut_a2b6_2;
    TLx493D_t dut_a2b6_3;
    
    Kit2GoBoardSupport k2go_a2b6_1;
    Kit2GoBoardSupport k2go_a2b6_2;
    Kit2GoBoardSupport k2go_a2b6_3;

    TLx493D_A2B6_init(&dut_a2b6_1);
    TLx493D_A2B6_init(&dut_a2b6_2);
    TLx493D_A2B6_init(&dut_a2b6_3);

    tlx493d_initBoardSupport(&dut_a2b6_1, &k2go_a2b6_1);
    tlx493d_initBoardSupport(&dut_a2b6_2, &k2go_a2b6_2);
    tlx493d_initBoardSupport(&dut_a2b6_3, &k2go_a2b6_3);

    /** Here we're using three GPIOs to power up the sensors, one
     *  after the other. This is done by defining the pins with the
     *  Board Support Class and its functions. The power up pins are
     *  enabled during the bsc_init() call to the sensor object as done below.
     */
    bsc_initAttributes(&k2go_a2b6_1);
	bsc_setPowerPin(&k2go_a2b6_1, POWER_PIN_1, CYHAL_GPIO_DIR_OUTPUT,
					CYHAL_GPIO_DRIVE_STRONG, true, false, false, 0, 250000, 0, 0);

    bsc_initAttributes(&k2go_a2b6_2);
	bsc_setPowerPin(&k2go_a2b6_2, POWER_PIN_2, CYHAL_GPIO_DIR_OUTPUT,
					CYHAL_GPIO_DRIVE_STRONG, true, false, false, 0, 250000, 0, 0);

    bsc_initAttributes(&k2go_a2b6_3);
	bsc_setPowerPin(&k2go_a2b6_3, POWER_PIN_3, CYHAL_GPIO_DIR_OUTPUT,
					CYHAL_GPIO_DRIVE_STRONG, true, false, false, 0, 250000, 0, 0);
    
    /** Here we're enabling one sensor after another. This procedure 
     *  is necessary in order to avoid an interrupt to occur on the SCL line before
     *  interrupts are disabled in the sensor's begin() method. Additionally, the IIC address
     *  is changed from the default A0 to a distinct one for each sensor.
     */
	tlx493d_initPSOCIICCommunication(&dut_a2b6_1, &mI2C,  &mI2C_cfg, SDA_PIN, SCL_PIN, NULL, TLx493D_IIC_ADDR_A0_e, true);
    bsc_init(&k2go_a2b6_1, true, false, false);
	tlx493d_setDefaultConfig(&dut_a2b6_1);
    tlx493d_setIICAddress(&dut_a2b6_1, TLx493D_IIC_ADDR_A3_e);

    printf("Init of sensor one successful\n");

    tlx493d_initPSOCIICCommunication(&dut_a2b6_2, &mI2C,  &mI2C_cfg, SDA_PIN, SCL_PIN, NULL, TLx493D_IIC_ADDR_A0_e, false);
    bsc_init(&k2go_a2b6_2, true, false, false);
	tlx493d_setDefaultConfig(&dut_a2b6_2);
    tlx493d_setIICAddress(&dut_a2b6_2, TLx493D_IIC_ADDR_A2_e);

    printf("Init of sensor two successful\n");

    tlx493d_initPSOCIICCommunication(&dut_a2b6_3, &mI2C, &mI2C_cfg, SDA_PIN, SCL_PIN, NULL, TLx493D_IIC_ADDR_A0_e, false);
    bsc_init(&k2go_a2b6_3, true, false, false);
    tlx493d_setDefaultConfig(&dut_a2b6_3);

    printf("Init of sensor three successful\n");
    
    /** In the loop we're reading out the temperature value as well as the magnetic values in X, Y, Z-direction 
     *  of all three sensors and print them to the console.
     */
    for (;;)
    {
		double x = 0, y = 0, z = 0;
		double temperature = 0;

        printf("Reading from Sensor 1:\n");
        tlx493d_getMagneticFieldAndTemperature(&dut_a2b6_1, &x, &y, &z, &temperature);
		tlx493d_printRegisters(&dut_a2b6_1);

		printf("\nTemperature is: %.2f °C\n", temperature);

		printf("Value X is: %.2f mT\n", x);
		printf("Value Y is: %.2f mT\n", y);
		printf("Value Z is: %.2f mT\n\n", z);

        printf("Reading from Sensor 2:\n");
		tlx493d_getMagneticFieldAndTemperature(&dut_a2b6_2, &x, &y, &z, &temperature);
		tlx493d_printRegisters(&dut_a2b6_2);

		printf("\nTemperature is: %.2f °C\n", temperature);

		printf("Value X is: %.2f mT\n", x);
		printf("Value Y is: %.2f mT\n", y);
		printf("Value Z is: %.2f mT\n\n", z);

        printf("Reading from Sensor 3:\n");
        tlx493d_getMagneticFieldAndTemperature(&dut_a2b6_3, &x, &y, &z, &temperature);
		tlx493d_printRegisters(&dut_a2b6_3);

		printf("\nTemperature is: %.2f °C\n", temperature);

		printf("Value X is: %.2f mT\n", x);
		printf("Value Y is: %.2f mT\n", y);
		printf("Value Z is: %.2f mT\n\n", z);

		cyhal_gpio_toggle(CYBSP_USER_LED);
		cyhal_system_delay_ms(1000);
    }
}