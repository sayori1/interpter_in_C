#ifndef UNTITLED5_PARSER_H
#define UNTITLED5_PARSER_H

#include <stdlib.h>
#include "parser/nodes/node.h"
#include "lexer/lexer.h"
#include "nodes/num_node.h"
#include "nodes/binop_node.h"
#include "nodes/compound_statement_node.h"
#include "nodes/symbol_node.h"

typedef struct {
    Lexer* lexer;
} Parser;

Node* parsePlusMinus(Parser* self);
Parser* parserCreate(Lexer* lexer);
Node* parseLiteral(Parser* self);
Node* parseMulDiv(Parser* self);
Node* parseStatement(Parser* self);
Node* parseCompoundStatement(Parser* self);
Node* parse(Parser* self);
char* nodeToString(Node* node);
Node* parseAssign(Parser* self);

#endif // UNTITLED5_PARSER_H
