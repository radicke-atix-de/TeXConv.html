
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>

#include "TexParser.h"
#include "TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;


// B =========================================================================

// C =========================================================================

void TexParser::cutOutBeginEnd(
    TexDocElement& parentElement, 
    string keyWord,
    const enum TexDocElement::ElementType& type
){
    string beginKeyWord = "\\begin{" + keyWord + "}";
    string endKeyWord = "\\end{" + keyWord + "}";
    string rawPreSubString = "";
    string texSubstring = "";
    string rawPostSubString = "";
    
    
    string texElementValue = parentElement.getTexElementValue();
    size_t      searchBegin     = 0;
    size_t      found_end       = string::npos;
    size_t      found_begin     = string::npos;

    while ( true) {
        found_begin = texElementValue.find (
            beginKeyWord,
            searchBegin
        );
        found_end = texElementValue.find (
            endKeyWord,
            found_begin
        );
        if (found_begin!=string::npos || found_end!=string::npos) {
            // text before found the right element.
            rawPreSubString = texElementValue.substr (
                searchBegin,
                found_begin
            );
            TexDocElement preElement;
            preElement.setTexElementTyp( TexDocElement::RAW );
            preElement.setTexElementValue( rawPreSubString );
            parentElement.texDocElementsList.push_back(preElement);
            
            // the founded element
            searchBegin = found_end + endKeyWord.length() + 1;
            found_begin += beginKeyWord.length();
            texSubstring = texElementValue.substr (
                found_begin,
                (found_end - found_begin)
            );
            TexDocElement subElement;
            subElement.setTexElementTyp( type );
            subElement.setTexElementValue( texSubstring );
            parentElement.texDocElementsList.push_back(subElement);            
            
        }else {
            if( searchBegin < (texElementValue.size() - 1) ) {
                // text after the last found right element.
                rawPostSubString = texElementValue.substr (
                    searchBegin,
                    (texElementValue.size() - 1)
                );
                TexDocElement postElement;
                postElement.setTexElementTyp( TexDocElement::RAW );
                postElement.setTexElementValue( rawPostSubString );
                parentElement.texDocElementsList.push_back(postElement);
            }
            break;
        }
    } // end while-loop
}

void TexParser::cutOutSectionElements(
    TexDocElement& parentElement,
    string keyWord,
    const enum TexDocElement::ElementType& type
){
    string      firstCharacter      = "";
    string      rawPreSubString     = "";
    string      texSubstring        = "";
    string      rawPostSubString    = "";

    string      texElementValue     = parentElement.getTexElementValue();
    size_t      searchBegin         = 0;
    size_t      found_begin         = string::npos;
    size_t      found_end           = string::npos;
    size_t      cutBegin            = 0;
    size_t      cutEnd              = 0;
    string      beginKeyWord        = "\\" + keyWord;
    string      endKeyWord          = "}";
    
    enum TexDocElement::ElementType  elementTyp = parentElement.getTexElementTyp();
    if ( elementTyp != TexDocElement::DOCUMENT
        && elementTyp != TexDocElement::TEXT
        && elementTyp != TexDocElement::RAW
    ){
        // all other ignore....      
        return;
    }

    while ( true) {
        found_begin = texElementValue.find ( 
            beginKeyWord,
            searchBegin 
        );
        found_end = texElementValue.find ( 
            endKeyWord,
            found_begin 
        );
        if ( found_begin!=string::npos || found_end!=string::npos )  {
            // text before found the right element.
            rawPreSubString = texElementValue.substr (
                searchBegin,
                found_begin - searchBegin
            );
            TexDocElement preElement;
            preElement.setTexElementTyp( TexDocElement::RAW );
            preElement.setTexElementValue( rawPreSubString );
            parentElement.texDocElementsList.push_back(preElement);

            // the founded element
            TexDocElement subElement;
            subElement.setTexElementTyp( type );
            searchBegin = found_end + 1;
            cutBegin = found_begin + beginKeyWord.length() ;
            cutEnd = 1;
            while ( true) {
                firstCharacter = texElementValue.substr (
                    cutBegin,
                    1
                );
                cutBegin++;
                if( firstCharacter == "*"){
                    TexDocElement metaData;
                    metaData.setTexElementTyp( TexDocElement::NO_TABCON );
                    subElement.texDocElementsList.push_back(metaData);
                }
                if( firstCharacter == "["){
                    TexDocElement metaData;
                    string shortTitle = "";
                    metaData.setTexElementTyp( TexDocElement::SHORTTITLE );
                    cutEnd = texElementValue.find (
                        "]",
                        cutBegin 
                    );
                    cutEnd = cutEnd - cutBegin;
                    shortTitle = texElementValue.substr (
                        cutBegin,
                        (cutEnd - cutBegin)
                    );
                    metaData.setTexElementValue( shortTitle );
                    subElement.texDocElementsList.push_back(metaData);
                    cutBegin = cutBegin + cutEnd;
                    cutEnd = 1;
                }
                if( firstCharacter == "{"){
                    string title = texElementValue.substr (
                        cutBegin,
                        (found_end - cutBegin)
                    );
                    subElement.setTexElementValue( title );
                    parentElement.texDocElementsList.push_back(subElement);
                    break;
                }      
            } // end inner while
        }else
        {
            // if nothing found do nothing.
            if( searchBegin == 0 ) {
                break;
            }
            // if text after the last right element found .
            if( searchBegin < (texElementValue.size() - 1)
                && searchBegin > 0 )
            {
                rawPostSubString = texElementValue.substr ( 
                    searchBegin,
                    (texElementValue.size() - 1) 
                );
                TexDocElement postElement;
                postElement.setTexElementTyp( TexDocElement::RAW );
                postElement.setTexElementValue( rawPostSubString );
                parentElement.texDocElementsList.push_back(postElement);
            }
            break;
        }
    } // end while-loop
}

void TexParser::cutOutShortElements(
    TexDocElement& parentElement,
    string keyWord,
    const enum TexDocElement::ElementType& type
){
    string beginKeyWord = "\\" + keyWord + "{";
    string endKeyWord = "}";
// DBINF << "Suche nach: " <<  keyWord << "\n";
    string rawPreSubString = "";
    string texSubstring = "";
    string rawPostSubString = "";
    
    string texElementValue = parentElement.getTexElementValue();
    size_t      searchBegin     = 0;
    size_t      found_end       = string::npos;
    size_t      found_begin     = string::npos;

    while ( true) {
        found_begin = texElementValue.find ( beginKeyWord,
            searchBegin );
        found_end = texElementValue.find ( endKeyWord,
            found_begin );
        if ( found_begin!=string::npos || found_end!=string::npos )  {
            // text before found the right element.
            rawPreSubString = texElementValue.substr (
                searchBegin,
                found_begin
            );
            TexDocElement preElement;
            preElement.setTexElementTyp( TexDocElement::RAW );
            preElement.setTexElementValue( rawPreSubString );
            parentElement.texDocElementsList.push_back(preElement);
            
            // the founded element
            searchBegin = found_end;
            found_begin += beginKeyWord.length();
            texSubstring = texElementValue.substr (
                found_begin,
                (found_end - found_begin)
            );
            TexDocElement subElement;
            subElement.setTexElementTyp( type );
            subElement.setTexElementValue( texSubstring );
            parentElement.texDocElementsList.push_back(subElement);            
            
        }else
        {
            // if nothing found do nothing.
            if( searchBegin == 0 ) {
                break;
            }
            
            // if text after the last right element found .
            if( searchBegin < (texElementValue.size() - 1) 
                && searchBegin > 0 )
            {
                rawPostSubString = texElementValue.substr ( 
                    (searchBegin + 1),
                    (texElementValue.size() - 1) 
                );
                TexDocElement postElement;
                postElement.setTexElementTyp( TexDocElement::RAW );
                postElement.setTexElementValue( rawPostSubString );
                parentElement.texDocElementsList.push_back(postElement);
            }
            break;
        }
    } // end while-loop    
    
}

// F =========================================================================


string TexParser::findAndRemoveComments(const string &read_line){
    return TexParser::findAndRemoveCommentsSTD(read_line);
}

string TexParser::findAndRemoveCommentsBoost(const string &read_line){
    // More detais to boost::regex see: 
    // http://www.boost.org/doc/libs/1_47_0/libs/regex/doc/html/boost_regex/syntax/basic_syntax.html
    // It is in use a case sensitive POSIX-Basic expression. The POSIX-Basic 
    // regular expression syntax is used by the Unix utility sed, and 
    // variations are used by grep and emacs. 

    boost::regex pattern (
        "(^\\(.*\\)[^\\\\]*%.*$)|(/^\\(.*\\)[^\\\\]*%.*$)",
        boost::regex::basic
    );
    string replace ("");
    return boost::regex_replace (read_line, pattern, replace);
}    


string TexParser::findAndRemoveCommentsSTD(const string &read_line) {
    string line = read_line;
    if( line.size() == 0 ) {
        return "";
    }
    size_t found_index = line.find("%");
    if(found_index == string::npos)  {
        // no '%' found. Get back all.
        return line;
    }
    if( found_index == 0) {
        // is on the begin of the line.
        return "";        
    }
    if( line.at(found_index -1) != '\\') {
        return line.substr( 0, found_index );
    }    

    do {
        found_index = line.find("%", (found_index + 1));
        if(found_index != string::npos) {
            if( line[(found_index -1)] != '\\') {
                line = line.substr( 0, found_index );
                break;
            } 
        } else {
            break;
        }
    }while( true );
    // no more  '%' found. Get back all.
    return line;
}

// G =========================================================================

TexDocElement& TexParser::getDocumentElement(void){
    for ( list<TexDocElement>::iterator i = TexParser::rootElement.texDocElementsList.begin();
        i != TexParser::rootElement.texDocElementsList.end();
        i++
    ) { int type = i->getTexElementTyp();
        if(type == TexDocElement::DOCUMENT) {
            return *i;
        }
    }
    cerr << "[201111171814] No Document found." << endl;
    throw;    
}

list<TexDocElement&>  TexParser::getListElementOfType(
        TexDocElement& parentElement,
        const enum TexDocElement::ElementType& type){
  
    list<TexDocElement&> listElement;
    list<TexDocElement>::iterator itSubElement;
    string header = "";
    enum TexDocElement::ElementType  elementTyp = parentElement.getTexElementTyp();
   
    if(elementTyp == type){
        listElement.push_back(parentElement);
    }

    for(
        itSubElement = parentElement.texDocElementsList.begin();
        itSubElement != parentElement.texDocElementsList.end();
        itSubElement++
    ) {
        listElement.push_back( PrintElementTree::getListElementOfType(*itSubElement) );
    }
    return listElement;
}
        
TexDocElement& TexParser::getMetadataElement(void){
    for (
        list<TexDocElement>::iterator i = TexParser::rootElement.texDocElementsList.begin();
        i != TexParser::rootElement.texDocElementsList.end();
        i++
    ) {
        int type = i->getTexElementTyp();
        if(type == TexDocElement::METADATA) {
            return *i;
        }
    }
    cerr << "[201111192151] No Metadata found." << endl;
    throw;    
}


TexDocElement& TexParser::getRootElement(void){
    return TexParser::rootElement;
}

// P =========================================================================

void TexParser::pars(){
    TexParser::completeDoc = TexParser::readInputFile(TexParser::inputFileName);
    TexParser::parsDocument();
    TexParser::parsVerbatim( TexParser::getDocumentElement() );
    TexParser::parsInput( TexParser::getRootElement() );
    // second level?
    TexParser::parsVerbatim( TexParser::getDocumentElement() );
    TexParser::parsNewCommand();
    TexParser::parsAllSections( TexParser::getDocumentElement() );
    return;
}

void TexParser::parsAllSections ( TexDocElement& parentElement){
DBINF << "parsAllSections...." <<  endl;
    TexParser::parsSections(
        parentElement,
        "chapter",
        TexDocElement::CHAPTER
    );
    TexParser::parsSections(
        parentElement,
        "paragraph",
        TexDocElement::PARAGRAPH
    );
    TexParser::parsSections(
        parentElement,
        "section",
        TexDocElement::SECTION
    );
    TexParser::parsSections(
        parentElement,
        "subparagraph",
        TexDocElement::SUPPARAGRAPH
    );
    TexParser::parsSections(
        parentElement,
        "subsubsection",
        TexDocElement::SUBSUBSECTION
    );
    TexParser::parsSections(
        parentElement,
        "subsection",
        TexDocElement::SUBSECTION
    );
}

void TexParser::parsDocument(void) {
    string text_document = "";
    string document_metadata = "";
    
    size_t found_begin = TexParser::completeDoc.find("\\begin{document}");
    size_t found_end = TexParser::completeDoc.find("\\end{document}");
    if (found_begin!=string::npos || found_end!=string::npos) {
        // cut metadata.
        document_metadata = TexParser::completeDoc.substr (
            0,
            found_begin
        );
        // cut netto document.
        found_begin += string("\\begin{document}").length();
        text_document = TexParser::completeDoc.substr(
            found_begin,
            (found_end - found_begin)
        );
    }else {
        cerr << "[201111062044] No begin or end of document found." << endl;
        throw;
    }
    TexDocElement metaElement;
    metaElement.setTexElementTyp( TexDocElement::METADATA );
    metaElement.setTexElementValue( document_metadata );
    TexParser::rootElement.texDocElementsList.push_back(metaElement);
    
    TexDocElement docElement;
    docElement.setTexElementTyp( TexDocElement::DOCUMENT );
    docElement.setTexElementValue( text_document );
    TexParser::rootElement.texDocElementsList.push_back(docElement);
}

void TexParser::parsInput(TexDocElement&  parentElement){
    list<TexDocElement>::iterator subElement;
    
    if( parentElement.getTexElementTyp() == TexDocElement::VERBATIM
        || parentElement.getTexElementTyp() == TexDocElement::VERB
    ) { 
        return;
    }else{
        if( parentElement.getTexElementTyp() == TexDocElement::INPUT ) {         
            string fileName = parentElement.getTexElementValue();
            parentElement.setTexElementValue ( TexParser::readInputFile(fileName) );
            parentElement.setTexElementTyp( TexDocElement::RAW );
        }else {
            if ( parentElement.texDocElementsList.size() == 0 ) {
                TexParser::cutOutShortElements( parentElement, 
                    string("input"),
                    TexDocElement::INPUT );
            } 
            for ( subElement = parentElement.texDocElementsList.begin();
                subElement != parentElement.texDocElementsList.end();
                subElement++
            ) {
                TexParser::parsInput( *subElement );
            } // end for-loop
        }
    }
}

void TexParser::parsNewCommand(void){
    TexParser::cutOutShortElements (
        getMetadataElement(),
        string("newcommand"),
        TexDocElement::NEWCOMMAND
    );  

}

void TexParser::parsSections(
    TexDocElement&  parentElement,
    std::string keyWord,
    const enum TexDocElement::ElementType& type
){ 
    list<TexDocElement>::iterator subElement;
  
    if ( parentElement.texDocElementsList.size() == 0 ) {
        TexParser::cutOutSectionElements( 
            parentElement,
            keyWord,
            type
    );
    }
    for ( subElement = parentElement.texDocElementsList.begin();
        subElement != parentElement.texDocElementsList.end();
        subElement++
    ) {
        TexParser::parsSections( *subElement, keyWord, type );
    } // end for-loop

}

void TexParser::parsVerbatim(TexDocElement&  parentElement){
    list<TexDocElement>::iterator subElement;   
    if( parentElement.getTexElementTyp() == TexDocElement::VERB
        || parentElement.getTexElementTyp() == TexDocElement::VERBATIM
    ) {    
        return;
    }
    if( parentElement.texDocElementsList.size() == 0 ) {
        TexParser::cutOutBeginEnd (
            parentElement,
            string("verbatim"),
            TexDocElement::VERBATIM
        );  
        return;
    }
    for( subElement = parentElement.texDocElementsList.begin();
        subElement != parentElement.texDocElementsList.end();
        subElement++
    ) {
        if( (*subElement).getTexElementTyp() == TexDocElement::VERB
            || (*subElement).getTexElementTyp() == TexDocElement::VERBATIM
        ) {
            return;
        } 
        TexParser::parsVerbatim( *subElement );
    }    
}

// R ==========================================================================


string TexParser::readInputFile(string& fileName){
    string completString = "";
    // open fiele to read....
    ifstream tex_file(fileName.c_str());
    if (tex_file.is_open()) {
        while ( tex_file.good() ) {
            string line;
            getline (tex_file,line);
            completString.append( TexParser::findAndRemoveComments(line) );
            completString.append("\n");
        }
    }else{
        cerr << "[201111062048] couldn't open \"" << inputFileName \
            << "\" for reading\n" << endl;
        throw;
    }
    tex_file.close();
    return completString;
}


// S ==========================================================================


void TexParser::setInputFileName(string fileName){
    TexParser::inputFileName = fileName;
}

// T ==========================================================================

TexParser::TexParser(){
    TexParser::rootElement = TexDocElement();
    TexParser::rootElement.setTexElementTyp( TexDocElement::ROOTELEMENT );
}

TexParser::~TexParser(){
    // pass
}