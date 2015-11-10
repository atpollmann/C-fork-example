#include <stdio.h>
#include <stdlib.h>
#include "ChildProcess.h"
#include "utils.h"

void executeChildProcess(ChildProcess *childProcess, char *dataFilename) {
    int gcCount = (childProcess->assetType == 'A') ? 2 : 1;
    GrandChildProcess grandChilds[gcCount];
    buildGCList(grandChilds, gcCount, childProcess);
    spawnGrandChilds(grandChilds, gcCount, dataFilename);
    processGrandChildsResponses(grandChilds, childProcess, gcCount);
}

char getCurrentAssetType(char sat, int gcp) {
    return (sat == 'A') ? (char) ((gcp == 0) ? 'F' : 'V') : sat;
}

void buildGCList(GrandChildProcess *gcl, int gcCount, ChildProcess *cp) {
    int i;
    for (i = 0; i < gcCount; i++) {
        gcl[i].fundType = cp->fundType;
        gcl[i].assetType = getCurrentAssetType(cp->assetType, i);
        pipe(gcl[i].pipe);
    }
}

void spawnGrandChilds(GrandChildProcess *gcl, int gcCount, char *dataFilename) {
    int i;
    for (i = 0; i < gcCount; i++) {
        pid_t pid = fork();
        if(pid < 0) terminateWithMessage("No se pudo crear proceso nieto");
        else if(pid == 0) {
            close(gcl[i].pipe[0]);
            executeGrandChildProcess(&gcl[i], dataFilename);
            exit(EXIT_SUCCESS);
        } else {
            close(gcl[i].pipe[1]);
        }
    }
}

void processGrandChildsResponses(GrandChildProcess *gcl, ChildProcess *cp, int gcCount) {
    int i, status;
    double buffer, valorization = 0.0;
    for (i = 0; i < gcCount; i++) {
        wait(&status);
        read(gcl[i].pipe[0], &buffer, sizeof(buffer));
        valorization = (double)valorization + (double)buffer;
    }
    write(cp->pipe[1], &valorization, sizeof(valorization));
}

