#include "node.h"
#include <stdlib.h>
#include <parser/parser.h>
#include "var_declaration_node.h"

#ifndef STATEMENT_NODE
#define STATEMENT_NODE

typedef struct
{
    Node base;

    Node *child;

} StatementNode;

StatementNode *statementNodeCreate(Node *child)
{
    StatementNode *statementNode = (StatementNode *)malloc(sizeof(StatementNode));
    statementNode->base.type = STATEMENT;
    statementNode->child = child;

    return statementNode;
}

Node *parseStatement(Parser *self)
{
    Node *node = NULL;
    if (self->lexer->currentLexem->type == VAR)
    {
        node = (Node *)parseAssign(self);
    }
    eatToken(self->lexer, STATEMEND_END);

    return (Node *)statementNodeCreate(node);
}

#endif // !STATEMENT_NODE