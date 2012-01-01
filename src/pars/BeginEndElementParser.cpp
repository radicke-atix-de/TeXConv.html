
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <boost/regex.hpp>

#include "BeginEndElementParser.h"
#include "../TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
using namespace Pars;

void BeginEndElementParser::beginToEnd(
    TexDocElement& parentElement, 
    string keyWord,
    const enum TexDocElement::ElementType& type
){
    string beginKeyWord = "\\begin{" + keyWord + "}";
    string endKeyWord = "\\end{" + keyWord + "}";
    string rawPreSubString = "";
    string texSubstring = "";
    string rawPostSubString = "";
    
    
    string texElementValue = parentElement.getValue();
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
DBINF << "Gefunden: "  << keyWord << endl;          
            // text before found the right element.
            rawPreSubString = texElementValue.substr (
                searchBegin,
                found_begin
            );
            TexDocElement preElement;
            preElement.setType( TexDocElement::RAW );
            preElement.setValue( rawPreSubString );
            parentElement.subElementList.push_back(preElement);
/*          
DBINF << "preElement.getID(): " << preElement.getID() << endl;
DBINF << "preElement.getValue().size(): " <<  preElement.getValue().size() << "\n";   
            if ( preElement.getValue().size() == 0 ) {            
DBINF << "...RAUS!!" << endl; 
                parentElement.subElementList.push_back(preElement);
            }
*/           
            // the founded element
            searchBegin = found_end + endKeyWord.length() + 1;
            found_begin += beginKeyWord.length();
            texSubstring = texElementValue.substr (
                found_begin,
                (found_end - found_begin)
            );
            TexDocElement subElement;
            subElement.setType( type );
            subElement.setValue( texSubstring );
            parentElement.subElementList.push_back(subElement);            
            
        }else {
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
                postElement.setType( TexDocElement::RAW );
                postElement.setValue( rawPostSubString );
                parentElement.subElementList.push_back(postElement);
            }
            break;            
        }
    } // end while-loop
    if ( parentElement.subElementList.size() > 0 ){
        parentElement.setValue("");
DBINF << "delet value of: " << parentElement.getID() << endl;
        if ( parentElement.getType() == TexDocElement::RAW ) {
            parentElement.setType( TexDocElement::VOID );
        }
    }
}


void BeginEndElementParser::pars ( 
    TexDocElement& parentElement,
    std::string keyWord,
    const enum TexDocElement::ElementType& type 
){
DBINF << "BeginEndElementParser...." <<  endl;
    BeginEndElementParser::parsRecursion(
        parentElement,
        keyWord,
        type
    );
}

void BeginEndElementParser::parsRecursion(
    TexDocElement&  parentElement,
    std::string keyWord,
    const enum TexDocElement::ElementType& type 
){ 
    list<TexDocElement>::iterator subElement;
  
    if ( parentElement.subElementList.size() == 0 ) {
        BeginEndElementParser::beginToEnd( 
            parentElement,
            keyWord,
            type
        );
    }
    for ( subElement = parentElement.subElementList.begin();
        subElement != parentElement.subElementList.end();
        subElement++
    ) {
        BeginEndElementParser::parsRecursion( 
            *subElement,
            keyWord,
            type 
        );
    } // end for-loop

}