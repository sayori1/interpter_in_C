#include "core/array.h"
#include "core/map.h"
#include "lexer/lexer.h"
#include "parser/parser_utils.h"

void main()
{
    Lexer *lexer = lexerCreate("{var a = 10; var b = 20; var c = a + b;}");
    Node *node = parseCompoundStatement(parserCreate(lexer));
    printf("%s", nodeToString(node));
}