// Doku to yyFlexLexer Lexer
// http://laurel.datsi.fi.upm.es/~rpons/gjsc/doxygen/classyyFlexLexer.html
// http://dinosaur.compilertools.net/flex/flex_19.html

// TODO: create subfunctions for open and close file.


#include <string>
#include <iostream>
#include "TexToHtml.h"


int main(int argc,char *argv[])
{
    if(argc > 3)
    {
        std::cout << "error: too much arguments" << std::endl;
        std::cout << "Please specify the input file & output file\n" << std::endl;
        return 1;
    };
    
    if(argc < 1)
    {
        std::cout << "error: too few arguments" << std::endl;
        std::cout << "Please specify the input file & output file\n" << std::endl;
        return 1;
    };
    
    TexToHtml texToHtml;
    texToHtml.setInputFileName(std::string(argv[1]));
    texToHtml.setOutputFileName(std::string(argv[2]));
    texToHtml.start();
    return 0;
}


