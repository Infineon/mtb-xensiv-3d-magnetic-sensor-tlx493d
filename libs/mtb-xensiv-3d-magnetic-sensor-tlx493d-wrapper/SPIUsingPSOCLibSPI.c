#include <malloc.h>
#include <stddef.h>

#include "cyhal.h"
#include "cyhal_hw_resources.h"
#include "tlx493d_types.h"

#include "types.h"
#include "Logger.h"
#include "PSOCLibSPIWrapper.h"
#include "SPIUsingPSOCLibSPI.h"
#include "Kit2GoBoardSupport.h"



TLx493D_ComLibraryFunctions_t comLibFuncs_spi = {
    .init.spi_init = tlx493d_psoc_initSPI,
    .deinit.spi_deinit = tlx493d_psoc_deinitSPI,
    .transfer.spi_transfer = tlx493d_psoc_transferSPI,
    .setReadAddress.spi_setReadAddress = tlx493d_psoc_setReadAddressSPI,
};

bool tlx493d_initPSOCSPICommunication(TLx493D_t *sensor, cyhal_spi_t *mSPI , cyhal_gpio_t mosi, cyhal_gpio_t miso, cyhal_gpio_t sclk, cyhal_gpio_t cs,
    const cyhal_clock_t *clk, uint8_t bits, cyhal_spi_mode_t mode, bool is_slave, bool execute_init) {
    if (sensor->comIFType != TLx493D_SPI_e) {
        return false;
    }

    sensor->comInterface.comLibObj.spi_obj = (TLx493D_SPIObject_t *)malloc(sizeof(TLx493D_SPIObject_t));
    sensor->comInterface.comLibObj.spi_obj->mSPI = mSPI;
    sensor->comInterface.comLibObj.spi_obj->mosi = mosi;
    sensor->comInterface.comLibObj.spi_obj->miso = miso;
    sensor->comInterface.comLibObj.spi_obj->sclk = sclk;
    sensor->comInterface.comLibObj.spi_obj->cs = cs;
    sensor->comInterface.comLibObj.spi_obj->clk = (cyhal_clock_t *)clk;
    sensor->comInterface.comLibObj.spi_obj->bits = bits;
    sensor->comInterface.comLibObj.spi_obj->mode = mode;
    sensor->comInterface.comLibObj.spi_obj->is_slave = is_slave;
    
    sensor->comInterface.comLibFuncs = &comLibFuncs_spi;

    if (execute_init) {
        sensor->comInterface.comLibFuncs->init.spi_init(sensor);
    }

    return true;
}
