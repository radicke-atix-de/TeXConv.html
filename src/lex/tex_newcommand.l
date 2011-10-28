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


"\begin{description}"
"\end{description}"
"\begin{document}"
"\end{document}"
"\begin{itemize}"
"\end{itemize}"
"\begin{lstlisting}"
"\end{lstlisting}"
"\begin{tabular}"
"\end{tabular}"
"%"

  /* single commands */
{word}          { }
  /* {word}          { std::cout << "Das Wort: " << yytext  << std::endl;} */
{white}     { /* We ignore white characters */ }

{comment}    { std::cout << "comment: " << yytext  << std::endl; }


"\\hline"           {}
"\\index"           {}
"\\item"            {}
"\\label"           {}
"\maketitle"        {}
"\n"                {}
"\\newpage"     {
                  std::cout << "---- Neue Seite!! ----" << std::endl;
                }
"\\pageref"         {}
"\\ref"             {}
"\\subsubsection"   {}
"\\subsection"      {}
"\\section"         {}
"\\subsection"      {}
"\\tableofcontents" {}
"&"                 {}
"\\\\"              {}
"--"                {}
"\\-"               {}
"\\&"               {}
"|"                 {}
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
