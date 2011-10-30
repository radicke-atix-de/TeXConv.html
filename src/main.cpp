// Doku to yyFlexLexer Lexer
// http://laurel.datsi.fi.upm.es/~rpons/gjsc/doxygen/classyyFlexLexer.html
// http://dinosaur.compilertools.net/flex/flex_19.html

// TODO: create subfunctions for open and close file.

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
    filename_tmp = "texconv_tex.tmp";
    
    if(argc!=3)
    {
        std::cout << "Please specify the input file & output file\n" << std::endl;
        return 0;
    }
    filename_in = argv[1];
    filename_out = argv[2];

    
    // open fiele to write....
    std::ofstream tmp_file (filename_tmp.c_str());
    if (tmp_file.is_open())
    {
//         tmp_file << "This is a line.\n";
//         tmp_file << "This is another line.\n";
    }else{
        std::cout << "Unable to open file" << std::endl;
        return 0;
    }    

    // open fiele to read....
    std::ifstream tex_file(filename_in.c_str());
    if (tex_file.is_open())
    {
        while ( tex_file.good() )
        {
            std::string line;
            getline (tex_file,line);
            tmp_filet << line << std::endl;
        }
    }else{
        std::cout << "couldn't open temp for writting\n" << std::endl;
        return 0;
    }



    // open fiele to write....
    std::ofstream err_file ("error.log");
    if (err_file.is_open())
    {
//         tmp_file << "This is a line.\n";
//         tmp_file << "This is another line.\n";
    }else{
        std::cout << "Unable to open file" << std::endl;
        return 0;
    }  
  
  
    newcomFlexLexer comLexer; //( &tex_file,  &tmp_file);
    comLexer.switch_streams( &tex_file,  &err_file);
    comLexer.yylex();
//     tex_file.close();
    tmp_file.close();

    // Main processing.

    // open file to read...
    std::ifstream tex_file_tmp(filename_tmp.c_str());
    if (tex_file_tmp.is_open())
    {
//         while ( tex_file_tmp.good() )
//         {
//             std::string line;
//             getline (tex_file_tmp,line);
//             std::cout << line << std::endl;
//         }
    }else{
        std::cout << "couldn't open temp for writting\n" << std::endl;
        return 0;
    }



//     FlexLexer htmlLexer( &tex_file_tmp,  &html_file);
//     htmlFlexLexer htmlLexer( &tex_file_tmp,  &err_file);
    htmlFlexLexer htmlLexer( &tex_file_tmp,  &err_file);
    htmlLexer.yylex();
    
    // file open for writeing
    std::ofstream html_file (filename_out.c_str());
    if (html_file.is_open())
    {
//         html_file << "This is a line.\n";
//         html_file << "This is another line.\n";
    }else{
        std::cout << "Unable to open file" << std::endl;
        return 0;
    }    
    
    tex_file_tmp.close();
    html_file.close();


    std::cout << "tmp-fiel-name: " << filename_tmp << std::endl;
    std::cout << "filename_out: " << filename_out << std::endl;
//    std::cout << htmlLexer.html_open_round_brackets << std::endl;
    return 0;
}


