#ifndef BOARDSUPPORTUSINGKIT2GO_H
#define BOARDSUPPORTUSINGKIT2GO_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Kit2GoBoardSupport.h"
#include "tlx493d_types.h"

/**
 * @brief Initializes the board support configuration for the TLx493D sensor.
 *
 * This function sets up the necessary board support structures and configurations
 * required to interface with the TLx493D sensor using the Kit2Go board.
 *
 * @param sensor Pointer to the TLx493D sensor structure to be initialized.
 * @param bsc Pointer to the Kit2GoBoardSupport structure containing board-specific settings.
 * @return true if initialization was successful, false otherwise.
 */
bool tlx493d_initBoardSupport(TLx493D_t *sensor, Kit2GoBoardSupport *bsc);

#endif //BOARDSUPPORTUSINGKIT2GO_H