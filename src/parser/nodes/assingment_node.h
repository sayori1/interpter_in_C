#include "node.h"
#include <stdlib.h>

#ifndef ASSIGNMENT_NODE_H
#define ASSIGNMENT_NODE_H

typedef struct{
    Node base;

    char* name;
    Node* expr;
} AssignNode;

AssignNode* assignNodeCreate(char* name, Node* expr){
    AssignNode* assignNode = (AssignNode*)malloc(sizeof(AssignNode));
    assignNode->base.type = ASSIGN;
    assignNode->name = name;
    assignNode->expr = expr;

    return assignNode;
}



#endif // !ASSIGNMENT_NODE_H