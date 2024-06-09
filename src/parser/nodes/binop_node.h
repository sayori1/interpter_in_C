
#include "node.h"
#include <lexer/lexem.h>
#include <parser/parser.h>
#include "parser/nodes/symbol_node.h"

#ifndef BINOP_NODE
#define BINOP_NODE

// Function prototypes
Node *parsePlusMinus(Parser *self);

typedef struct
{
    Node base;

    Node *left;
    Node *right;
    Lexem *op;
} BinOpNode;

BinOpNode *binOpNodeCreate(Node *left, Node *right, Lexem *op)
{
    BinOpNode *self = (BinOpNode *)malloc(sizeof(BinOpNode));

    self->base.type = BINOP;
    self->left = left;
    self->right = right;
    self->op = op;

    return self;
}

Node *parseLiteral(Parser *self)
{
    Lexem *lexem = self->lexer->currentLexem;

    switch (lexem->type)
    {
    case NUM:
        eatToken(self->lexer, NUM);
        return (Node *)numNodeCreate((int)lexem->value);
    case PARB:
        eatToken(self->lexer, PARB);
        Node *expr = parsePlusMinus(self);
        eatToken(self->lexer, PARE);
        return expr;
    case ID:
        eatToken(self->lexer, ID);
        return (Node *)symbolNodeCreate((char *)lexem->value);
    default:
        return NULL;
    }
}

Node *parseMulDiv(Parser *self)
{
    Node *left = parseLiteral(self);
    Lexem *lexem = self->lexer->currentLexem;

    while (lexem->type == OPERATOR && ((char)lexem->value == '*' || (char)lexem->value == '/'))
    {
        char op = (char)lexem->value;
        eatToken(self->lexer, OPERATOR);
        Node *right = parseLiteral(self);

        if (op == '*')
        {
            left = (Node *)binOpNodeCreate(left, right, lexem);
        }
        else if (op == '/')
        {
            left = (Node *)binOpNodeCreate(left, right, lexem);
        }

        lexem = self->lexer->currentLexem;
    }

    return left;
}

Node *parsePlusMinus(Parser *self)
{
    Node *left = parseMulDiv(self);
    Lexem *lexem = self->lexer->currentLexem;

    while (lexem->type == OPERATOR && ((char)lexem->value == '+' || (char)lexem->value == '-'))
    {
        char op = (char)lexem->value;
        eatToken(self->lexer, OPERATOR);
        Node *right = parseMulDiv(self);

        if (op == '+')
        {
            left = (Node *)binOpNodeCreate(left, right, lexem);
        }
        else if (op == '-')
        {
            left = (Node *)binOpNodeCreate(left, right, lexem);
        }

        lexem = self->lexer->currentLexem;
    }

    return left;
}

#endif // !BINOP_NODE