
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>

using namespace std;

#include "TexParser.h"
#include "TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"


// B =========================================================================

void TexParser::cutOutBeginEnd
(
    TexDocElement& parentElement, 
    string keyWord,
    const int& typ
)
{
    string beginKeyWord = "\\begin{" + keyWord + "}";
    string endKeyWord = "\\end{" + keyWord + "}";
DBINF << "Suche nach: " <<  keyWord << "\n";
DBINF << "beginKeyWord: " + beginKeyWord + "\n";
DBINF << "endKeyWord: " + endKeyWord + "\n";
    string rawPreSubString = "";
    string texSubstring = "";
    string rawPostSubString = "";
    
    
    string texElementValue = parentElement.getTexElementValue();
// DBINF << "In: " <<  texElementValue << "\n";
    size_t      searchBegin     = 0;
    size_t      found_end       = string::npos;
    size_t      found_begin     = string::npos;

    while ( true)
    {
        found_begin = texElementValue.find
        (
            beginKeyWord,
            searchBegin
        );
        found_end = texElementValue.find
        (
            endKeyWord,
            found_begin
        );
        if (found_begin!=string::npos || found_end!=string::npos)
        {
DBINF << "....Fündig geworden!\n"  ;          
            // text before found the right element.
            rawPreSubString = texElementValue.substr
            (
                searchBegin,
                found_begin
            );
            TexDocElement preElement;
            preElement.setTexElementTyp( TexDocElement::RAW );
// DBINF << "rawPreSubString: " << rawPreSubString  << endl;
            preElement.setTexElementValue( rawPreSubString );
            parentElement.texDocElementsList.push_back(preElement);
            
            // the founded element
            searchBegin = found_end;
            found_begin += beginKeyWord.length();
// DBINF << "found_begin: " <<  found_begin << endl;
// DBINF << "(found_end - found_begin): " <<  (found_end - found_begin) << endl ;
            texSubstring = texElementValue.substr
            (
                found_begin,
                (found_end - found_begin)
            );
            TexDocElement subElement;
            subElement.setTexElementTyp( typ );
DBINF << "texSubstring: " << texSubstring  << endl;
            subElement.setTexElementValue( texSubstring );
            parentElement.texDocElementsList.push_back(subElement);            
            
        }else
        {
            if( searchBegin < (texElementValue.size() - 1) )
            {
                // text after the last found right element.
                rawPostSubString = texElementValue.substr
                (
                    searchBegin,
                    (texElementValue.size() - 1)
                );
                TexDocElement postElement;
                postElement.setTexElementTyp( TexDocElement::RAW );
//DBINF << "texPostSubstring: " << rawPostSubString  << endl;
                postElement.setTexElementValue( rawPostSubString );
                parentElement.texDocElementsList.push_back(postElement);
            }
            break;
        }
    } // end while-loop
}

void TexParser::cutOutShortElements
(
    TexDocElement& parentElement,
    string keyWord,
    const int& typ
)
{
    string beginKeyWord = "\\" + keyWord + "{";
    string endKeyWord = "}";
DBINF << "Suche nach: " <<  keyWord << "\n";
DBINF << "Anfang: " << beginKeyWord << "\n";
DBINF << "Ende: " << endKeyWord << "\n";
    string rawPreSubString = "";
    string texSubstring = "";
    string rawPostSubString = "";
    
    string texElementValue = parentElement.getTexElementValue();
// DBINF << "In: " <<  texElementValue << "\n";
    size_t      searchBegin     = 0;
    size_t      found_end       = string::npos;
    size_t      found_begin     = string::npos;

    while ( true)
    {
        found_begin = texElementValue.find
        (
            beginKeyWord,
            searchBegin
        );
        found_end = texElementValue.find
        (
            endKeyWord,
            found_begin
        );
        if (found_begin!=string::npos || found_end!=string::npos)
        {
DBINF << "....Fündig geworden!\n"  ;          
            // text before found the right element.
            rawPreSubString = texElementValue.substr
            (
                searchBegin,
                found_begin
            );
            TexDocElement preElement;
            preElement.setTexElementTyp( TexDocElement::RAW );
//DBINF << "rawPreSubString: " << rawPreSubString  << endl;
            preElement.setTexElementValue( rawPreSubString );
            parentElement.texDocElementsList.push_back(preElement);
            
            // the founded element
            searchBegin = found_end;
            found_begin += beginKeyWord.length();
DBINF << "found_begin: " <<  found_begin << endl;
DBINF << "(found_end - found_begin): " <<  (found_end - found_begin) << endl ;
            texSubstring = texElementValue.substr
            (
                found_begin,
                (found_end - found_begin)
            );
            TexDocElement subElement;
            subElement.setTexElementTyp( typ );
DBINF << "texSubstring: " << texSubstring  << endl;
            subElement.setTexElementValue( texSubstring );
            parentElement.texDocElementsList.push_back(subElement);            
            
        }else
        {
            if( searchBegin < (texElementValue.size() - 1) )
            {
                // text after the last found right element.
                rawPostSubString = texElementValue.substr
                (
                    searchBegin,
                    (texElementValue.size() - 1)
                );
                TexDocElement postElement;
                postElement.setTexElementTyp( TexDocElement::RAW );
//DBINF << "texPostSubstring: " << rawPostSubString  << endl;
                postElement.setTexElementValue( rawPostSubString );
                parentElement.texDocElementsList.push_back(postElement);
            }
            break;
        }
    } // end while-loop    
    
}

// F =========================================================================


string TexParser::findAndRemoveComments(const string &read_line)
{
    return TexParser::findAndRemoveCommentsSTD(read_line);
}

string TexParser::findAndRemoveCommentsBoost(const string &read_line)
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
    string replace ("");
    return boost::regex_replace (read_line, pattern, replace);
}    


string TexParser::findAndRemoveCommentsSTD(const string &read_line)
{
    string line = read_line;
//DBINF << "line: " << line << endl;
    if( line.size() == 0 )
    {
        return "";
    }
    size_t found_index = line.find("%");
    if(found_index == string::npos)
    {
        // no '%' found. Get back all.
//DBINF << "Kein % gefunden! in: \n " << line  << endl;
        return line;
    }    
//DBINF << "found_index: " << found_index << endl;
//DBINF << "line.size(): " << line.size() << endl;
    if( found_index == 0)
    {
        // is on the begin of the line.
//DBINF << "% am Anfang gefunden." << endl;
        return "";        
    }
    if( line.at(found_index -1) != '\\')
    {
//DBINF << "line.at(found_index -1): " << line.at(found_index -1) << endl;
//DBINF << "Unmaskiertes % gefunden!" <<  endl;
        return line.substr( 0, found_index );
    }    

    do
    {
//DBINF << "Maskiertes % gefunden!" <<  endl;
        found_index = line.find("%", (found_index + 1));
//DBINF << "found_index: " << found_index << endl;
        if(found_index != string::npos)
        {
            if( line[(found_index -1)] != '\\')
            {
//DBINF << "Unmaskiertes % gefunden!" <<  endl;
                line = line.substr( 0, found_index );
                break;
            } 
        } else 
        {
//DBINF << "Kein weiteren % gefunden!" <<  endl;
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
    TexParser::parsInput();
    return;
}

void TexParser::parsDocument(void)
{
    string text_document = "";
    string document_metadata = "";
    
    size_t found_begin = TexParser::completeDoc.find("\\begin{document}");
    size_t found_end = TexParser::completeDoc.find("\\end{document}");
    if (found_begin!=string::npos || found_end!=string::npos)
    {
        // cut metadata.
        document_metadata = TexParser::completeDoc.substr
        (
            0,
            found_begin
        );
        // cut netto document.
        found_begin += string("\\begin{document}").length();
        text_document = TexParser::completeDoc.substr
        (
            found_begin,
            (found_end - found_begin)
        );
    }else
    {
        cerr << "[201111062044] No begin or end of document found." << endl;
        throw;
    }
    TexDocElement metaElement;
    metaElement.setTexElementTyp( TexDocElement::METADATA );
    metaElement.setTexElementValue( document_metadata );
//DBINF << "document_metadata: " << document_metadata << endl;
    TexParser::rootElement.texDocElementsList.push_back(metaElement);
    
    TexDocElement docElement;
    docElement.setTexElementTyp( TexDocElement::DOCUMENT );
    docElement.setTexElementValue( text_document );
    TexParser::rootElement.texDocElementsList.push_back(docElement);
}

void TexParser::parsInput(void)
{
    for
    (
        list<TexDocElement>::iterator i = TexParser::rootElement.texDocElementsList.begin();
        i != TexParser::rootElement.texDocElementsList.end();
        i++)
    {
        int typ = i->getTexElementTyp();
        if(typ == TexDocElement::DOCUMENT)
        {
DBINF << "TexParser::DOCUMENT gefunden!\n";
            TexParser::cutOutBeginEnd
            (
                *i, 
                string("verbatim"),
                TexDocElement::VERBATIM
            ); 
            TexDocElement& childElement = *i;
            for
            (
                list<TexDocElement>::iterator i2 = childElement.texDocElementsList.begin();
                i2 != childElement.texDocElementsList.end();
                i2++)
            {            
                TexParser::cutOutShortElements
                (
                    *i2, 
                    string("input"),
                    TexDocElement::INPUT
                ); 
            }
            
        } // end if(typ == TexDocElement::DOCUMENT)
    } // end for 
    
}

// R ==========================================================================


void TexParser::readImputFile()
{
    // open fiele to read....
    ifstream tex_file(inputFileName.c_str());
    if (tex_file.is_open())
    {
        while ( tex_file.good() )
        {
            string line;
            getline (tex_file,line);
//             cout << "return: " << TexParser::findAndRemoveComments(line) << endl;;
            TexParser::completeDoc.append( TexParser::findAndRemoveComments(line) );
            TexParser::completeDoc.append("\n");
        }
    }else{
        cerr << "[201111062048] couldn't open \"" << inputFileName \
            << "\" for reading\n" << endl;
        throw;
    }
    tex_file.close();
}


// S ==========================================================================


void TexParser::setInputFileName(string fileName)
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