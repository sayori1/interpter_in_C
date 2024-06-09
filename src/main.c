#include "core/array.h"
#include "core/map.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

void main(){
    Lexer* lexer = lexerCreate("{var a = 10; var b = 20; var c = a + b;}");
    Parser* parser = parserCreate(lexer);
    Node* node = parse(parser);

    printf("%s\n", nodeToString(node));
    
}