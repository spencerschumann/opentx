#include "opentx.h"
#include <stdio.h>

// None of these functions should ever be called for rx_update.
// They are included here just to satisfy the linker.

void telemetryOutputPushByte(uint8_t byte) {
    printf("WARNING: unexpected call to stub telemetryOutputPushByte() function\n");
}

void telemetryOutputSetTrigger(uint8_t byte) {
    printf("WARNING: unexpected call to stub telemetryOutputSetTrigger() function\n");
}

void frskyDProcessPacket(const uint8_t *packet) {
    printf("WARNING: unexpected call to stub frskyDProcessPacket() function\n");
}

void sportProcessTelemetryPacket(const uint8_t * packet) {
    printf("WARNING: unexpected call to stub sportProcessTelemetryPacket() function\n");
}
