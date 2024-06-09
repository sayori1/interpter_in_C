#include "node.h"
#include <stdlib.h>

#ifndef STATEMENT_NODE
#define STATEMENT_NODE



typedef struct{
    Node base;

    Node* child;

} StatementNode;


StatementNode* statementNodeCreate(Node* child){
    StatementNode* statementNode = (StatementNode*)malloc(sizeof(StatementNode));
    statementNode->base.type = STATEMENT;
    statementNode->child = child;

    return statementNode;
}


#endif // !STATEMENT_NODE