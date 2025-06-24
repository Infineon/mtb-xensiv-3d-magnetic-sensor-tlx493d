#ifndef READ_SPI_SENSOR_H
#define READ_SPI_SENSOR_H

// MTB includes
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

// project c includes
#include "pal.h"
#include "tlx493d.h"
#include "types.h"
#include "tlx493d_types.h"
#include "SPIUsingPSOCLibSPI.h"
#include "IICUsingPSOCLibIIC.h"
#include "BoardSupportUsingKit2Go.h"
#include "Logger.h"

#include "TLx493D_A1B6.h"
#include "TLx493D_A2B6.h"
#include "TLx493D_P2B6.h"
#include "TLx493D_W2B6.h"
#include "TLx493D_W2BW.h"
#include "TLx493D_P3B6.h"
#include "TLx493D_P3I8.h"

void read_spi_sensor(void);

#endif // READ_SPI_SENSOR_H