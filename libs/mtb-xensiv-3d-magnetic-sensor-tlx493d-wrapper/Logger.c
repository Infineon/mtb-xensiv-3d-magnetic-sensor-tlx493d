#include <stdio.h>

#include "Logger.h"
#include "tlx493d_types.h"


#define BUFFER_SIZE 512

void logPrintRegisters(const TLx493D_t *sensor, const char *headLine) { //TODO: Create function
    
    if( headLine != NULL ) {
            printf("%s\n", headLine);
        }

    for(uint8_t i = 0; i < sensor->regMapSize; ++i) {
        logPrint("    0x%02X", sensor->regMap[i]);
    }

    printf("\n");
}

void logPrintDouble(double d ) {
    printf("%f\n", d);
}

void logPrint(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);
    printf("%s", buffer);
    va_end(args);
}

void logPrintln(const char *prefix, const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buffer[BUFFER_SIZE];
    vsnprintf(buffer, sizeof(buffer), format, args);
    printf("%s%s\n", prefix, buffer);
    va_end(args);
}

void logFlush() {
    fflush(stdout);
}