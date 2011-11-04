// Doku to yyFlexLexer Lexer
// http://laurel.datsi.fi.upm.es/~rpons/gjsc/doxygen/classyyFlexLexer.html
// http://dinosaur.compilertools.net/flex/flex_19.html

// TODO: create subfunctions for open and close file.


#include <string>
#include <iostream>
#include "TexToHtml.h"

void get_help(void)
{
    std::cout << "\n--help" << std::endl;
    std::cout << "\t\t Help text." << std::endl;
    std::cout << "\n--imput=[file name]" << std::endl;
    std::cout << "\t\t Name of imput file." << std::endl;
    std::cout << "\n--output=[file name]" << std::endl;
    std::cout << "\t\t Name of output file." << std::endl;


}

int main(int argc,char *argv[])
{
    std::string str_arg;
    size_t found;
    std::string imputFileName;
    imputFileName="";
    std::string outputFileName;
    outputFileName="";
  
//     if(argc > 3)
//     {
//         std::cout << "error: too much arguments" << std::endl;
//         std::cout << "Please specify the input file & output file\n" << std::endl;
//         return 1;
//     };
//     
//     if(argc < 1)
//     {
//         std::cout << "error: too few arguments" << std::endl;
//         std::cout << "Please specify the input file & output file\n" << std::endl;
//         return 1;
//     };
//     
//     TexToHtml texToHtml;
//     texToHtml.setInputFileName(std::string(argv[1]));
//     texToHtml.setOutputFileName(std::string(argv[2]));
//     texToHtml.start();

    for ( int i = 1; i < argc; i++)
    {
        str_arg = std::string(argv[i]);
        found = str_arg.find("--help");
        if (found!=std::string::npos)
        {
            get_help();
        }
        found = str_arg.find("--imput=");
        if (found!=std::string::npos)
        {
            size_t endIdentifier = std::string("--imput=").length();
            imputFileName = str_arg.substr( endIdentifier );
        }
        found = str_arg.find("--output=");
        if (found!=std::string::npos)
        {
            size_t endIdentifier = std::string("--output=").length();
            outputFileName = str_arg.substr( endIdentifier );
        }        


    }

    if( imputFileName == "" )
    {
        std::cout << "Name of imput file is not set!" << std::endl;
        return 1;
    }
    if( outputFileName == "" )
    {
        std::cout << "Name of output file is not set!" << std::endl;
        return 1;
    }
    std::cout << "convert " << imputFileName << " to " << outputFileName << std::endl;
    
    return 0;
}




