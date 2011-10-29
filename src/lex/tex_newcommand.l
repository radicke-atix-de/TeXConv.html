%option prefix="newcom"
%option noyywrap
%option c++
%{
#include <iostream>
  /* "("  */
int newcom_open_round_brackets = 0;
  /* "["  */
int newcom_open_square_brackets = 0;
  /* "{"  */
int newcom_open_curly_brackets = 0;
%}

word        [a-zA-Z][a-zA-Z0-9_!.:;,-?=/]*
white       [ \t]+
comment     %.*\n

%%
"("             {
                  newcom_open_round_brackets++;
                  std::cout << "Klammer auf" << std::endl;
                }
")"             {
                  newcom_open_round_brackets--;
                  std::cout << "Klammer zu. Rest:" << newcom_open_round_brackets << std::endl;
                }
"["             {
                  newcom_open_square_brackets++; std::cout << "Klammer auf" << std::endl;
                }
"]"             {
                  newcom_open_square_brackets--;std::cout << "Klammer zu" << std::endl;
                }
"{"             {
                  newcom_open_curly_brackets++; std::cout << "Klammer auf" << std::endl;
                }
"}"             {
                  newcom_open_curly_brackets--;
                  std::cout << "Klammer zu. Rest: " << newcom_open_curly_brackets <<
                  std::endl;
                }


"#[0-9]"        {
                  std::cout << "Platzhalter gefunden: " << yytext << std::endl;
                }

  /* single commands */
{word}          { }
  /* {word}          { std::cout << "Das Wort: " << yytext  << std::endl;} */
{white}     { /* We ignore white characters */ }

{comment}    { std::cout << "comment: " << yytext  << std::endl; }


"\\newcommand"      {}
"\#"      {}
%%


// int main()
// {
//     yyFlexLexer Lexer;
//     Lexer.yylex();
// 
//     std::cout << "Bilanz (: " << open_round_brackets << std::endl;
//     std::cout << "Bilanz [: " << open_square_brackets << std::endl;
//     std::cout << "Bilanz {: " << open_curly_brackets << std::endl;
// }
