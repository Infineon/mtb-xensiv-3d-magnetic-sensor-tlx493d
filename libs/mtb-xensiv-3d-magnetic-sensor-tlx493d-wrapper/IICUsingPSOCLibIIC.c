#include <malloc.h>
#include <stddef.h>

#include "pal.h"
#include "types.h"
#include "IICUsingPSOCLibIIC.h"
#include "tlx493d_types.h"

TLx493D_ComLibraryFunctions_t comLibIF_i2c = {
    .init.iic_init = tlx493d_psoc_initIIC,
    .deinit.iic_deinit = tlx493d_psoc_deinitIIC,
    .transfer.iic_transfer = tlx493d_psoc_transferIIC,
    .setReadAddress.iic_setReadAddress = tlx493d_psoc_setReadAddressIIC,
};

bool tlx493d_initPSOCIICCommunication(TLx493D_t *sensor, cyhal_i2c_t *mI2C, cyhal_i2c_cfg_t *mI2C_cfg, cyhal_gpio_t sda, cyhal_gpio_t scl, 
                                      const cyhal_clock_t *clk, TLx493D_IICAddressType_t iic_addr, bool execute_init) {
    if (sensor->comIFType != TLx493D_I2C_e) {
        return false;
    }

    sensor->comInterface.comLibObj.iic_obj = (TLx493D_I2CObject_t *)malloc(sizeof(TLx493D_I2CObject_t));
    sensor->comInterface.comLibObj.iic_obj->mI2C = mI2C;
    sensor->comInterface.comLibObj.iic_obj->mI2C_config = mI2C_cfg;
    sensor->comInterface.comLibObj.iic_obj->sda = sda;
    sensor->comInterface.comLibObj.iic_obj->scl = scl;

    sensor->comInterface.comLibFuncs = &comLibIF_i2c;

    sensor->comInterface.comLibParams.iic_params.address = sensor->functions->selectIICAddress(sensor, iic_addr);

    if (execute_init) {
        sensor->comInterface.comLibFuncs->init.iic_init(sensor);
    }

    return true;
}