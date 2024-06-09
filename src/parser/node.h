//
// Created by admin on 6/7/2024.
//

#ifndef UNTITLED5_AST_H
#define UNTITLED5_AST_H

#include "lexer/lexem.h"
#include <stdlib.h>
#include "core/char_utils.h"

typedef enum {
    NUMBER,
    BINOP,
    VAR_LITERAL,
    COMPOUND,
    STATEMENT,
    ASSIGN
} NodeType;

typedef struct{
    NodeType type;
} Node;


typedef struct{
    Node base;
    int value;
} NumNode;

NumNode* numNodeCreate(int value){
    NumNode* self = (NumNode*)malloc(sizeof(NumNode));
    self->base.type = NUMBER;
    self->value = value;

    return self;
}

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

typedef struct{
    Node base;

    char* name;
} VarLiteralNode;

VarLiteralNode* varLiteralNodeCreate(char* name){
    VarLiteralNode* varLiteralNode = (VarLiteralNode*)malloc(sizeof(VarLiteralNode));
    varLiteralNode->base.type = VAR_LITERAL;
    varLiteralNode->name = name;

    return varLiteralNode;
}


typedef struct{
    Node base;

    Node* child;

} StatementNode;

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

StatementNode* statementNodeCreate(Node* child){
    StatementNode* statementNode = (StatementNode*)malloc(sizeof(StatementNode));
    statementNode->base.type = STATEMENT;
    statementNode->child = child;

    return statementNode;
}

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


char* nodeToString(Node* node){
    if(node->type == NUMBER){
        NumNode* numNode = (NumNode*)node;
        return charsFormat("NumNode(value: %d)", numNode->value);
    }
    else if(node->type == BINOP){
        BinOpNode* binOpNode = (BinOpNode*)node;
        return charsFormat("BinOpNode(left: %s, right: %s, op: %s)", nodeToString(binOpNode->left), nodeToString(binOpNode->right), lexemToString(binOpNode->op));
    }
    else if(node->type == COMPOUND){
        CompoundNode* compoundNode = (CompoundNode*)node;
        char* buffer = "";
        for(int i = 0; i < compoundNode->count; i++){
            buffer = charsFormat("%s%s;", buffer, nodeToString((Node*)  compoundNode->statements[i]));
        }
        return charsFormat("CompoundNode(statements: %s)", buffer);
    }
    else if(node->type == STATEMENT){
        StatementNode* statementNode = (StatementNode*)node;
        return charsFormat("StatementNode(child: %s)", nodeToString(statementNode->child));
    }
    else if(node->type == ASSIGN){
        AssignNode* assignNode = (AssignNode*)node;
        return charsFormat("AssignNode(name: %s, expr: %s)", assignNode->name, nodeToString(assignNode->expr));
    }
    else if(node->type == VAR_LITERAL){
        VarLiteralNode* varLiteralNode = (VarLiteralNode*)node;
        return charsFormat("VarLiteralNode(name: %s)", varLiteralNode->name);
    }
    else
        return "Unknown";
}

#endif //UNTITLED5_AST_H
