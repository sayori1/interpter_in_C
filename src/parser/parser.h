

#ifndef UNTITLED5_PARSER_H
#define UNTITLED5_PARSER_H

#include "parser/node.h"
#include "lexer/lexer.h"

typedef struct{
    Lexer* lexer;
} Parser;

Node* parsePlusMinus(Parser* self);

Parser* parserCreate(Lexer* lexer){
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->lexer = lexer;
    return parser;
}

Node* parseLiteral(Parser* self){
    Lexem* lexem = self->lexer->currentLexem;

    if(lexem->type == NUM){
        eatToken(self->lexer, NUM);
        return (Node*)numNodeCreate((int)lexem->value);
    }
    else if(lexem->type == PARB){
        eatToken(self->lexer, PARB);
        Node* expr = parsePlusMinus(self);
        eatToken(self->lexer, PARE);
        return expr;
    }
    else if(lexem->type == ID){
        eatToken(self->lexer, ID);

        return (Node*)varLiteralNodeCreate((char*)lexem->value);
    } 
}

Node* parseMulDiv(Parser* self){
    Node* left = parseLiteral(self);

    Lexem* lexem = self->lexer->currentLexem;
    char ch = (char)lexem->value;

    if(lexem->type == OPERATOR && (ch == '*' || ch == '/')){
        eatToken(self->lexer, OPERATOR);

        NumNode* right = (NumNode*)parseMulDiv(self);

        if(ch == '*'){
            return (Node*)binOpNodeCreate(left, (Node*)right, lexem);
        }
        else if(ch == '/'){
            return (Node*)binOpNodeCreate(left, (Node*)right, lexem);
        }
    }

    return left;
}

Node* parsePlusMinus(Parser* self){
    Node* left = parseMulDiv(self);

    Lexem* lexem = self->lexer->currentLexem;
    char ch = (char)lexem->value;

    if(lexem->type == OPERATOR && (ch == '+' || ch == '-')){
        eatToken(self->lexer, OPERATOR);
        Node* right = parsePlusMinus(self);

        if(ch == '+'){
            return (Node*)binOpNodeCreate(left, right, lexem);
        }
        else if(ch == '-'){
            return (Node*)binOpNodeCreate(left, right, lexem);
        }
    }

    return left;
}

Node* parseAssign(Parser* self){
    eatToken(self->lexer, VAR);
    Lexem* varName = eatToken(self->lexer, ID);
    eatToken(self->lexer, OPERATOR);
    Node* expr = parsePlusMinus(self);

    return (Node*) assignNodeCreate((char*)varName->value, expr);
}


Node* parseStatement(Parser* self){
    Node* node;
    if(self->lexer->currentLexem->type == VAR){
         node = parseAssign(self);
    }
    eatToken(self->lexer, STATEMEND_END);

    Node* statementNode = (Node*)statementNodeCreate(node);

    return statementNode;
}


Node* parseCompoundStatement(Parser* self){
    eatToken(self->lexer, COMB);

    CompoundNode* compoundNode = compoundNodeCreate();

    while(self->lexer->currentLexem->type != COME){
        StatementNode* statement = (StatementNode*)parseStatement(self);
        compoundNodeAddStatement(compoundNode, statement);
    }

    return (Node*)compoundNode;
}


Node* parse(Parser* self){
    return parseCompoundStatement(self);
}

#endif
