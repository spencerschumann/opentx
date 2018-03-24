#include "opentx.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>

uint8_t outputTelemetryBuffer[TELEMETRY_OUTPUT_FIFO_SIZE];
uint8_t telemetryRxBuffer[TELEMETRY_RX_PACKET_SIZE];
uint8_t telemetryRxBufferCount = 0;

static int device_fd = -1;

// Delay by x*2 milliseconds
void CoTickDelay(uint32_t x) {
    usleep(x * 2 * 1000);
}

void telemetryInit(uint8_t protocol) {
    // This is a no-op - the actual opening was done earlier in main().
}

uint8_t telemetryGetByte(uint8_t *byte) {
    // TODO: read a byte from the serial port.
    ssize_t count = read(device_fd, byte, 1);
    if (count == -1) {
        printf("ERROR: could not read data: %s\n", strerror(errno));
        return 0;
    }
    return (uint8_t) count;
}

void sportSendBuffer(uint8_t * buffer, uint32_t count) {
    // TODO: send the buffer via the serial port.
    // Note that the buffer will also be received back due to the
    // rx/tx hardware tie, so read back the same amount of data
    // to drain the buffer and verify it.

    ssize_t written = write(device_fd, buffer, count);
    if (written != (uint32_t)count) {
        printf("ERROR: did not write all bytes, requested %d, wrote %ld\n", count, written);
    }

    // Read and verify the echoed data.
    // Time out after 2 seconds.
    int totalDelay = 0;
    for (uint32_t i = 0; i < count; ) {
        uint8_t byte;
        uint8_t r_count = telemetryGetByte(&byte);
        if (r_count == 0) {
            CoTickDelay(1);
            totalDelay += 2;
            if (totalDelay >= 2000) {
                printf("ERROR: time out waiting for echoed data\n");
                return;
            }
            continue;
        }
        if (byte != buffer[i]) {
            printf("WRITE VERIFICATION FAILED: expected %02x, got %02x\n", buffer[i], byte);
        }
        i++;
    }
}

void drawProgressBar(const char * label, int num, int den) {
    // TODO: make console display better.
    printf("PROGRESS: %s %d/%d\n", label, num, den);
}

void POPUP_WARNING(const char *s) {
    // TODO: make console display better.
    printf("WARNING: %s\n", s);
}

void SET_WARNING_INFO(const char *info, size_t len, int flags) {
    // TODO: make console display better.
    printf("         %s\n", info);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("usage: %s <device> <filename>\n", argv[0]);
        printf("Flash <filename> to an Frsky receiver using the serial device <device>.\n");
        printf("TODO: add details on the required serial device hardware.\n");
    }

    const char *device = argv[1];
    const char *filename = argv[2];

    // Open the serial device
    device_fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (device_fd == -1) {
        printf("ERROR: could not open device: %s\n", strerror(errno));
        return 1;
    }

    // Configure the serial device: 57600 baud, 8 data bits, no flow control or parity.
    fcntl(device_fd, F_SETFL, FNDELAY);
    struct termios options;
    if (tcgetattr(device_fd, &options) != 0) {
        printf("ERROR: could not retrieve device settings: %s\n", strerror(errno));
        close(device_fd);
        return 1;
    }
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~CSIZE;
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    //options.c_cflag &= ~CNEW_RTSCTS;
    options.c_cflag |= CS8;

    cfsetispeed(&options, B57600);
    cfsetospeed(&options, B57600);

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag = 0;
    options.c_oflag &= ~OPOST;

    if (tcsetattr(device_fd, TCSANOW, &options) != 0) {
        printf("ERROR: could not set device settings: %s\n", strerror(errno));
        close(device_fd);
        return 1;
    }

    printf("Device %s opened.\n", device);

    sportFlashDevice(0, filename);

    close(device_fd);

    return 0;
}
