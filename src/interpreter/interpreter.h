
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <core/map.h>


typedef struct{
    Map* variables;
} Interpreter;


Interpreter* interpreterCreate(){
    Interpreter* interpreter = (Interpreter*)malloc(sizeof(Interpreter));
    interpreter->variables = mapCreate(10);
    return interpreter;
}


void addVariable(Interpreter* self, char* name, int value){
    mapSet(self->variables, name, (void*)value);
}

#endif
