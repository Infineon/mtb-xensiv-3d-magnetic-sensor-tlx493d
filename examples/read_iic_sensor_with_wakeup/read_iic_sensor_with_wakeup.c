/* Include project files*/
#include "read_iic_sensor_with_wakeup.h"

/** GPIO interrupt priority */
#define GPIO_INTERRUPT_PRIORITY (7u)

/** GPIO interrupt flag */
volatile bool gpio_interrupt_flag = false;

/** GPIO callback data */
cyhal_gpio_callback_data_t gpio_callback_data;

/** GPIO interrupt handler */
static void gpio_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event);


void read_iic_sensor_with_wakeup(void)
{
    cyhal_i2c_t mI2C;
    cyhal_i2c_cfg_t mI2C_cfg;

    /** I2C pin configuration */
    const uint8_t SDA_PIN = CYBSP_I2C_SDA;
    const uint8_t SCL_PIN = CYBSP_I2C_SCL;

    /** Wakeup thresholds */
    const int16_t THRESHOLD = 200;

    const int16_t LOWER_TRESHOLD_X = -THRESHOLD;
    const int16_t LOWER_TRESHOLD_Y = -THRESHOLD;
    const int16_t LOWER_TRESHOLD_Z = -THRESHOLD;

    const int16_t UPPER_TRESHOLD_X = THRESHOLD;
    const int16_t UPPER_TRESHOLD_Y = THRESHOLD;
    const int16_t UPPER_TRESHOLD_Z = THRESHOLD;

    /** Interrupt pin */
    const uint8_t INTERRUPT_PIN = P6_0;

	TLx493D_t dut;

	TLx493D_W2B6_init(&dut);

	tlx493d_initPSOCIICCommunication(&dut, &mI2C,  &mI2C_cfg, SDA_PIN, SCL_PIN, NULL, TLx493D_IIC_ADDR_A0_e, true);

    tlx493d_setDefaultConfig(&dut);	

    /** Here we're setting up the wakeup thresholds, enabling the wake up mode for the sensor and enable the interrupt */
    tlx493d_setWakeUpThresholdsAsInteger(&dut, LOWER_TRESHOLD_X, UPPER_TRESHOLD_X, LOWER_TRESHOLD_Y,
                                         UPPER_TRESHOLD_Y, LOWER_TRESHOLD_Z, UPPER_TRESHOLD_Z);
    tlx493d_enableWakeUpMode(&dut);
    TLx493D_W2B6_enableInterrupt(&dut);

    /** Configuration of the interrupt pin, the callback function and enablement of the interrupt */
    cyhal_gpio_init(INTERRUPT_PIN, CYHAL_GPIO_DIR_INPUT,
                    CYHAL_GPIO_DRIVE_PULL_NONE, CYBSP_LED_STATE_OFF);
    gpio_callback_data.callback = gpio_interrupt_handler;
    cyhal_gpio_register_callback(INTERRUPT_PIN,
                                 &gpio_callback_data);
    cyhal_gpio_enable_event(INTERRUPT_PIN, CYHAL_GPIO_IRQ_FALL,
                                 GPIO_INTERRUPT_PRIORITY, true);

    /* Enable global interrupts */
    __enable_irq(); 
    
    /** In the main loop we're waiting for the sensor's interrupt. 
     *  Once the interrupt is triggered, the LED is toggled and the system sleeps for 2 seconds.
     *  After that the loop starts again. 
     */
    for (;;)
    {   
        if (gpio_interrupt_flag){
            cyhal_gpio_toggle(CYBSP_USER_LED);
            cyhal_system_delay_ms(2000);

            gpio_interrupt_flag = false;
        }
    }
}

/** GPIO interrupt handler function */
static void gpio_interrupt_handler(void *handler_arg, cyhal_gpio_event_t event) {
    gpio_interrupt_flag = true;
}
