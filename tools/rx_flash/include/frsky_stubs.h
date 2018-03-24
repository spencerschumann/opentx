#pragma once

// No-ops
inline void pausePulses() { }
inline void resumePulses() { }
inline void watchdogSuspend(uint32_t timeout) { };

// Stubs that are never called and are needed only to satisfy the compiler.
void telemetryOutputPushByte(uint8_t byte);
void telemetryOutputSetTrigger(uint8_t byte);
void frskyDProcessPacket(const uint8_t *packet);
void sportProcessTelemetryPacket(const uint8_t * packet);

PACK(union SportTelemetryPacket
{
  struct {
    uint8_t physicalId;
    uint8_t primId;
    uint16_t dataId;
    uint32_t value;
  };
  uint8_t raw[8];
});

#define outputTelemetryBufferSize 0
#define outputTelemetryBufferTrigger 0x7E
