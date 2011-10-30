#include "TexToHtml.h"

#include <iostream>
#include <fstream>
#include <string>

#undef yyFlexLexer
#define yyFlexLexer newcomFlexLexer
#include <FlexLexer.h>

#undef yyFlexLexer
#define yyFlexLexer htmlFlexLexer
#include <FlexLexer.h>


// H ==========================================================================

void TexToHtml::htmlLexer(void)
{
    // Main processing.

    // open file to read...
    std::ifstream tex_file_tmp(tmpFileName.c_str());
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
        return;
    }



//     FlexLexer htmlLexer( &tex_file_tmp,  &html_file);
//     htmlFlexLexer htmlLexer( &tex_file_tmp,  &errFStrem);
    htmlFlexLexer htmlLexer( &tex_file_tmp);
    htmlLexer.yylex();
    
    
    
    
    
    
    // file open for writeing
    std::ofstream html_file (outputFileName.c_str());
    if (html_file.is_open())
    {
//         html_file << "This is a line.\n";
//         html_file << "This is another line.\n";
    }else{
        std::cout << "Unable to open file" << std::endl;
        return;
    }    
    
    
    // open file to read...
    std::ifstream html_file_tmp(tmpFileName.c_str());
    if (html_file_tmp.is_open())
    {
        while ( html_file_tmp.good() )
        {
            std::string line;
            getline (html_file_tmp,line);
            html_file << line << std::endl;
        }
    }else{
        std::cout << "couldn't open temp for writting\n" << std::endl;
        return;
    }
    
    tex_file_tmp.close();
    html_file.close();

};




// F ==========================================================================

void TexToHtml::newcommandLexer(void)
{
    // open fiele to write....
    std::ofstream tmp_file (tmpFileName.c_str());
    if (tmp_file.is_open())
    {
//         tmp_file << "This is a line.\n";
//         tmp_file << "This is another line.\n";
    }else{
        std::cout << "Unable to open file" << std::endl;
        return;
    }    

    // open fiele to read....
    std::ifstream tex_file(inputFileName.c_str());
    if (tex_file.is_open())
    {
        while ( tex_file.good() )
        {
            std::string line;
            getline (tex_file,line);
            tmp_file << line << std::endl;
        }
    }else{
        std::cout << "couldn't open temp for writting\n" << std::endl;
        return;
    }



 
  
  
    newcomFlexLexer comLexer; //( &tex_file,  &tmp_file);
    comLexer.switch_streams( &tex_file);
    comLexer.yylex();
    tmp_file.close();
   
};

// S ==========================================================================

void TexToHtml::setInputFileName(std::string input)
{
    TexToHtml::inputFileName = input;
};


void TexToHtml::setOutputFileName(std::string output)
{
    TexToHtml::outputFileName = output;
};



void TexToHtml::start(void)
{

    TexToHtml::newcommandLexer();
    TexToHtml::htmlLexer();


    std::cout << "tmp-fiel-name: " << tmpFileName << std::endl;
    std::cout << "filename_out: " << outputFileName << std::endl;
//    std::cout << htmlLexer.html_open_round_brackets << std::endl;
    return;  
  
};

// T ==========================================================================

TexToHtml::TexToHtml(void):
        tmpFileName("texconv.tmp"),
        tmpHtmlFileName("texconv.html.tmp")
{

};

TexToHtml::~TexToHtml(void)
{

};