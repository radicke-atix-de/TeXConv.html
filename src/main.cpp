// Doku to yyFlexLexer Lexer
// http://laurel.datsi.fi.upm.es/~rpons/gjsc/doxygen/classyyFlexLexer.html
// http://dinosaur.compilertools.net/flex/flex_19.html

#include <iostream>
#include <fstream>
#include <string>

#undef yyFlexLexer
#define yyFlexLexer xxFlexLexer
#include <FlexLexer.h>

#undef yyFlexLexer
#define yyFlexLexer htmlFlexLexer
#include <FlexLexer.h>




main(int argc,char *argv[])
{
    std::string filename_in;
    filename_in = "";
    std::string filename_out;
    filename_out = "";
    if(argc!=3)
    {
        std::cout << "Please specify the input file & output file\n" << std::endl;
        return 0;
    }
    filename_in = argv[1];
    filename_out = argv[2];
    
    std::ifstream read_file(filename_in.c_str());
    if (read_file.is_open())
    {
        while ( read_file.good() )
        {
            std::string line;
            getline (read_file,line);
            std::cout << line << std::endl;
        }
        read_file.close();
    }else{
        std::cout << "couldn't open temp for writting\n" << std::endl;
        return 0;
    }


    std::ofstream write_file (filename_out.c_str());
    if (write_file.is_open())
    {
        write_file << "This is a line.\n";
        write_file << "This is another line.\n";
        write_file.close();
    }else{
        std::cout << "Unable to open file" << std::endl;
        return 0;
    }

    
//     yyin=fp;
//     yyparse();

//     std::ofstream *p_write_file = &write_file;
    htmlFlexLexer Lexer( &read_file,  &write_file);
//     Lexer.switch_streams( read_file, write_file);
    Lexer.yylex();

    return 0;
}


// int main()
// {
//     yyFlexLexer Lexer;
//     Lexer.yylex();
// 
//     std::cout << "Bilanz (: " << open_round_brackets << std::endl;
//     std::cout << "Bilanz [: " << open_square_brackets << std::endl;
//     std::cout << "Bilanz {: " << open_curly_brackets << std::endl;
// }