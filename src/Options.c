#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Options.h"
#include "utils.h"

void getOptions(Options *option, int argc, char **argv) {
    // 1 or 5
    int fundsCount = 5;
    // 0 = Fixed, 1 = Variable, 2 = All
    int assetType = 2;
    // In case OPT_FUNDS_COUNT = 1
    // 0 = A, 1 = B, 2 = C, 3 = D, 4 = E
    int fundSelection = 1;
    // The filename of the data file
    char *filename = NULL;

    char fund;
    char *assetTypeSelection;

    int opt;
    char msg[100];

    while((opt = getopt(argc, argv, "f:t:r:")) != -1) {
        switch(opt) {
            case 'f':
                filename = optarg;
                if(access(filename, R_OK) != 0) {
                    sprintf(msg, "El archivo %s no esta disponible", filename);
                    terminateWithMessage(msg);
                }
                break;
            case 't':
                fund = optarg[0];
                if(fund == 'A') fundSelection = 0;
                else if(fund == 'B') fundSelection = 1;
                else if(fund == 'C') fundSelection = 2;
                else if(fund == 'D') fundSelection = 3;
                else if(fund == 'E') fundSelection = 4;
                else {
                    printf("Fondo invalido (%s)\n\n", optarg);
                    printUsage(argv[0]);
                    exit(EXIT_SUCCESS);
                }
                fundsCount = 1;
                break;
            case 'r':
                assetTypeSelection = optarg;
                if(strcmp(assetTypeSelection, "RF") == 0) assetType = 0;
                else if(strcmp(assetTypeSelection, "RV") == 0) assetType = 1;
                else {
                    printf("Tipo de renta invalida (%s)\n\n", optarg);
                    printUsage(argv[0]);
                    exit(EXIT_SUCCESS);
                }
                break;
            default:
                printUsage(argv[0]);
                abort();
        }
    }

    if(filename == NULL) {
        printUsage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    option->filename = filename;
    option->assetType = assetType;
    option->fundsCount = fundsCount;
    option->fundSelection = fundSelection;
}

void printUsage(char *binaryName) {
    printf("\nUso: %s -f <archivo> [-t <A|B|C|D|E>] [-r <RF|RV>]\n\n", binaryName);
    printf("Ejemplos:\n");
    printf("%s -f data.txt\n", binaryName);
    printf("\t- Imprime la valorizacion de todos los fondos\n\n");
    printf("%s -f data.txt -t C\n", binaryName);
    printf("\t- Imprime la valorizacion del fondo C\n\n");
    printf("%s -f data.txt -r RV\n", binaryName);
    printf("\t- Imprime la valorizacion de renta variable para todos los fondos\n\n");
    printf("%s -f data.txt -t B -r RF\n", binaryName);
    printf("\t- Imprime la valorizacion de renta fija para el fondo B\n\n");
}
