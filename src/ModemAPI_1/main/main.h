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

#define CMD_STATE 0
#define CMD_SLEEP 1
#define CMD_DEEPSLEEP 2
#define CMD_WAKE 3

bool terminateProgram = false;

/**
 * @brief Asks the user what to do.
 *
 *  1. Retrouver l'etat d'une ou plusieures balises - send status request
 *  2. Wake / Sleep balises 
 *  3. Send command
 *
 * @return 1, 2 or 3, depending on the action chosen. 
 */
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
};

/**
 * @brief Do something depending on the result of menuPrincipal()
 *
 * Returns a (standard) 0 for success.
 *
 * @return 0
 */
int main(int argc, char *argv[]);