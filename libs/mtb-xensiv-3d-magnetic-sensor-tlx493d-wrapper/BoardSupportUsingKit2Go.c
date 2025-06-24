// std includes
#include <malloc.h>
#include <stddef.h>

// project includes
// common to all sensors
#include "tlx493d_types.h"

// project c includes
#include "BoardSupportUsingKit2Go.h"
#include "types.h"

bool tlx493d_initBoardSupport(TLx493D_t *sensor, Kit2GoBoardSupport *bsc) {
    sensor->boardSupportInterface.boardSupportObj.k2go_obj = (TLx493D_Kit2GoBoardSupportObject_t *)malloc(sizeof(TLx493D_Kit2GoBoardSupportObject_t));

    if (sensor->boardSupportInterface.boardSupportObj.k2go_obj == NULL) {
        return false;
    }
    else {
        sensor->boardSupportInterface.boardSupportObj.k2go_obj->k2go = bsc;
        sensor->boardSupportInterface.boardSupportObj.k2go_obj->isToBeDeleted = false;
        
        return true;
    }
}