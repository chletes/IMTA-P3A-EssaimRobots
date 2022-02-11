#include "main.h"

uint32_t requestRepeatsCount = 1;

#ifdef WIN32
BOOL CtrlHandler( DWORD fdwCtrlType ){
    if ((fdwCtrlType==CTRL_C_EVENT ||
            fdwCtrlType==CTRL_BREAK_EVENT ||
            fdwCtrlType==CTRL_CLOSE_EVENT ||
            fdwCtrlType==CTRL_LOGOFF_EVENT ||
            fdwCtrlType==CTRL_SHUTDOWN_EVENT) &&
            (terminateProgram==false)){
        terminateProgram=true;
        return true;
    }else return false;
}
#else
void CtrlHandler(int signum){
    terminateProgram = true;
}
#endif

#ifdef WIN32
void sleepMs(unsigned int ms){
    Sleep (ms);
}
#else
void sleepMs(unsigned int ms){
    usleep (ms*1000);
}
#endif

void processBeaconStateReply(void *data){
    struct BeaconState *beaconState = (struct BeaconState *)data;

    if (beaconState->rq.resultCode == MM_EXCHANGE_OK){
        printf("Beacon %d state: RSSI= %d, Vcc= %.3f, Time= %ld \n",
               (int)beaconState->rq.address, (int)beaconState->RSSI_dbM,
               ((double)beaconState->VCC_mV) / 1000.0, (long int)beaconState->workingTimeSeconds);
    }else{
        printf("Failed read beacon %d state: error %d \n", (int)beaconState->rq.address, (int)beaconState->rq.resultCode);
    }

    if (requestRepeatsCount > 0)
        requestRepeatsCount--;
}

void processSleepControlCmdReply(void *data){
    struct BeaconSleepControl *beaconSleepControl = (struct BeaconSleepControl *)data;

    if (beaconSleepControl->rq.resultCode == MM_EXCHANGE_OK){
        printf("Beacon sleep control command %d to device %d completed \n",
               (int)beaconSleepControl->sleepControlCmd, (int)beaconSleepControl->rq.address);
    }else{
        printf("Beacon sleep control command %d for device %d failed: error %d \n",
               (int)beaconSleepControl->sleepControlCmd, (int)beaconSleepControl->rq.address, (int)beaconSleepControl->rq.resultCode);
    }

    if (requestRepeatsCount > 0)
        requestRepeatsCount--;
}

static void trySendCommand(struct MarvelmindModem *modem, uint8_t cmd, uint8_t address){
    if (requestRepeatsCount == 0)
        return;

    switch (cmd){
        case CMD_STATE:{
            if (modem->beaconState.rq.state != inProgress){
                startGetBeaconState(modem, address, &processBeaconStateReply);
            }
            break;
        }

        case CMD_SLEEP:
        case CMD_DEEPSLEEP:
        case CMD_WAKE:{
            uint8_t sleepCmd;

            if (modem->beaconState.rq.state != inProgress){
                switch (cmd){
                    case CMD_SLEEP:{
                        sleepCmd = SCC_SLEEP_NORMAL;
                        break;
                    };
                    case CMD_DEEPSLEEP:{
                        sleepCmd = SCC_SLEEP_DEEP;
                        break;
                    };
                    case CMD_WAKE:{
                        sleepCmd = SCC_WAKE;
                        break;
                    };
                }
                startSendSleepControlCmd(modem, address, sleepCmd, &processSleepControlCmdReply);
            }
            break;
        }
    }
}

int stopModemThread(struct MarvelmindModem * modem){
    printf("* Stopping modem...\n");
    stopMarvelmindModem (modem);
    destroyMarvelmindModem (modem);
}

int main(int argc, char *argv[]){
    int beaconAddress = -1;
    uint8_t cmd = -1;
    printf("* Creating modem...\n");

    struct MarvelmindModem * modem = createMarvelmindModem ();
    if (modem==NULL){
        printf("Error: Unable to create MarvelmindModem");
    }
    
    int result = startMarvelmindModem (modem); // result creating thread
    if (result) { //Checking creation of thread
        fprintf(stderr, "%s", strerror (result));
        terminateProgram = true;
    }

    // Set Ctrl-C handler
    #ifdef WIN32
        SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );
    #else
        signal (SIGINT, CtrlHandler);
        signal (SIGQUIT, CtrlHandler);
    #endif

    sleepMs (2000);

    while((!terminateProgram) && (!modem->terminationRequired)){
        #ifndef WIN32
            system("clear");
        #endif
        beaconAddress = -1;
        switch(menuPrincipal()){
            case 1:{ /* Status */
                while (beaconAddress < 0 || beaconAddress > 255){
                    printf("\nIntroduisez la balise ciblee: ");
                    scanf("%d", &beaconAddress);
                }
                
                cmd = CMD_STATE;
                printf("\nAsking beacon number %d its state...\n", beaconAddress);
                printf("Press ENTER to continue...\n");
                #ifndef WIN32
                    getchar();
                    getchar();
                #endif
                break;
            }
            case 2:{ /* Wake */
                /*askbeaconAddress(beaconAddress);
                printf("beaconAddress: %s", beaconAddress);*/
                break;
            }
            case 3:{ /* Send Command */
                /*askbeaconAddress(beaconAddress);
                printf("beaconAddress: %s", beaconAddress);*/
                break;
            }
            case 0:{
                /* sortie*/
                printf("Au revoir!\n");
                // Exit
                stopMarvelmindModem(modem);
                destroyMarvelmindModem(modem);
                return 0;
            }
        }

        trySendCommand(modem, cmd, (uint8_t) beaconAddress);

        sleepMs (500);
    }

    // Exit
    stopModemThread(modem);
    return 0;
}