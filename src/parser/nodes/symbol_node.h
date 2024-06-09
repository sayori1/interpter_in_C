#include "node.h"
#include <stdlib.h>

#ifndef SYMBOL_NODE
#define SYMBOL_NODE

typedef struct{
    Node base;

    char* name;
} SymbolNode;

SymbolNode* symbolNodeCreate(char* name){
    SymbolNode* symbolNode = (SymbolNode*)malloc(sizeof(SymbolNode));
    symbolNode->base.type = VAR_LITERAL;
    symbolNode->name = name;

    return symbolNode;
}

#endif