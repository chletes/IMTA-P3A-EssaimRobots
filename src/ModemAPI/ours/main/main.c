#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <signal.h>
#endif // WIN32
#include "../modem/modem.h"
//#include "main.h"

uint32_t requestRepeatsCount = 1;

#define CMD_STATE 0
#define CMD_SLEEP 1
#define CMD_DEEPSLEEP 2
#define CMD_WAKE 3

bool terminateProgram = false;

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

int menuPrincipal(){
    int valor;
    printf("Choisisez une option pour continuer, puis appuyez ENTER:\n \
    \t 1. Retrouver l'etat d'une balise \n \
    \t 2. Wake balises \n \
    \t 3. Sleep balises \n \
    \t 4. Send command \n \
    \t *N'importe quel numéro pour sortir...*\n \
    Option choisie: ");
    scanf("%d", &valor);
    return valor;
}

int main(int argc, char *argv[]){
    
    const char * ttyFileName= DEFAULT_TTY_FILENAME;
    int beaconAddress = -1;
    uint8_t cmd = -1;

    // Init
    struct MarvelmindModem * modem=createMarvelmindModem ();
    if (modem==NULL){
        printf("Error: Unable to create MarvelmindModem");
        return -1;
    }
    modem->ttyFileName=ttyFileName;
    modem->verbose=true; // show errors and warnings
    startMarvelmindModem (modem);

    // Set Ctrl-C handler
    #ifdef WIN32
        SetConsoleCtrlHandler( (PHANDLER_ROUTINE) CtrlHandler, TRUE );
    #else
        signal (SIGINT, CtrlHandler);
        signal (SIGQUIT, CtrlHandler);
    #endif

    sleepMs (500);

    while(1){
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
        // Main loop
        while ((!terminateProgram) && (!modem->terminationRequired)){

            trySendCommand(modem, cmd, beaconAddress);

            if (requestRepeatsCount == 0){
                modem->terminationRequired = true;
            }

            sleepMs (500);
        }
    }

    // Exit
    stopMarvelmindModem (modem);
    destroyMarvelmindModem (modem);
    return 0;
}