typedef struct financialAsset{
    char fundType;
    char assetType;
    double amount;
    double rate;
    double price;
    int daysUntilValid;
}FinancialAsset;

/**
 * Given a file record, builds the corresponding
 * financialAsset struct of it
 *
 * @param char* Line of file
 * @return FinancialAsset struct
 */
FinancialAsset buildFinancialAsset(char* line);

/**
 * Based on the assettype, applys the corresponding
 * formula to obtain its valorization
 *
 * @param FinancialAsset    Pointer to the financialasset structure
 */
double getFundValorization(FinancialAsset *fa);

/**
 * Given the financialInstrumentTypeId
 * return what kind of assettype corresponds
 * (F)ixed or (V)ariable
 *
 * @param   char*   Financial instrument type id (ie.: ACC, ACE, DPF)
 * @return  char    Asset type (F or V)
 */
char getAssetType(char *financialInstrumentTypeId);
