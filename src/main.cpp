// Doku to yyFlexLexer Lexer
// http://laurel.datsi.fi.upm.es/~rpons/gjsc/doxygen/classyyFlexLexer.html
// http://dinosaur.compilertools.net/flex/flex_19.html

#include <iostream>
#include <fstream>
#include <string>

#undef yyFlexLexer
#define yyFlexLexer newcomFlexLexer
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
    std::string filename_tmp;
    filename_tmp = "";
    
    if(argc!=3)
    {
        std::cout << "Please specify the input file & output file\n" << std::endl;
        return 0;
    }
    filename_in = argv[1];
    filename_out = argv[2];
    filename_tmp = filename_out + std::string(".tmp");


    // open fiele to read....
    std::ifstream read_file(filename_in.c_str());
    if (read_file.is_open())
    {
//         while ( read_file.good() )
//         {
//             std::string line;
//             getline (read_file,line);
//             std::cout << line << std::endl;
//         }
    }else{
        std::cout << "couldn't open temp for writting\n" << std::endl;
        return 0;
    }

    // open fiele to write....
    std::ofstream write_file_tmp (filename_tmp.c_str());
    if (write_file_tmp.is_open())
    {
//         write_file_tmp << "This is a line.\n";
//         write_file_tmp << "This is another line.\n";
    }else{
        std::cout << "Unable to open file" << std::endl;
        return 0;
    }

    
    newcomFlexLexer comLexer; //( &read_file,  &write_file_tmp);
    comLexer.switch_streams( &read_file,  &write_file_tmp);
    comLexer.yylex();
    read_file.close();
    write_file_tmp.close();

    // Main processing.

    // open file to read...
    std::ifstream read_file_tmp(filename_tmp.c_str());
    if (read_file_tmp.is_open())
    {
//         while ( read_file_tmp.good() )
//         {
//             std::string line;
//             getline (read_file_tmp,line);
//             std::cout << line << std::endl;
//         }
    }else{
        std::cout << "couldn't open temp for writting\n" << std::endl;
        return 0;
    }

    // file open for writeing
    std::ofstream write_file (filename_out.c_str());
    if (write_file.is_open())
    {
//         write_file << "This is a line.\n";
//         write_file << "This is another line.\n";
    }else{
        std::cout << "Unable to open file" << std::endl;
        return 0;
    }

//     FlexLexer htmlLexer( &read_file_tmp,  &write_file);
    htmlFlexLexer htmlLexer( &read_file_tmp,  &write_file);
    htmlLexer.yylex();
    read_file_tmp.close();
    write_file.close();


    std::cout << "tmp-fiel-name: " << filename_tmp << std::endl;
    std::cout << "filename_out: " << filename_out << std::endl;
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