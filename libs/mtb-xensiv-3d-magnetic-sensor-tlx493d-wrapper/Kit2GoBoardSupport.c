#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#include "Kit2GoBoardSupport.h"
#include "cyhal_gpio.h"
#include "cyhal_gpio_impl.h"
#include "cyhal_system.h"

void bsc_initAttributes(Kit2GoBoardSupport *k2go) {
    bsc_setAddrPin(k2go, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    bsc_unsetAddrPin(k2go);

    bsc_setPowerPin(k2go, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    bsc_unsetPowerPin(k2go);

    bsc_setSelectPin(k2go, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    bsc_unsetSelectPin(k2go);
}

void bsc_init(Kit2GoBoardSupport *k2go, bool enablePower, bool enableSelect, bool enableExtendedAddr) {
    if (enableSelect) {
        for(size_t i = 0; i < sizeof(k2go->selectPins) / sizeof(pinCtrl); i++) {
            initPin(&k2go->selectPins[i]);
        }
    bsc_controlSelect(k2go, true);
    }

    if (enableExtendedAddr) {
        for(size_t i = 0; i < sizeof(k2go->addrPins) / sizeof(pinCtrl); i++) {
            initPin(&k2go->addrPins[i]);
        }
        bsc_controlAddr(k2go, true);
    }

    if (enablePower) {
        for(size_t i = 0; i < sizeof(k2go->powerPins) / sizeof(pinCtrl); i++) {
            initPin(&k2go->powerPins[i]);
        }
        bsc_controlPower(k2go, true);
    }

    if(enableExtendedAddr) {
        bsc_controlAddr(k2go, false);

        for(size_t i = 0; i < sizeof(k2go->addrPins) / sizeof(pinCtrl); i++) {
            cyhal_gpio_free(k2go->addrPins[i].pin);
        }
    }
}

void bsc_deinit(Kit2GoBoardSupport *k2go) {
    bsc_controlPower(k2go, false);
    
    bsc_controlSelect(k2go, false);
}


void bsc_setPowerPin(Kit2GoBoardSupport *k2go, cyhal_gpio_t pin, cyhal_gpio_direction_t direction,
                     cyhal_gpio_drive_mode_t drive_mode, bool enable_value, bool disable_value,
                     bool init_val, uint32_t delayAfterEnable, uint32_t delayAfterDisable,
                     uint32_t delayBeforeEnable, uint32_t delayBeforeDisable) {
    k2go->powerPins[0] = (pinCtrl) {
        .isSet = true,
        .pin = pin,
        .direction = direction,
        .drive_mode = drive_mode,
        .enable_value = enable_value,
        .disable_value = disable_value,
        .init_val = init_val,
        .delayAfterEnable = delayAfterEnable,
        .delayAfterDisable = delayAfterDisable,
        .delayBeforeEnable = delayBeforeEnable,
        .delayBeforeDisable = delayBeforeDisable
    };
}

void bsc_unsetPowerPin(Kit2GoBoardSupport *k2go) {
    k2go->powerPins[0].isSet = false;
}

void bsc_setSelectPin(Kit2GoBoardSupport *k2go, cyhal_gpio_t pin, cyhal_gpio_direction_t direction,
                      cyhal_gpio_drive_mode_t drive_mode, bool enable_value, bool disable_value,
                      bool init_val, uint32_t delayAfterEnable, uint32_t delayAfterDisable, 
                      uint32_t delayBeforeEnable, uint32_t delayBeforeDisable) {
    k2go->selectPins[0] = (pinCtrl) {
        .isSet = true,
        .pin = pin,
        .direction = direction,
        .drive_mode = drive_mode,
        .enable_value = enable_value,
        .disable_value = disable_value,
        .init_val = init_val,
        .delayAfterEnable = delayAfterEnable,
        .delayAfterDisable = delayAfterDisable,
        .delayBeforeEnable = delayBeforeEnable,
        .delayBeforeDisable = delayBeforeDisable
    };
}

void bsc_unsetSelectPin(Kit2GoBoardSupport *k2go) {
    k2go->selectPins[0].isSet = false;
}

void bsc_controlPower(Kit2GoBoardSupport *k2go, bool enablePower) { // TODO: Change function names -> enablePower
    for(size_t i = 0; i < sizeof(k2go->powerPins) / sizeof(pinCtrl); i++) {
        controlPin(&k2go->powerPins[i], enablePower);
    }
}

void bsc_controlSelect(Kit2GoBoardSupport *k2go, bool enableSelect) {
    for(size_t i = 0; i < sizeof(k2go->selectPins) / sizeof(pinCtrl); i++) {
        controlPin(&k2go->selectPins[i], enableSelect);
    }
}

void bsc_setAddrPin(Kit2GoBoardSupport *k2go, cyhal_gpio_t pin, cyhal_gpio_direction_t direction,
                    cyhal_gpio_drive_mode_t drive_mode,  bool enable_value, bool disable_value,
                    bool init_val, uint32_t delayAfterEnable,uint32_t delayAfterDisable,
                    uint32_t delayBeforeEnable, uint32_t delayBeforeDisable) {
    k2go->addrPins[0] = (pinCtrl) {
        .isSet = true,
        .pin = pin,
        .direction = direction,
        .drive_mode = drive_mode,
        .enable_value = enable_value,
        .disable_value = disable_value,
        .init_val = init_val,
        .delayAfterEnable = delayAfterEnable,
        .delayAfterDisable = delayAfterDisable,
        .delayBeforeEnable = delayBeforeEnable,
        .delayBeforeDisable = delayBeforeDisable
    };
}

void bsc_unsetAddrPin(Kit2GoBoardSupport *k2go) {
    k2go->addrPins[0].isSet = false;
}

void bsc_controlAddr(Kit2GoBoardSupport *k2go, bool enableExtendedAddr) {
    for(size_t i = 0; i < sizeof(k2go->addrPins) / sizeof(pinCtrl); i++) {
        controlPin(&k2go->addrPins[i], enableExtendedAddr);
    }
}

void bsc_reset(Kit2GoBoardSupport *k2go) {
    bsc_controlPower(k2go, false);
    bsc_controlPower(k2go, true);
}

void initPin(pinCtrl *pin) {
     cyhal_gpio_init(pin->pin, pin->direction, pin->drive_mode, pin->init_val);
}

void controlPin(pinCtrl *pin, bool enable) {
    if(pin->isSet) {
        if (enable) {
            cyhal_system_delay_us(pin->delayBeforeEnable);
            cyhal_gpio_write(pin->pin, pin->enable_value);
            cyhal_system_delay_us(pin->delayAfterEnable);
        } else {
            cyhal_system_delay_us(pin->delayBeforeDisable);
            cyhal_gpio_write(pin->pin, pin->disable_value);
            cyhal_system_delay_us(pin->delayAfterDisable);
        }
    }
}

void setPinDirection(pinCtrl *pin, bool isInput) {
    if(pin->isSet) {
        if (isInput) {
            cyhal_gpio_configure(pin->pin, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE);
        } else {
            cyhal_gpio_configure(pin->pin, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG);
        }
    }
}

// void setPinDirectionToTristate(pinCtrl *pin) {
//     if(pin->isSet) {
//         cyhal_gpio_configure(pin->pin, CYHAL_GPIO_DIR_BIDIRECTIONAL, CYHAL_GPIO_DRIVE_STRONG);
//     }
// }
