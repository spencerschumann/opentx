#pragma once

#include <inttypes.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "definitions.h"

#include "file.h"

// Not actually STM32, but frsky_sport.cpp is mostly disabled without it.
#define STM32

// String translations - hard-coded English for simplicity
#define TR(short, long) (long)
#define STR_WRITING "Writing..."
#define STR_FIRMWARE_UPDATE_ERROR "Firmware update error"

uint16_t crc16(const uint8_t * ptr, uint32_t len);

#include "frsky.h"

// Not called for update, but required to compile telemetry/frsky.cpp and io/frsky_sport.cpp
#include "frsky_stubs.h"

// Functions reimplemented to simulate the opentx environment and
// redirect data to/from the serial port.
void CoTickDelay(uint32_t x);
uint8_t telemetryGetByte(uint8_t *byte);
void sportSendBuffer(uint8_t * buffer, uint32_t count);
void telemetryInit(uint8_t protocol);
void drawProgressBar(const char * label, int num, int den);
void POPUP_WARNING(const char *s);
void SET_WARNING_INFO(const char *info, size_t len, int flags);
