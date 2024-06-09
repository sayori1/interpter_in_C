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
} VarDeclarationNode;

VarDeclarationNode *varDeclarationNodeCreate(char *name, Node *expr)
{
    VarDeclarationNode *assignNode = (VarDeclarationNode *)malloc(sizeof(VarDeclarationNode));
    assignNode->base.type = ASSIGN;
    assignNode->name = name;
    assignNode->expr = expr;

    return assignNode;
}

VarDeclarationNode *parseAssign(Parser *self)
{
    eatToken(self->lexer, VAR);
    Lexem *varName = eatToken(self->lexer, ID);
    eatToken(self->lexer, OPERATOR);
    Node *expr = parsePlusMinus(self);

    return varDeclarationNodeCreate((char *)varName->value, expr);
}

#endif // !ASSIGNMENT_NODE_H