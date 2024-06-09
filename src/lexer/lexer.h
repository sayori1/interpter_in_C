
#ifndef UNTITLED5_LEXER_H
#define UNTITLED5_LEXER_H

#include "core/char_utils.h"
#include "lexem.h"
#include <ctype.h>
#include <string.h>

typedef struct {
    char* text;
    int currentPosition;
    char currentChar;
    Lexem* currentLexem;
} Lexer;

Lexem* getNextToken(Lexer* self);

Lexer* lexerCreate(char* text){
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));

    lexer->text = text;
    lexer->currentPosition = 0;
    lexer->currentChar = lexer->text[lexer->currentPosition];
    lexer->currentLexem = getNextToken(lexer);

    return lexer;
}

char advance(Lexer* self){
    if(self->currentPosition >= strlen(self->text)){
        self->currentChar = '\0';
    }
    else{
        self->currentPosition += 1;
        self->currentChar = self->text[self->currentPosition];
    }
    return self->currentChar;
}

Lexem* handleNum(Lexer* self){
    char* buffer = "";
    while(isdigit(self->currentChar)){
        buffer = charsAppend(buffer, self->currentChar);
        advance(self);
    }

    int v = atoi(buffer);

    return lexemCreate(NUM, v);
}

Lexem* handleCompoundOperator(Lexer* self, char first, char second){
    char* buffer = (char*) malloc(sizeof(char) * 4);

    buffer[0] = first;
    buffer[1] = second;
    buffer[2] = '\0';

    return lexemCreate(COMPOUND_OPERATOR, buffer);
}

Lexem* eatToken(Lexer* self, LexemType type){
    if(self->currentLexem->type == type){
        Lexem* lexem = self->currentLexem;
        self->currentLexem = getNextToken(self);
        return lexem;
    }
    else{


        fprintf(stderr, "Error: Unexpected token. Expected %d, get %d \n", type, self->currentLexem->type );
    }
}

Lexem* getNextToken(Lexer* self){
    if(isspace(self->currentChar)){
        while(isspace(self->currentChar)){
            advance(self);
        }
    }

    char currentCh = self->text[self->currentPosition];

    if(currentCh == '\0'){
        return lexemCreate(END, 0);
    }
    else if(isdigit(currentCh)){
        return handleNum(self);
    }
    else if(isoperator(currentCh)){
        advance(self);
        if(isoperator(self->currentChar)){
            Lexem* lexem = handleCompoundOperator(self, currentCh, self->currentChar);
            advance(self);

            return lexem;
        }
        else
            return lexemCreate(OPERATOR, currentCh);
    }
    else if(currentCh == '('){
        advance(self);
        return lexemCreate(PARB, currentCh);
    }
    else if(currentCh == ')'){
        advance(self);
        return lexemCreate(PARE, currentCh);
    }
    else if(currentCh == '{'){
        advance(self);
        return lexemCreate(COMB, currentCh);
    }
    else if(currentCh == '}'){
        advance(self);
        return lexemCreate(COME, currentCh);
    }
    else if(currentCh == ';'){
        advance(self);
        return lexemCreate(STATEMEND_END, currentCh);
    }
    else if(isalpha(currentCh)){
        char* buffer = "";
        while(isalpha(self->currentChar)){
            buffer = charsAppend(buffer, self->currentChar);
            advance(self);
        }

        if(strcmp(buffer, "var") == 0){
            return lexemCreate(VAR, buffer);
        }
        else{
            return lexemCreate(ID, buffer);
        }
    }
    else{
        fprintf(stderr, "Error: Invalid character.\n");
    }
}

#endif //UNTITLED5_LEXER_H
