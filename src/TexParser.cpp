
#include <iostream>
#include <fstream>
#include <string>
#include <regex.h>
#include <boost/regex.hpp>


#include "TexParser.h"


// P =========================================================================

void TexParser::pars()
{
    TexParser::readImputFile();
//     std::cout << TexParser::completeDoc << std::endl;
    std::cout << TexParser::parsDocument() << std::endl;
    
    return;

}

std::string TexParser::parsDocument(void)
{
    // More detais to boost::regex see: 
    // http://www.boost.org/doc/libs/1_47_0/libs/regex/doc/html/boost_regex/syntax/basic_syntax.html
    // It is in use a case sensitive POSIX-Basic expression. The POSIX-Basic 
    // regular expression syntax is used by the Unix utility sed, and 
    // variations are used by grep and emacs. 
    boost::regex pattern ("[^\\]%*\\n",boost::regex::basic);
    std::string stringa = TexParser::completeDoc;
    std::string replace ("");
    std::string newString;

    newString = boost::regex_replace (stringa, pattern, replace);
   

    std::cerr << "###############################################" << std::endl;
    printf("The new string is: |%s|\n",newString.c_str());
    std::cerr << "###############################################" << std::endl;

    // TODO: lösung. zeile für Zeile nach "%" suchen und ab dar Abschneiden,
    // wenn index minus 1 nicht "\" ist...
 
    size_t found_begin = TexParser::completeDoc.find("\\begin{document}");
    size_t found_end = TexParser::completeDoc.find("\\end{document}");
    if (found_begin!=std::string::npos || found_end!=std::string::npos)
    {
        found_begin += std::string("\\begin{document}").length();
        return TexParser::completeDoc.substr
        (
            found_begin,
            (found_end - found_begin)
        );
    }else
    {
        std::cerr << "No begin or end of document found." << std::endl;
        throw;
    }


    
  
}

// R ==========================================================================


void TexParser::readImputFile()
{
    // open fiele to read....
    std::ifstream tex_file(inputFileName.c_str());
    if (tex_file.is_open())
    {
        while ( tex_file.good() )
        {
            std::string line;
            getline (tex_file,line);
            TexParser::completeDoc.append(line);
            TexParser::completeDoc.append("\n");
        }
    }else{
        std::cerr << "couldn't open " << inputFileName << " for reading\n" << std::endl;
        return;
    }
    tex_file.close();
}

// S ==========================================================================


void TexParser::setInputFileName(std::string fileName)
{
    TexParser::inputFileName = fileName;
}

// T ==========================================================================

TexParser::TexParser()
{
    // pass
}

TexParser::~TexParser()
{
    // pass
}