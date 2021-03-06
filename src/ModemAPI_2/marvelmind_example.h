#ifndef __MARVELMIND_EXAMPLE_H_
#define __MARVELMIND_EXAMPLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#endif // WIN32
#include "marvelmind_example.h"
#include "marvelmind_devices.h"
#include "marvelmind_utils.h"
#include "marvelmind_pos.h"
#include "marvelmind_api.h"

bool marvelmindCheckVersionCommand(char *token);
bool marvelmindCheckWakeCommand(char *token1, char *token2);
bool marvelmindCheckSleepCommand(char *token1, char *token2);
bool marvelmindCheckDefaultCommand(char *token1, char *token2);
bool marvelmindCheckTelemetryCommand(char *token1, char *token2);
bool marvelmindCheckSubmapCommand(char *token1, char *token2, char *token3);
bool marvelmindCheckMapCommand(char *token1, char *token2);
bool marvelmindCheckRateCommand(char *token1, char *token2, char *token3);
bool marvelmindCheckUltrasoundCommand(char *token1, char *token2, char *token3);
bool marvelmindCheckAxesCommand(char *token1, char *token2, char *token3, char *token4);
bool marvelmindCheckReadDumpCommand(char *token1, char *token2, char *token3);
bool marvelmindCheckWriteDumpCommand(char *token1, char *token2, char *token3);
bool marvelmindCheckResetCommand(char *token1, char *token2);
bool marvelmindCheckTemperatureCommand(char *token1, char *token2, char *token3);
bool marvelmindCheckSetLocCommand(char *token1, char *token2, char *token3, char *token4, char *token5);
bool marvelmindCheckSetDistanceCommand(char *token1, char *token2, char *token3, char *token4);
bool marvelmindCheckHeightCommand(char *token1, char *token2, char *token3, char *token4, char *token5);
bool marvelmindCheckRealtimePlayerCommand(char *token1, char *token2, char *token3);
bool marvelmindCheckGeoreferencingCommand(char *token1, char *token2, char *token3, char *token4);
bool marvelmindCheckUpdateLocationModeCommand(char *token1, char *token2, char *token3);
bool marvelmindCheckSendUpdateLocationCommand(char *token1);
bool marvelmindCheckSetMotorsCommand(char *token1, char *token2, char *token3, char *token4, char *token5);
bool marvelmindCheckSetRobotCommand(char *token1, char *token2, char *token3, char *token4, char *token5, char *token6);

void marvelmindCycle();
void marvelmindStart();
void marvelmindFinish();

#endif // __MARVELMIND_EXAMPLE_H_
