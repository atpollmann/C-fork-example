#include <unistd.h>
#include "GrandChildProcess.h"

typedef struct childProcess {
    char fundType;
    char assetType;
    int pipe[2];
}ChildProcess;

/**
 * Executes the given childprocess
 */
void executeChildProcess(ChildProcess *childProcess, char *dataFilename);

/**
 * Given the user's selected asset type (A,F or V)
 * and the position of the grandchilds queue, returns the
 * final asset type corresponding to that position
 *
 * @param   char    User's selected asset type
 * @param   int     GrandChild queue position
 */
char getCurrentAssetType(char selectedAssetType, int GrandChildPosition);

/**
 * Builds the grandchilds processes list based
 * on the information given by the childprocess
 * structure
 *
 * @param   *grandChildProcess  Pointer to the array that will
 *                              hold the granchild processes
 * @param   listCount           The length of the array
 * @param   childProcess        The childprocess structure
 */
void buildGCList(GrandChildProcess *grandChildsList,
                 int listCount,
                 ChildProcess *childProcess);

/**
 * Creates all the grandchild processes
 * given in the list
 *
 * @param GranChildProcess  List of grandchild processes to deploy
 * @param int               Length of the list
 */
void spawnGrandChilds(GrandChildProcess *grandChildProcessesList, int listCount, char *dataFilename);

/**
 * Process the responses given by the list of grandchilds
 * It waits untill all of them have exited
 *
 * @param GranChildProcess  List of grandchild processes to process
 * @param int               Length of the list
 */
void processGrandChildsResponses(GrandChildProcess *grandChildProcessesList,
                                 ChildProcess *childProcess,
                                 int gcCount);
