
#ifndef UNTITLED5_PARSER_H
#define UNTITLED5_PARSER_H

#include <stdlib.h>
#include <lexer/lexer.h>

typedef struct {
    Lexer* lexer;
} Parser;

Parser* parserCreate(Lexer* lexer) {
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->lexer = lexer;
    return parser;
}

#endif // UNTITLED5_PARSER_H