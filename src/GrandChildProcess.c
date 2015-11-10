#include <stdio.h>
#include <stdlib.h>
#include "GrandChildProcess.h"
#include "FinancialAsset.h"

void executeGrandChildProcess(GrandChildProcess *process, char *dataFilename) {	
    float valorization = parseFile(process->fundType, process->assetType, dataFilename);
    write(process->pipe[1], &valorization, sizeof(valorization));
}

float parseFile(char ft, char at, char *dataFilename) {

    FinancialAsset fa;
    float valorization = 0;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    fp = fopen(dataFilename, "r");
    if(fp == NULL) {
        printf("Could not read file %s\n", dataFilename);
        exit(EXIT_FAILURE);
    }
    while(getline(&line, &len, fp) != -1) {
        // We could build a financial asset from every line
        // but that would be very time consuming.
        // A better aproach would be to examine the first
        // byte of the line, where its supposed to live
        // the fundtype, and if it matches, build the asset
        char currentFundType = line[0];
        if(currentFundType == ft) {
            fa = buildFinancialAsset(line);
            if (fa.assetType == at) {
            	valorization += getFundValorization(&fa);
            }
        }
    }
    free(line);
    return valorization;
}
