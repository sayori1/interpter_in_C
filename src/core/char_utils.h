//
// Created by almetoff on 05.06.2024.
//

#ifndef UNTITLED5_CHAR_UTILS_H
#define UNTITLED5_CHAR_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

char* charsAdd(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char* result = (char*)malloc(len1 + len2 + 1);

    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    strcpy(result, str1);
    strcat(result, str2);

    return result;
}

char* charsAppend(char* str, char ch){
    size_t len = strlen(str);

    char *new_str = (char*)malloc(strlen(str) * (sizeof(char) + 2));

    if (new_str == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return str;
    }

    strcpy(new_str, str);

    new_str[len] = ch;
    new_str[len + 1] = '\0';
    return new_str;
}

char* charsFormat(const char* format, ...) {
    va_list args;
    va_start(args, format);

    int length = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);

    char* formatted_string = (char*)malloc(length);
    if (formatted_string == NULL) {
        return NULL;
    }

    va_start(args, format);
    vsnprintf(formatted_string, length, format, args);
    va_end(args);

    return formatted_string;
}

int isoperator(char ch) {
    switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%': // Modulus operator
        case '^': // Exponentiation operator
        case '&': // Bitwise AND operator
        case '|': // Bitwise OR operator
        case '~': // Bitwise NOT operator
        case '!': // Logical NOT operator
        case '=': // Assignment operator
        case '<': // Less than operator
        case '>': // Greater than operator
            return 1;
        default:
            return 0;
    }
}

#endif //UNTITLED5_CHAR_UTILS_H
