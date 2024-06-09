#include "node.h"
#include <stdlib.h>
#include "parser/parser.h"
#include "expression_node.h"

#ifndef ASSIGNMENT_NODE_H
#define ASSIGNMENT_NODE_H

typedef struct
{
    Node base;

    char *name;
    Node *expr;
} AssignNode;

AssignNode *assignNodeCreate(char *name, Node *expr)
{
    AssignNode *assignNode = (AssignNode *)malloc(sizeof(AssignNode));
    assignNode->base.type = ASSIGN;
    assignNode->name = name;
    assignNode->expr = expr;

    return assignNode;
}

AssignNode *parseAssign(Parser *self)
{
    eatToken(self->lexer, VAR);
    Lexem *varName = eatToken(self->lexer, ID);
    eatToken(self->lexer, OPERATOR);
    Node *expr = parsePlusMinus(self);

    return assignNodeCreate((char *)varName->value, expr);
}

#endif // !ASSIGNMENT_NODE_H