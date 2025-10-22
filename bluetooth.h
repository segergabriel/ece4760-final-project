#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

void initBluetooth(uint baudrate, uint tx_pin, uint rx_pin, int master);
int sendBluetoothData(const char* data);
void sendATCommand(const char* cmd);
bool readBluetoothResponse(char* buffer);
void configMaster();
int parseResponse(char*, int*, int*);
int parseBluetoothResponse(const char* , int*, int*, volatile bool*, volatile bool*);

#endif
