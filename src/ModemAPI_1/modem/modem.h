#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#include <process.h>
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <pthread.h>
#endif // WIN32

#include "packets.h"

// Result codes
#define MM_EXCHANGE_OK 0
#define MM_ERROR_TRANSMIT 1
#define MM_ERROR_RECEIVE 2
#define MM_ERROR_CRC 3
#define MM_ERROR_UNEXPECTED_MODEM_REPLY 4
#define MM_ERROR_ANSWERED_MASK 0x80

#define MM_RECEIVED_DATA_OFFSET 3

typedef enum {idle, inProgress, finished} RequestState;

struct RequestContext{
    uint8_t address;
    RequestState state;
    uint8_t resultCode;
    void (*requestFinishCallback)(void *data);
};

// Beacon state structure
struct BeaconState{
    struct RequestContext rq;
    uint32_t workingTimeSeconds;
    int8_t RSSI_dbM;
    uint16_t VCC_mV;
    bool lowPowerFlag;
    bool veryLowPowerFlag;
};

// Sleep control commands
#define SCC_SLEEP_NORMAL 0
#define SCC_SLEEP_DEEP 1
#define SCC_WAKE 2
struct BeaconSleepControl{
    struct RequestContext rq;
    uint8_t sleepControlCmd;
};

#define SERIAL_PORT_HANDLE int
#define PORT_NOT_OPENED -1
#ifdef WIN32
#define DEFAULT_TTY_FILENAME "\\\\.\\COM3"
#else
#define DEFAULT_TTY_FILENAME "/dev/ttyACM0"
#endif // WIN32

struct MarvelmindModem{
    // serial port device name (physical or USB/virtual). It should be provided as an argument:
    // /dev/ttyACM0 - typical for Linux / Raspberry Pi
    // /dev/tty.usbmodem1451 - typical for Mac OS X
    const char * ttyFileName;
    SERIAL_PORT_HANDLE ttyPort;

    // verbose flag which activate console output
    bool verbose; //		default: False


    bool terminationRequired; //  set to "True" to exit from main loop and stop the thread

    struct BeaconState beaconState;
    struct BeaconSleepControl beaconSleepControl;
    #ifdef WIN32
        HANDLE thread_;
        CRITICAL_SECTION lock_;
    #else
        pthread_t thread_;
        pthread_mutex_t lock_;
    #endif
};

struct MarvelmindModem * createMarvelmindModem ();
void destroyMarvelmindModem (struct MarvelmindModem * modem);

int startMarvelmindModem (struct MarvelmindModem * modem);
void stopMarvelmindModem (struct MarvelmindModem * modem);

void startGetBeaconState(struct MarvelmindModem * modem, uint8_t address, void (*requestFinishCallback)(void *data));
void startSendSleepControlCmd(struct MarvelmindModem * modem, uint8_t address, uint8_t sleepControlCmd, void (*requestFinishCallback)(void *data));
