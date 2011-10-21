
%option noyywrap
%option c++
%{
#include <iostream>
  /* "("  */
int open_round_brackets = 0;
  /* "["  */
int open_square_brackets = 0;
  /* "{"  */
int open_curly_brackets = 0;
%}

WORD    [a-zA-Z][a-zA-Z0-9_]*

%%
{WORD}          { }
  /* {WORD}          { std::cout << "Das Wort: " << yytext  << std::endl;} */
"\n"            {}
"("             {open_round_brackets++; std::cout << "Klammer auf" << std::endl;}
")"             {open_round_brackets--;
                  std::cout << "Klammer zu. Rest:" << open_round_brackets << std::endl;}
"["             {open_square_brackets++; std::cout << "Klammer auf" << std::endl;}
"]"             {open_square_brackets--;std::cout << "Klammer zu" << std::endl;}
"{"             {open_curly_brackets++; std::cout << "Klammer auf" << std::endl;}
"}"             {open_curly_brackets--;
                  std::cout << "Klammer zu. Rest: " << open_curly_brackets << std::endl;}
%%


int main()
{
    yyFlexLexer Lexer;
    Lexer.yylex();

    std::cout << "Bilanz (: " << open_round_brackets << std::endl;
    std::cout << "Bilanz [: " << open_square_brackets << std::endl;
    std::cout << "Bilanz {: " << open_curly_brackets << std::endl;
}
