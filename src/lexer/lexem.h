
#ifndef UNTITLED5_LEXEM_H
#define UNTITLED5_LEXEM_H

#include <stdlib.h>

typedef enum {
    NUM,
    STR,
    OPERATOR,
    COMPOUND_OPERATOR,
    PARB,
    PARE,
    COMB,
    COME,
    VAR,
    ID,
    STATEMEND_END,
    END
} LexemType;

typedef struct {
    LexemType type;
    void* value;
} Lexem;

Lexem* lexemCreate(LexemType type, void* value){
    Lexem* lexem = malloc(sizeof(Lexem));
    lexem->type = type;
    lexem->value = value;
    return lexem;
}

char* lexemToString(Lexem* self){
    if(self->type == NUM)
        return charsFormat("Lexem(type: %d, value: %d)", self->type, self->value);
    else if(self->type == STR)
        return charsFormat("Lexem(type: %d, value: %s)", self->type, self->value);
    else if(self->type == OPERATOR)
        return charsFormat("Lexem(type: %d, value: %c)", self->type, self->value);
    else if(self->type == COMPOUND_OPERATOR)
        return charsFormat("Lexem(type: %d, value: %s)", self->type, self->value);
    else if(self->type == PARB)
        return "Lexem(PARENTHESES BEGIN)";
    else if(self->type == PARE)
        return "Lexem(PARENTHESES END)";
    else if(self->type == COMB)
        return "Lexem(Compound BEGIN)";
    else if(self->type == COME)
        return "Lexem(Compound END)";
    else if(self->type == END)
        return "Lexem(END)";
    else if(self->type == VAR)
        return charsFormat("Lexem(VAR type: %d, value: %s)", self->type, self->value);
    else if(self->type == ID)
        return charsFormat("Lexem(ID type: %d, value: %s)", self->type, self->value);
    else if(self->type == STATEMEND_END){
        return "Lexem(STATEMENT END)";}
    else
        return "Lexem(UNKNOWN)";
}

#endif //UNTITLED5_LEXEM_H
