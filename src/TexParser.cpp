
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>
#include <boost/config.hpp>


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
// test...............

    boost::regex pattern ("b.lug",boost::regex_constants::icase|boost::regex_constants::perl);
    std::string stringa ("Searching for bolug");
    std::string replace ("BgLug");
    std::string newString;

    newString = boost::regex_replace (stringa, pattern, replace);

    printf("The new string is: |%s|\n",newString.c_str());

 // test end...............
 
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