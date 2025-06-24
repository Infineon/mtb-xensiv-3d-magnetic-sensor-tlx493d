#include <malloc.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cy_result.h"
#include "cyhal_hw_types.h"
#include "cyhal_spi.h"

#include "pal.h"
#include "tlx493d_types.h"
#include "types.h"
#include "PSOCLibSPIWrapper.h"


bool tlx493d_psoc_initSPI(TLx493D_t *sensor) {
    cy_rslt_t result;
    TLx493D_SPIObject_t *spiObj = sensor->comInterface.comLibObj.spi_obj;

    result = cyhal_spi_init(spiObj->mSPI, spiObj->mosi, spiObj->miso, spiObj->sclk, spiObj->cs, spiObj->clk, 
                            spiObj->bits, spiObj->mode, spiObj->is_slave);
    if (result != CY_RSLT_SUCCESS) {
        CY_ASSERT(0);
    }

    result = cyhal_spi_set_frequency(spiObj->mSPI, SPI_FREQ);
    if (result != CY_RSLT_SUCCESS) {
        CY_ASSERT(0);
    }
    
    spiObj->mSPI->base->SPI_CTRL &= ~0x10; // Making sure the SPI late sample mode is disabled

    return true;
}

bool tlx493d_psoc_deinitSPI(TLx493D_t *sensor) {
    TLx493D_SPIObject_t *spiObj = sensor->comInterface.comLibObj.spi_obj;

    cyhal_spi_free(spiObj->mSPI);

    return true;
}

bool tlx493d_psoc_transferSPI(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen) {
    if (sensor->boardSupportInterface.boardSupportObj.k2go_obj != NULL) {
        bsc_controlSelect(sensor->boardSupportInterface.boardSupportObj.k2go_obj->k2go, true);
    }
    
    cy_rslt_t result;
    TLx493D_SPIObject_t *spiObj = sensor->comInterface.comLibObj.spi_obj;

    if (txBuffer != NULL && txLen > 0) {
        uint8_t bytesWritten = 0;

        for(; bytesWritten < txLen; bytesWritten++) {   
            result = cyhal_spi_send(spiObj->mSPI, txBuffer[bytesWritten]);
            if (result != CY_RSLT_SUCCESS) {
                CY_ASSERT(0);
            }
        }

        if (bytesWritten != txLen) {
            return false;
        }
    }

    if (rxBuffer != NULL && rxLen > 0) {

        result = cyhal_spi_send(spiObj->mSPI, 0x80);
        if (result != CY_RSLT_SUCCESS) {
            CY_ASSERT(0);
        }

        uint8_t bytesRead = 0;

        for(; bytesRead < rxLen; bytesRead++) {
            uint32_t recv_value = 0;

            result = cyhal_spi_recv(spiObj->mSPI, &recv_value);
            if (result != CY_RSLT_SUCCESS) {
                CY_ASSERT(0);
            }
            rxBuffer[bytesRead] = (uint8_t)recv_value;
        }
        
        if (bytesRead != rxLen) {
            return false;
        }
    }

    if (sensor->boardSupportInterface.boardSupportObj.k2go_obj != NULL) {
        bsc_controlSelect(sensor->boardSupportInterface.boardSupportObj.k2go_obj->k2go, false);
    }

    return true;
}

void tlx493d_psoc_setReadAddressSPI(TLx493D_t *sensor, uint8_t address) {
    
}

