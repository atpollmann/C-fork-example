/**
 * Terminates the execution of the program
 * with a message to stdout
 */
void terminateWithMessage(const char*);

/**
 * Counts the number of ocurreces of
 * needle inside str
 */
int strCountFind(char* str, char needle);

/**
 * Given a string and a delimiter, it splits
 * the string into an array of string
 * delimited by the delimiter
 */
char** splitLine(char* str, const char* delimiter);

/**
 * Converts a string into a double
 */
double stringToDouble(char *str);

/**
 * Converts a string into an integer
 */
int stringToInt(char* str);