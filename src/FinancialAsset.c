#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "FinancialAsset.h"
#include "utils.h"

FinancialAsset buildFinancialAsset(char *line) {

    char **split = splitLine(line, ";");
    FinancialAsset fa;

    fa.fundType         = *split[0];
    fa.assetType        = getAssetType(split[2]);
    fa.amount           = stringToFloat(split[3]);
    fa.rate             = stringToFloat(split[4]);
    fa.price            = stringToFloat(split[5]);
    fa.daysUntilValid   = stringToInt(split[6]);

    free(split);

    return fa;
}

char getAssetType(char *id) {
    int i;
    char* fixed[2] = {"DPF", "ECO"};

    for(i = 0; i < 2; i++) {
        if (strcmp(id, fixed[i]) == 0) return 'F';
    }

    return 'V';
}

float getFundValorization(FinancialAsset *fa) {
    float valorization;
    if(fa->assetType == 'F') {
        valorization =  (float) (fa->amount / (1.0 + (fa->rate / 360.0) * fa->daysUntilValid / 100));
    } else {
        valorization = fa->amount * fa->price;
    }
    return valorization;
}
