#include <stddef.h>
#include <stdlib.h>

#include "CommunicationInterface.h"

#include "tlx493d_enums.h"
#include "tlx493d_types.h"


bool tlx493d_transfer(TLx493D_t *sensor, uint8_t *txBuffer, uint8_t txLen, uint8_t *rxBuffer, uint8_t rxLen) {
    return sensor->comIFType == TLx493D_I2C_e ? sensor->comInterface.comLibFuncs->transfer.iic_transfer(sensor, txBuffer, txLen, rxBuffer, rxLen) :
           sensor->comIFType == TLx493D_SPI_e ? sensor->comInterface.comLibFuncs->transfer.spi_transfer(sensor, txBuffer, txLen, rxBuffer, rxLen) :
           false;
}

void tlx493d_setReadAddress(TLx493D_t *sensor, uint8_t address){
    if (sensor->comIFType == TLx493D_I2C_e) {
        sensor->comInterface.comLibFuncs->setReadAddress.iic_setReadAddress(sensor, address);
    } else if (sensor->comIFType == TLx493D_SPI_e) {
        sensor->comInterface.comLibFuncs->setReadAddress.spi_setReadAddress(sensor, address);
    }
}

void deinitCommunication(TLx493D_t *sensor, bool executeDeinit){
    if (sensor->comIFType == TLx493D_I2C_e) {
        if (sensor->comInterface.comLibFuncs != NULL) {
            if (executeDeinit) {
                sensor->comInterface.comLibFuncs->deinit.iic_deinit(sensor);

                free(sensor->comInterface.comLibObj.iic_obj);
                sensor->comInterface.comLibObj.iic_obj = NULL;
            }

            else if (sensor->comIFType == TLx493D_SPI_e) {
                if (executeDeinit) {
                    sensor->comInterface.comLibFuncs->deinit.spi_deinit(sensor);

                    free(sensor->comInterface.comLibObj.spi_obj);
                    sensor->comInterface.comLibObj.spi_obj = NULL;
                }
            
            }
        }   
    }
    sensor->comInterface.comLibFuncs = NULL;
}