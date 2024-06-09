
#include "node.h"
#include <lexer/lexem.h>

#ifndef BINOP_NODE
#define BINOP_NODE


typedef struct{
    Node base;

    Node* left;
    Node* right;
    Lexem* op;
} BinOpNode;

BinOpNode* binOpNodeCreate(Node* left, Node* right, Lexem* op){
    BinOpNode* self = (BinOpNode*)malloc(sizeof(BinOpNode));

    self->base.type = BINOP;
    self->left = left;
    self->right = right;
    self->op = op;

    return self;
}

#endif // !BINOP_NODE