#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "Options.h"
#include "ChildProcess.h"
#include "utils.h"

int main(int argc, char** argv) {

    Options opt;
    getOptions(&opt, argc, argv);

    char fundTypes[MAX_FUND_TYPES] = {'A','B','C','D','E'};
    char assetTypes[MAX_ASSET_TYPES] = {'F', 'V', 'A'};
    int i;
    int status;
    double valorization;
    char* filename = opt.filename;
    int fc = opt.fundsCount;
    int at = opt.assetType;
    int fs = opt.fundSelection;

    ChildProcess childs[fc];

    // It can be only one fund or all five of them
    // One child process for each
    if(fc == 1) {
        childs[0].fundType = fundTypes[fs];
        childs[0].assetType = assetTypes[at];
        pipe(childs[0].pipe);
    } else {
        for (i = 0; i < fc; i++) {
            childs[i].fundType = fundTypes[i];
            childs[i].assetType = assetTypes[at];
            pipe(childs[i].pipe);
        }
    }

    // Spawn childs
    for (i = 0; i < fc; i++) {
        pid_t pid = fork();
        if(pid < 0) terminateWithMessage("No se pudo crear proceso");
        else if(pid == 0) {
            close(childs[i].pipe[0]);
            executeChildProcess(&childs[i], filename);
            exit(EXIT_SUCCESS);
        } else {
            close(childs[i].pipe[1]);
        }
    }

    // Collect results
    printf("Resultado Valorizacion:\n");
    printf("=======================\n\n");
    for (i = 0; i < fc; i++) {
        wait(&status);
        read(childs[i].pipe[0], &valorization, sizeof(valorization));
        printf("Total valorizacion tipo de fondo %c: %f\n", childs[i].fundType, valorization);
    }

    return 0;
}

