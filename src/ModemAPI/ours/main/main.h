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
//#include "process.h"

/**
 * @brief Asks the user what to do.
 *
 *  1. Retrouver l'etat d'une ou plusieures balises - send status request
 *  2. Wake / Sleep balises 
 *  3. Send command
 *
 * @return 1, 2 or 3, depending on the action chosen. 
 */
int menuPrincipal();

/**
 * @brief Do something depending on the result of menuPrincipal()
 *
 * Returns a (standard) 0 for success.
 *
 * @return 0
 */
int main(int argc, char *argv[]);