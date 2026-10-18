#include "State.h"
#include <cstdint>

typedef struct {
    uint8_t data; // P1/P2 W A S D BLK
} ClientTelemetry;

typedef struct {
    float ballx, bally;
    float p1x, p1y;
    float p2x, p2y;
} ServerTelemetry;
