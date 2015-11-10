#define MAX_FUND_TYPES 5
#define MAX_ASSET_TYPES 3

typedef struct options{
    char *filename;
    int fundsCount;
    int fundSelection;
    int assetType;
}Options;

/**
 * Returns the user option using getopt
 */
void getOptions(Options *opt, int argc, char **argv);

/**
 * Prints the program usage
 */
void printUsage(char *binaryName);