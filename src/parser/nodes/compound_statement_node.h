
#include "node.h"
#include "statement_node.h"

#ifndef COMPOUND_STATEMENT_H
#define COMPOUND_STATEMENT_H


typedef struct{
    Node base;

    StatementNode** statements;
    int count;
} CompoundNode;

CompoundNode* compoundNodeCreate(){
    CompoundNode* compoundNodeCreate = (CompoundNode*)malloc(sizeof(CompoundNode));
    compoundNodeCreate->base.type = COMPOUND;
    compoundNodeCreate->count = 0;
    compoundNodeCreate->statements = (StatementNode**)malloc(sizeof(StatementNode*));

    return compoundNodeCreate;
}

void compoundNodeAddStatement(CompoundNode* compoundNode, StatementNode* node){
    compoundNode->count += 1;

    compoundNode->statements = (StatementNode**)realloc(compoundNode->statements, sizeof(StatementNode*) * (compoundNode->count));

    compoundNode->statements[compoundNode->count-1] = node;
}

#endif // !COMPOUND_STATEMENT_H