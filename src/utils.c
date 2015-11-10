#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void terminateWithMessage(const char* message) {
    printf("%s\n", message);
    exit(EXIT_SUCCESS);
}

int strCountFind(char* str, char needle) {
    size_t len = strlen(str);
    int i, count = 0;
    for (i = 0; i < len; i++) {
        if(str[i] == needle) count++;
    }
    return count;
}

char** splitLine(char* str, const char* delimiter) {
    int i = 0, count = strCountFind(str, ';') + 1;
    char** result = malloc(sizeof(char*) * count);
    char* token = strtok(str, delimiter);

    while(token != NULL) {
        char *buffer = (char *) malloc(strlen(token));
        strcpy(buffer, token);
        result[i] = buffer;
        i++;
        token = strtok(NULL, delimiter);
    }

    return result;
}

double stringToDouble(char *str) {
    return (double) atof(str);
}
int stringToInt(char* str) {
    return atoi(str);
}