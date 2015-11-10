#include <unistd.h>

typedef struct grandChildProcess {
    char fundType;
    char assetType;
    double valorization;
    pid_t pid;
    int pipe[2];
}GrandChildProcess;

/**
 * Executes the given grandchild process
 */
void executeGrandChildProcess(GrandChildProcess *grandChildProcess, char *dataFilename);

/**
 * The function that finally does the work.
 * It walks through every line of the data file
 * building a financialasset structure out of
 * every line that has the given fundtype and
 * assettype and computes the asset's valorization
 *
 * from http://linux.die.net/man/3/getline
 *
 * @param   char    The fund type
 * @param   char    The asset type
 * @returns foat    The funds total valorization
 */
double parseFile(char fundType, char assetType, char *dataFilename);
