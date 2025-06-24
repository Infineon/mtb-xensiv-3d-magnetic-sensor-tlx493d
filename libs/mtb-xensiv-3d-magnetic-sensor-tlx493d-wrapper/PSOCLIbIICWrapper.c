#include <malloc.h>
#include <stddef.h>

#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "cy_result.h"
#include "cyhal_i2c.h"
#include "logger.h"
#include "pal.h"
#include "PSOCLibIICWrapper.h"
#include "types.h"

bool tlx493d_psoc_initIIC(TLx493D_t *sensor){
    cy_rslt_t result;

    TLx493D_I2CObject_t *iic_obj = sensor->comInterface.comLibObj.iic_obj;
    
    result = cyhal_i2c_init(iic_obj->mI2C, iic_obj->sda, iic_obj->scl, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    iic_obj->mI2C_config->is_slave = false;
    iic_obj->mI2C_config->address = 0x00; // Not used in master mode
    iic_obj->mI2C_config->frequencyhal_hz = 400000; // 400kHz

    result = cyhal_i2c_configure(iic_obj->mI2C, iic_obj->mI2C_config);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    return true;
}

bool tlx493d_psoc_deinitIIC(TLx493D_t *sensor){
    TLx493D_I2CObject_t *iic_obj = sensor->comInterface.comLibObj.iic_obj;

    cyhal_i2c_free(iic_obj->mI2C);

    return true;
}

bool tlx493d_psoc_transferIIC(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen){
    cy_rslt_t result;

    TLx493D_I2CObject_t *iic_obj = sensor->comInterface.comLibObj.iic_obj;

    if (txBuffer != NULL) {
        result = cyhal_i2c_master_write(iic_obj->mI2C, sensor->comInterface.comLibParams.iic_params.address>>1, txBuffer, txLen, 0, true);
        if (result != CY_RSLT_SUCCESS)
        {
            CY_ASSERT(0);
        }
    }

    if (rxBuffer != NULL) {
        result = cyhal_i2c_master_read(iic_obj->mI2C, sensor->comInterface.comLibParams.iic_params.address>>1, rxBuffer, rxLen, 0, true);
        if (result != CY_RSLT_SUCCESS)
        {
            CY_ASSERT(0);
        }
    }

    return true;
}

void tlx493d_psoc_setReadAddressIIC(TLx493D_t *sensor, uint8_t address){
    logWarn("Function 'setReadAddressIIC' not supported!");
}