
%option noyywrap
%option c++
%{
#include <stdio.h>
#include <iostream>
int num_lines = 0;
int num_chares = 0;
%}

%%
"\n"    {num_lines++; num_chares++;}
.       {num_chares++;}
%%
int main()
{
    yyFlexLexer Lexer;
    Lexer.yylex();

    std::cout << num_lines << " Zeilen" << std::endl;
}
