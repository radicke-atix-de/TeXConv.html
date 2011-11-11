
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>


#include "TexParser.h"
#include "TexDocElement.h"

// B =========================================================================

void TexParser::cutOfBeginEnd(TexDocElement &element, std::string keyWord)
{
    std::string texSubstring;
    std::string texElementValue = element.getTexElementValue();
    size_t searchBegin = texElementValue.begin();
    size_t found_end =  texElementValue.begin();

    while ( true)
    {
        size_t found_begin = texElementValue.find
        (
            ("\\begin{" + keyWord + "}"),
            searchBegin
        );
        size_t found_end = texElementValue.find
        (
            ("\\end{" + keyWord + "}"),
            found_begin
        );
        if (found_begin!=std::string::npos || found_end!=std::string::npos)
        {
            searchBegin = found_end;
            found_begin += std::string("\\begin{" + keyWord + "}").length();
            texSubstring = TexParser::completeDoc.substr
            (
                found_begin,
                (found_end - found_begin)
            );
        }else
        {
            break;
        }
        TexDocElement metaElement;
        // TODU
        metaElement.setTexElementTyp( TexDocElement::METADATA );
        metaElement.setTexElementValue( texSubstring );
        std::cout << "document_metadata: " << document_metadata << std::endl;
        element.push_back(metaElement);

    }


}

// F =========================================================================


std::string TexParser::findAndRemoveComments(const std::string &read_line)
{
    return TexParser::findAndRemoveCommentsSTD(read_line);
}

std::string TexParser::findAndRemoveCommentsBoost(const std::string &read_line)
{
    // More detais to boost::regex see: 
    // http://www.boost.org/doc/libs/1_47_0/libs/regex/doc/html/boost_regex/syntax/basic_syntax.html
    // It is in use a case sensitive POSIX-Basic expression. The POSIX-Basic 
    // regular expression syntax is used by the Unix utility sed, and 
    // variations are used by grep and emacs. 

    boost::regex pattern
    (
        "(^\\(.*\\)[^\\\\]*%.*$)|(/^\\(.*\\)[^\\\\]*%.*$)",
        boost::regex::basic
    );
    std::string replace ("");
    return boost::regex_replace (read_line, pattern, replace);
}    


std::string TexParser::findAndRemoveCommentsSTD(const std::string &read_line)
{
    std::string line = read_line;
//     std::cout << "line: " << line << std::endl;
    if( line.size() == 0 )
    {
        return "";
    }
    size_t found_index = line.find("%");
    if(found_index == std::string::npos)
    {
        // no '%' found. Get back all.
//         std::cout << "Kein % gefunden! in: \n " << line  << std::endl;
        return line;
    }    
//     std::cout << "found_index: " << found_index << std::endl;
//     std::cout << "line.size(): " << line.size() << std::endl;
    if( found_index == 0)
    {
        // is on the begin of the line.
//         std::cout << "% am Anfang gefunden." << std::endl;
        return "";        
    }
    if( line.at(found_index -1) != '\\')
    {
//         std::cout << "line.at(found_index -1): " << line.at(found_index -1) << std::endl;
//         std::cout << "Unmaskiertes % gefunden!" <<  std::endl;
        return line.substr( 0, found_index );
    }    

    do
    {
//         std::cout << "Maskiertes % gefunden!" <<  std::endl;
        found_index = line.find("%", (found_index + 1));
//         std::cout << "found_index: " << found_index << std::endl;
        if(found_index != std::string::npos)
        {
            if( line[(found_index -1)] != '\\')
            {
//                 std::cout << "Unmaskiertes % gefunden!" <<  std::endl;
                line = line.substr( 0, found_index );
                break;
            } 
        } else 
        {
//             std::cout << "Kein weiteren % gefunden!" <<  std::endl;
            break;
        }
    }while( true );
    // no more  '%' found. Get back all.
    return line;
}

// P =========================================================================

void TexParser::pars()
{
    TexParser::readImputFile();
    TexParser::parsDocument();
    return;
}

void TexParser::parsDocument(void)
{
    std::string text_document = "";
    std::string document_metadata = "";
    
    size_t found_begin = TexParser::completeDoc.find("\\begin{document}");
    size_t found_end = TexParser::completeDoc.find("\\end{document}");
    if (found_begin!=std::string::npos || found_end!=std::string::npos)
    {
        // cut metadata.
        document_metadata = TexParser::completeDoc.substr
        (
            0,
            found_begin
        );
        // cut netto document.
        found_begin += std::string("\\begin{document}").length();
        text_document = TexParser::completeDoc.substr
        (
            found_begin,
            (found_end - found_begin)
        );

        
    }else
    {
        std::cerr << "[201111062044] No begin or end of document found." << std::endl;
        throw;
    }
    TexDocElement metaElement;
    metaElement.setTexElementTyp( TexDocElement::METADATA );
    metaElement.setTexElementValue( document_metadata );
    std::cout << "document_metadata: " << document_metadata << std::endl;
    TexParser::rootElement.texDocElementsList.push_back(metaElement);
    
    TexDocElement docElement;
    docElement.setTexElementTyp( TexDocElement::DOCUMENT );
    docElement.setTexElementValue( text_document );
    TexParser::rootElement.texDocElementsList.push_back(docElement);
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
//             std::cout << "return: " << TexParser::findAndRemoveComments(line) << std::endl;;
            TexParser::completeDoc.append( TexParser::findAndRemoveComments(line) );
            TexParser::completeDoc.append("\n");
        }
    }else{
        std::cerr << "[201111062048] couldn't open " << inputFileName \
            << " for reading\n" << std::endl;
        throw;
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
    TexParser::rootElement = TexDocElement();
    TexParser::rootElement.setTexElementTyp( TexDocElement::ROOTELEMENT );
}

TexParser::~TexParser()
{
    // pass
}