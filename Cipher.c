#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TERMS 20
#define MAX_STR 200

int charToNumber(char ch) {
    if ('a' <= ch && ch <= 'z') {
        return ch - 'a';
    }
    else if ('A' <= ch && ch <= 'Z') {
        return ch - 'A';
    }
    return 0; // Return 0 instead of '\0' for an integer value
}

void removeExtraSpaces(char* str) {
    int i, j,n;
    int spaceFound = 0;
    for (i = 0, j = 0; i < strlen(str); i++) {
        if (str[i] == ' ') {
            if (!spaceFound) {
                str[j++] = ' ';
                spaceFound = 1;
            }
        }
        else {
            str[j++] = str[i];
            spaceFound = 0;
        }
    }
    str[j] = '\0';
}

void resetTerms(char* terms[]) {
    for (int i = 0; i < MAX_TERMS; i++) {
        terms[i] = NULL;
    }
}

void encode(char str[], char key[], char e[], char* terms[]) {
    resetTerms(terms); // Reset the array of pointers
    while (*str == ' ') { //remove unnecessary spaces in the began of the sentence
        str++;
    }
    int j = 0;
    int termIndex = 0;
    terms[termIndex] = &e[0]; // Always set the first element to &e[0]
    removeExtraSpaces(str); //remove unnecessary spaces
    int isAllSpaces = 1;
    for (int i = 0; i < strlen(str); i++) { // Check if the string consists only of spaces
        if (str[i] != ' ') {
            isAllSpaces = 0;
            break;
        }
    }
    if (isAllSpaces) {
        terms[termIndex + 1] = NULL; // Set the second element to NULL if the string is full of spaces
        strcpy(e, str);
        return; 
    }
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ' ') {
            i++;
            termIndex++;
            terms[termIndex] = &e[i];
        }
        int f = charToNumber(key[j]);
        int encodedChar = str[i] + f;
        if (encodedChar > 'z') {
            int d = 'z' - str[i];
            if (f > d) {
                f = charToNumber(key[j]) - d;
                str[i] = 'a' + f - 1;
            }
        }
        else {
            str[i] = encodedChar;
        }
        if (j != strlen(key) - 1) {
            j++;
        }
        else {
            j = 0;
        }
    }
    terms[termIndex + 1] = NULL;
    strcpy(e, str);
}

int getArrayLength(char* arr[]) {
    int length = 0;
    while (arr[length] != NULL) {
        length++;
    }
    return length;
}

void getIthElement(char* terms[], int i, char out[]) {
    if (i >= 0 && i < getArrayLength(terms)) {
        if (terms[i] != NULL && terms[i][0] != '\0') { 
            int j = 0;
            int start = 0;
            // Find the starting position of the word
            while (terms[i][start] != '\0' && terms[i][start] == ' ') {
                start++;
            }
            // Copy the word until the next space
            for (start; terms[i][start] != '\0' && terms[i][start] != ' '; start++) {
                out[j++] = terms[i][start];
            }
            out[j] = '\0'; 
        }
        else {
            strcpy(out, "Empty string");
        }
    }
    else {
        strcpy(out, "Invalid index");
    }
}

int main() {
    char str[MAX_STR] = "we love c course";
    char key[] = "atlm";
    char e[MAX_STR];
    char* terms[MAX_TERMS];
    char out[MAX_STR];

    encode(str, key, e, terms);

    printf("Encoded string: %s\n", e);

    for (int i = 0; i < getArrayLength(terms); i++) {
        getIthElement(terms, i, out);
        printf("Term %d: %s\n", i + 1, out);
    }

    return 0;
}


