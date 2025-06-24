#ifndef KIT2GOSUPPORT_H_
#define KIT2GOSUPPORT_H_

#include "cyhal_gpio.h"
#include <stdint.h>
#include <stdbool.h>

/**
 * @struct pinCtrl
 * @brief Structure for controlling and configuring a GPIO pin.
 *
 * This structure encapsulates the configuration and control parameters for a GPIO pin,
 * including its direction, drive mode, initial value, enable/disable values, and
 * timing delays for enable/disable operations.
 */
typedef struct pinCtrl {
    bool isSet;
    cyhal_gpio_t pin;

    cyhal_gpio_direction_t direction;
    cyhal_gpio_drive_mode_t drive_mode;

    bool enable_value;
    bool disable_value;

    bool init_val;

    uint32_t delayAfterEnable;
    uint32_t delayAfterDisable;

    uint32_t delayBeforeEnable;
    uint32_t delayBeforeDisable;
} pinCtrl;

/**
 * @struct Kit2GoBoardSupport
 * @brief Structure representing the board support configuration for Kit2Go.
 *
 * This structure holds arrays of pin control configurations for power, select, and address pins.
 */
typedef struct Kit2GoBoardSupport {
    pinCtrl powerPins[1];
    pinCtrl selectPins[1];
    pinCtrl addrPins[1];
} Kit2GoBoardSupport;


/**
 * @brief Initializes the attributes of the given Kit2GoBoardSupport instance.
 *
 * This function sets up the initial state and configuration parameters
 * for the specified Kit2GoBoardSupport structure. It should be called
 * before using the instance to ensure all attributes are properly initialized.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure to initialize.
 */
void bsc_initAttributes(Kit2GoBoardSupport *k2go);

/**
 * @brief Initializes the Kit2Go board support configuration.
 *
 * This function sets up the Kit2GoBoardSupport structure and configures
 * the board's power, selection, and extended address features based on
 * the provided flags.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure to initialize.
 * @param enablePower Set to true to enable board power, false to disable.
 * @param enableSelect Set to true to enable board selection, false to disable.
 * @param enableExtendedAddr Set to true to enable extended addressing, false to disable.
 */
void bsc_init(Kit2GoBoardSupport *k2go, bool enablePower, bool enableSelect, bool enableExtendedAddr);

/**
 * @brief Deinitializes the Board Support Controller (BSC) for the specified Kit2Go board.
 *
 * This function releases any resources and performs necessary cleanup associated with
 * the Kit2GoBoardSupport instance.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure to be deinitialized.
 */
void bsc_deinit(Kit2GoBoardSupport *k2go);

/**
 * @brief Configures and controls a power pin on the Kit2Go board.
 *
 * This function sets up a specified GPIO pin as a power control pin, allowing it to be enabled or disabled
 * with configurable drive mode, direction, and timing delays for power sequencing.
 *
 * @param k2go                Pointer to the Kit2GoBoardSupport structure.
 * @param pin                 The GPIO pin to be configured as a power pin.
 * @param direction           The direction of the GPIO pin (input/output).
 * @param drive_mode          The drive mode for the GPIO pin.
 * @param enable_value        Logic value to set the pin when enabling power (true for high, false for low).
 * @param disable_value       Logic value to set the pin when disabling power (true for high, false for low).
 * @param init_val            Initial value to set the pin upon configuration.
 * @param delayAfterEnable    Delay in milliseconds after enabling the power pin.
 * @param delayAfterDisable   Delay in milliseconds after disabling the power pin.
 * @param delayBeforeEnable   Delay in milliseconds before enabling the power pin.
 * @param delayBeforeDisable  Delay in milliseconds before disabling the power pin.
 */
void bsc_setPowerPin(Kit2GoBoardSupport *k2go, cyhal_gpio_t pin, cyhal_gpio_direction_t direction,
                     cyhal_gpio_drive_mode_t drive_mode, bool enable_value, bool disable_value,
                     bool init_val, uint32_t delayAfterEnable, uint32_t delayAfterDisable,
                     uint32_t delayBeforeEnable, uint32_t delayBeforeDisable);

/**
 * @brief Unsets or disables the power pin on the specified Kit2Go board support instance.
 *
 * This function is used to deactivate or release control of the power pin associated
 * with the provided Kit2GoBoardSupport object. It is typically called when the power
 * pin is no longer needed or before shutting down the board to ensure safe power management.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure representing the target board.
 */
void bsc_unsetPowerPin(Kit2GoBoardSupport *k2go);

/**
 * @brief Configures a select pin for the Kit2Go board support.
 *
 * This function sets up a GPIO pin as a select pin with the specified direction, drive mode,
 * and initial value. It also allows configuration of enable/disable logic levels and
 * timing delays for enabling and disabling the pin.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure.
 * @param pin The GPIO pin to configure.
 * @param direction The direction of the GPIO pin (input/output).
 * @param drive_mode The drive mode for the GPIO pin.
 * @param enable_value Logic value to set when enabling the pin.
 * @param disable_value Logic value to set when disabling the pin.
 * @param init_val Initial value to set on the pin during configuration.
 * @param delayAfterEnable Delay in milliseconds after enabling the pin.
 * @param delayAfterDisable Delay in milliseconds after disabling the pin.
 * @param delayBeforeEnable Delay in milliseconds before enabling the pin.
 * @param delayBeforeDisable Delay in milliseconds before disabling the pin.
 */
void bsc_setSelectPin(Kit2GoBoardSupport *k2go, cyhal_gpio_t pin, cyhal_gpio_direction_t direction,
                      cyhal_gpio_drive_mode_t drive_mode, bool enable_value, bool disable_value,
                      bool init_val, uint32_t delayAfterEnable, uint32_t delayAfterDisable,
                      uint32_t delayBeforeEnable, uint32_t delayBeforeDisable);

/**
 * @brief Unsets or deactivates the select pin for the specified Kit2Go board support instance.
 *
 * This function is typically used to deselect a device or peripheral connected to the board
 * by setting the select pin to its inactive state.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure representing the board instance.
 */
void bsc_unsetSelectPin(Kit2GoBoardSupport *k2go);

/**
 * @brief Controls the power state of the Kit2Go board.
 *
 * This function enables or disables the power supply to the Kit2Go board
 * by setting the appropriate control signals.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure representing the board.
 * @param enablePower Set to true to enable power, false to disable power.
 */
void bsc_controlPower(Kit2GoBoardSupport *k2go, bool enablePower);

/**
 * @brief Controls the selection state of the BSC (Board Support Controller).
 *
 * This function enables or disables the select control for the specified Kit2GoBoardSupport instance.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure representing the board.
 * @param enableSelect Set to true to enable selection, or false to disable selection.
 */
void bsc_controlSelect(Kit2GoBoardSupport *k2go, bool enableSelect);

/**
 * @brief Configures an address pin for the Kit2Go board support.
 *
 * This function sets up a specified GPIO pin as an address pin, configuring its direction,
 * drive mode, initial value, and enable/disable logic. It also allows specifying delays
 * before and after enabling or disabling the pin.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure.
 * @param pin The GPIO pin to configure.
 * @param direction The direction of the GPIO pin (input or output).
 * @param drive_mode The drive mode for the GPIO pin.
 * @param enable_value The value to set when enabling the pin.
 * @param disable_value The value to set when disabling the pin.
 * @param init_val The initial value to set for the pin.
 * @param delayAfterEnable Delay in milliseconds after enabling the pin.
 * @param delayAfterDisable Delay in milliseconds after disabling the pin.
 * @param delayBeforeEnable Delay in milliseconds before enabling the pin.
 * @param delayBeforeDisable Delay in milliseconds before disabling the pin.
 */
void bsc_setAddrPin(Kit2GoBoardSupport *k2go, cyhal_gpio_t pin, cyhal_gpio_direction_t direction,
                    cyhal_gpio_drive_mode_t drive_mode, bool enable_value, bool disable_value,
                    bool init_val, uint32_t delayAfterEnable, uint32_t delayAfterDisable, 
                    uint32_t delayBeforeEnable, uint32_t delayBeforeDisable);

/**
 * @brief Unsets or clears the address pin configuration on the specified Kit2Go board support instance.
 *
 * This function is typically used to reset or disable the address pin, which may be used for
 * hardware addressing or selection purposes on the Kit2Go board.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure representing the target board.
 */
void bsc_unsetAddrPin(Kit2GoBoardSupport *k2go);

/**
 * @brief Controls the address mode of the Kit2Go board support controller.
 *
 * This function enables or disables the extended address mode for the specified
 * Kit2GoBoardSupport instance.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure.
 * @param enableExtendedAddr Set to true to enable extended address mode, false to disable.
 */
void bsc_controlAddr(Kit2GoBoardSupport *k2go, bool enableExtendedAddr);

/**
 * @brief Resets the BSC (Board Support Controller) of the Kit2Go board.
 *
 * This function performs a reset operation on the BSC associated with the specified
 * Kit2GoBoardSupport instance. It is typically used to reinitialize the board support
 * controller to its default state.
 *
 * @param k2go Pointer to the Kit2GoBoardSupport structure representing the board to reset.
 */
void bsc_reset(Kit2GoBoardSupport *k2go);

/**
 * @brief Initializes the specified pin according to its configuration.
 *
 * This function sets up the hardware pin referenced by the provided
 * pinCtrl structure. It typically configures the pin's direction,
 * mode, and any other relevant hardware settings required for proper
 * operation.
 *
 * @param pin Pointer to a pinCtrl structure that describes the pin
 *            to be initialized.
 */
void initPin(pinCtrl *pin);

/**
 * @brief Controls the state of a specified pin.
 *
 * This function enables or disables the given pin based on the 'enable' parameter.
 *
 * @param pin Pointer to the pinCtrl structure representing the pin to control.
 * @param enable Set to true to enable the pin, or false to disable it.
 */
void controlPin(pinCtrl *pin, bool enable);

/**
 * @brief Sets the direction of a specified pin.
 *
 * Configures the given pin as either input or output based on the isInput parameter.
 *
 * @param pin Pointer to the pin control structure representing the pin to configure.
 * @param isInput If true, sets the pin as input; if false, sets the pin as output.
 */
void setPinDirection(pinCtrl *pin, bool isInput);

#endif // KIT2GOSUPPORT_H_