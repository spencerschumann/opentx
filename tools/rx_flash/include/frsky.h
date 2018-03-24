#pragma once

#define TELEMETRY_FRSKY_SPORT
#define IS_FRSKY_SPORT_PROTOCOL() (true)
#define FRSKY_TX_PACKET_SIZE            12
#define TELEMETRY_RX_PACKET_SIZE       19  // 9 bytes (full packet), worst case 18 bytes with byte-stuffing (+1)
#define FRSKY_SPORT_PACKET_SIZE   9
#define TELEMETRY_OUTPUT_FIFO_SIZE 16
#define PROTOCOL_FRSKY_SPORT 0
#define telemetryProtocol PROTOCOL_FRSKY_SPORT

#define START_STOP                        0x7e
#define BYTESTUFF                         0x7d
#define STUFF_MASK                        0x20

// Receive buffer state machine state enum
enum FrSkyDataState {
  STATE_DATA_IDLE,
  STATE_DATA_START,
  STATE_DATA_IN_FRAME,
  STATE_DATA_XOR
};
typedef int ModuleIndex;

extern uint8_t outputTelemetryBuffer[TELEMETRY_OUTPUT_FIFO_SIZE];
extern uint8_t telemetryRxBuffer[TELEMETRY_RX_PACKET_SIZE];
extern uint8_t telemetryRxBufferCount;

void sportFlashDevice(ModuleIndex module, const char * filename);
void sportProcessPacket(uint8_t * packet);
void processFrskyTelemetryData(uint8_t data);
