
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <boost/regex.hpp>

#include "SimpleElementParser.h"
#include "../TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
using namespace Pars;


void SimpleElementParser::cutOutElements(
    TexDocElement& parentElement,
    std::string keyWord,
    const enum TexDocElement::ElementType& type
){
DBINF << "SimpleElementParser::cutOutElements...." <<  endl;
    string      firstCharacter      = "";
    string      rawPreSubString     = "";
    string      texSubstring        = "";
    string      rawPostSubString    = "";

    string      texElementValue     = parentElement.getValue();
    size_t      searchBegin         = 0;
    size_t      found_begin         = string::npos;
    size_t      found_end           = string::npos;
    size_t      cutBegin            = 0;
 //   size_t      cutEnd              = 0;
    string      beginKeyWord        = "\\" + keyWord;
    string      endKeyWord          = "}";
    
    enum TexDocElement::ElementType  elementTyp = parentElement.getType();
    if ( elementTyp == TexDocElement::VERBATIM 
         || elementTyp == TexDocElement::VERB ){
        // all other ignore....      
        return;
    }

    while ( true ) {
        found_begin = texElementValue.find ( 
            beginKeyWord,
            searchBegin 
        );
        found_end = texElementValue.find ( 
            endKeyWord,
            found_begin 
        );
        if ( found_begin!=string::npos || found_end!=string::npos )  {
DBINF << "...found LabelElements...." <<  endl;
            // text before found the right element.
            rawPreSubString = texElementValue.substr (
                searchBegin,
                found_begin - searchBegin
            );
            TexDocElement preElement;
            preElement.setType( TexDocElement::RAW );
            preElement.setValue( rawPreSubString );
            parentElement.subElementList.push_back(preElement);

            // the founded element
            TexDocElement subElement;
            subElement.setType( type );
            searchBegin = found_end + 1;
            cutBegin = found_begin + beginKeyWord.length() ;
 //           cutEnd = 1;
            while ( true) {
                firstCharacter = texElementValue.substr (
                    cutBegin,
                    1
                );
                cutBegin++;
                if( firstCharacter == "["){
 /*               
                    TexDocElement metaData;
                    string shortTitle = "";
                    metaData.setType( TexDocElement::SHORTTITLE );
                    cutEnd = texElementValue.find (
                        "]",
                        cutBegin 
                    );
                    cutEnd = cutEnd - cutBegin;
                    shortTitle = texElementValue.substr (
                        cutBegin,
                        (cutEnd - cutBegin)
                    );
                    metaData.setValue( shortTitle );
                    subElement.subElementList.push_back(metaData);
                    cutBegin = cutBegin + cutEnd;
                    cutEnd = 1;
*/
                }
                if( firstCharacter == "{"){
                    string documentclasstype = texElementValue.substr (
                        cutBegin,
                        (found_end - cutBegin)
                    );
                    subElement.setValue( documentclasstype );
                    parentElement.subElementList.push_back(subElement);
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
                postElement.setType( TexDocElement::RAW );
                postElement.setValue( rawPostSubString );
                parentElement.subElementList.push_back(postElement);
            }
            break;
        }
    } // end while-loop
}

void SimpleElementParser::pars ( 
    TexDocElement& parentElement,
    std::string keyWord,
    const enum TexDocElement::ElementType& type 
){
DBINF << "SimpleElementParser...." <<  endl;
    SimpleElementParser::parsRecursion(
        parentElement,
        keyWord,
        type
    );
}

void SimpleElementParser::parsRecursion(
    TexDocElement&  parentElement,
    std::string keyWord,
    const enum TexDocElement::ElementType& type 
){ 
    list<TexDocElement>::iterator subElement;
  
    if ( parentElement.subElementList.size() == 0 ) {
        SimpleElementParser::cutOutElements( 
            parentElement,
            keyWord,
            type
        );
    }
    for ( subElement = parentElement.subElementList.begin();
        subElement != parentElement.subElementList.end();
        subElement++
    ) {
        SimpleElementParser::parsRecursion( 
            *subElement,
            keyWord,
            type 
        );
    } // end for-loop

}