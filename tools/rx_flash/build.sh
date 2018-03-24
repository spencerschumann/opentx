#!/bin/bash

g++ \
    -Wall \
    -Werror \
    -I include \
    ../../radio/src/crc16.cpp \
    ../../radio/src/telemetry/frsky.cpp \
    ../../radio/src/io/frsky_sport.cpp \
    stubs.cpp \
    file.cpp \
    main.cpp \
    -g -o rx_flash
