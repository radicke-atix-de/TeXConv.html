%option prefix="html"
%option noyywrap
%option c++
%{
#include <iostream>
#include <fstream>



std::ofstream html_file ("texconv_html.tmp");
  /* file open for writeing 
if (html_file.is_open())
{
//         html_file << "This is a line.\n";
//         html_file << "This is another line.\n";
}else{
    std::cout << "Unable to open file" << std::endl;
    return 0;
}*/

  /* "("  */
int html_open_round_brackets = 0;
  /* "["  */
int html_open_square_brackets = 0;
  /* "{"  */
int html_open_curly_brackets = 0;
%}

word        [a-zA-Z][a-zA-Z0-9_!.:;,-?=/]*
  /* white       [ \t]+ */
white       [:blank:]*
comment     %.*\n

%%
"("             {
                  html_open_round_brackets++;
                  std::cout << "Klammer auf" << std::endl;
                }
")"             {
                  html_open_round_brackets--;
                  std::cout << "Klammer zu. Rest:" << html_open_round_brackets << std::endl;
                }
"["             {
                  html_open_square_brackets++; std::cout << "Klammer auf" << std::endl;
                }
"]"             {
                  html_open_square_brackets--;std::cout << "Klammer zu" << std::endl;
                }
"{"             {
                  html_open_curly_brackets++; std::cout << "Klammer auf" << std::endl;
                }
"}"             {
                  html_open_curly_brackets--;
                  std::cout << "Klammer zu. Rest: " << html_open_curly_brackets << std::endl;
                }


"\begin{description}"   {}
"\end{description}"     {}
"\begin{document}"      {}
"\end{document}"        {}
"\begin{itemize}"       {}
"\end{itemize}"         {}
"\begin{lstlisting}"    {}
"\end{lstlisting}"      {}
"\begin{tabular}"       {}
"\end{tabular}"         {}
"\%"                    {}

  /* single commands */
{word}      { html_file <<  YYText(); }
  /* {word}          { std::cout << "Das Wort: " << yytext  << std::endl;} */
{white}     { html_file << " "; }

{comment}   { std::cout << "comment: " << yytext  << std::endl; }


"\\hline"           { std::cout << "comment: " << yytext  << std::endl; }
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
