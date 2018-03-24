## Frsky Updating Tool

This repo is a fork of OpenTX that adds a PC-based Frsky receiver flashing tool that
uses OpenTX's S.Port telemetry algorithms. The main purpose of this tool is to provide
a way to flash Frsky receivers on Linux (Frsky's proprietary flashing software is only
available on Windows). This is mainly useful for people who don't have access to an
Frsky transmitter for flashing.

**Use at your own risk!** This tool has been tested just once to flash an Frsky XM
receiver. It worked, and didn't brick the receiver! But with only one test I can't
guarantee the same results for anyone else.

The flashing hardware I used was an FTDI 1232 breakout board, with the jumper set to 5 volts.
The TX and RX lines must be inverted - to do this, I used https://github.com/eswierk/ft232r_prog.
Finally, a diode needs to be added to convert the full duplex TX/RX pins to the half duplex
S.Port pin. See the last page of https://www.multirotorparts.nl/downloads/frsky_smart_port_upgrade.pdf
for instructions and a schematic.

## OpenTX 2.2 Branch

[![Travis build Status](https://travis-ci.org/opentx/opentx.svg?branch=2.2)](https://travis-ci.org/opentx/opentx)
[![Quality Gate](https://sonarcloud.io/api/badges/gate?key=OpenTX:2.2)](https://sonarcloud.io/dashboard?id=OpenTX:2.2)
[![Join the chat at https://opentx.rocket.chat](https://camo.githubusercontent.com/3d659054abd6ce21c0e47cf3b83a51bda69ca282/68747470733a2f2f64656d6f2e726f636b65742e636861742f696d616765732f6a6f696e2d636861742e737667)](https://opentx.rocket.chat)
[![Donate using Paypal](https://img.shields.io/badge/paypal-donate-yellow.svg)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=DJ9MASSKVW8WN)

The ongoing development on 2.2.x is done in this branch.

Refer to the [OpenTX wiki](https://github.com/opentx/opentx/wiki) for information about setting up the tool chains for building OpenTX and OpenTX Companion as well as other development related issues.

Useful links:
 * OpenTX Main Site http://www.open-tx.org/
 * OpenTx University http://open-txu.org/
 * OpenTX User Manual https://www.gitbook.com/book/opentx/opentx-taranis-manual/details
 * OpenTX Lua Reference Guide https://www.gitbook.com/book/opentx/opentx-lua-reference-guide/details
