//
// Created by admin on 6/7/2024.
//

#ifndef UNTITLED5_INTERPRETER_H
#define UNTITLED5_INTERPRETER_H

#include "parser/node.h"
#include <core/map.h>


typedef struct{
    Map* variables;
} Interpreter;


Interpreter* interpreterCreate(){
    Interpreter* interpreter = (Interpreter*)malloc(sizeof(Interpreter));
    interpreter->variables = mapCreate(10);
    return interpreter;
}



void addVariable(Interpreter* self, char* name, int value){
    mapSet(self->variables, name, (void*)value);
}

int visit(Interpreter* self, Node* node);

int visitLiteral(Interpreter* self, NumNode* node){
    if(node->base.type == NUMBER){
        return (node)->value;
    }
    else if(node->base.type == VAR_LITERAL){
        return visitVariable(self, (VarLiteralNode*)node);
    }
}

int visitExpression(Interpreter* self, Node* node){
    if(node->type == BINOP){
        BinOpNode* binOpNode = (BinOpNode*) node;
        char ch = (char)binOpNode->op->value;

        if(ch == '+'){
            return visitExpression(self, binOpNode->left) + visitExpression(self, binOpNode->right);
        }
        else if(ch == '-'){
            return visitExpression(self, binOpNode->left) - visitExpression(self, binOpNode->right);
        }
        else if(ch == '*'){
            return visitExpression(self, binOpNode->left) * visitExpression(self, binOpNode->right);
        }
        else if(ch == '/'){
            return visitExpression(self, binOpNode->left) / visitExpression(self, binOpNode->right);
        }
    }
    else{
        return visitLiteral(self, (NumNode*)node);
    }

}

void visitAssign( Interpreter* self, AssignNode* node){
    int value = visitExpression(self, node->expr);

    addVariable(self, node->name, value);
}

int visitVariable(Interpreter* self, VarLiteralNode* node){
    return (int)mapGet(self->variables, node->name);
}

int visitStatement(Interpreter* self, StatementNode* node){
    visitAssign(self, (AssignNode*)node->child);
    return 0;
}

void visitCompound(Interpreter* self, CompoundNode* node){
    for(int i = 0; i < node->count; i++){
        visitStatement(self, node->statements[i]);
    }
}

int visit(Interpreter* self, Node* node){
    visitCompound(self, (CompoundNode*)node);
}

#endif //UNTITLED5_INTERPRETER_H
