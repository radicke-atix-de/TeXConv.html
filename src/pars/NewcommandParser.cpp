
#include <iostream>
#include <list>
#include <string>

#include "CutOut.h"
#include "NewcommandParser.h"
#include "../TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
using namespace Pars;

    
//  \newcommand{command_name}[count_param]{Remove #1 this #2}
void NewcommandParser::cutOutNewcommandElements(
    TexDocElement& parentElement
){
    const string keyWord = string("newcommand");
//     const enum TexDocElement::ElementType& type = TexDocElement::NEWCOMMAND;
    string      firstCharacter      = "";
    string      rawPreSubString     = "";
    string      texSubstring        = "";
    string      rawPostSubString    = "";

    string      texElementValue     = parentElement.getValue();
    size_t      searchBegin         = 0;
    size_t      found_begin         = string::npos;
    size_t      found_end           = string::npos;
    string      beginKeyWord        = "\\" + keyWord + "{";
    string      endKeyWord          = "}";
    // open "{"
    int opens = 0;
    
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
DBINF << "...Faunded newcommand! \n";
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
            subElement.setType( TexDocElement::NEWCOMMAND );
            
            // cut out command name
            string command_name = texElementValue.substr (
                found_begin + beginKeyWord.length(),
                found_end - ( found_begin + beginKeyWord.length() )
            );   
//             searchBegin = found_end + 1;
            searchBegin = found_end;
            TexDocElement elementName;
            elementName.setType( TexDocElement::NEWCOMMAND_NAME );
            elementName.setValue( command_name );
            subElement.subElementList.push_back( elementName );
            
            // Cut out param count.
            found_begin = texElementValue.find ( 
                "[",
                searchBegin 
            );
            found_end = texElementValue.find ( 
                "]",
                found_begin 
            );    
//             searchBegin = found_end + 1;   
            searchBegin = found_end;        
            string param_count = texElementValue.substr (
                found_begin + 1,
                found_end - ( found_begin + 1 )
            ); 
            TexDocElement elementCount;
            elementCount.setType( TexDocElement::NEWCOMMAND_PARAM_COUNT );
            elementCount.setValue( param_count );
            subElement.subElementList.push_back( elementCount );
            
            // cut out substitute string
            found_begin = texElementValue.find ( 
                "{",
                searchBegin 
            );
            // TODO using 
            for ( unsigned int i=found_begin ; i < texElementValue.size() ; i++){
                if ( texElementValue.at(i) == '{' ){
                    opens++;
                }
                if ( texElementValue.at(i) == '}' ){
                    opens--;
                }
                if (opens == 1) {
                    found_end = i;
                    break;
                }
            }
/*            found_end = texElementValue.find ( 
                "}",
                found_begin 
            );*/    
//             searchBegin = found_end + 1;  
            searchBegin = found_end;        
            string substitute_string = texElementValue.substr (
                found_begin + 1,
                found_end - ( found_begin + 1 )
            ); 
            TexDocElement elementSubstitute;
            elementSubstitute.setType( TexDocElement::NEWCOMMAND_SUBSTITUTE );
            elementSubstitute.setValue( substitute_string );
            subElement.subElementList.push_back( elementSubstitute );
            parentElement.subElementList.push_back( subElement );
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

void NewcommandParser::pars(TexDocElement& metadataElement){
    list<TexDocElement*> listOfElement;
    list<TexDocElement*>::iterator element;
    NewcommandParser::parsRecursion ( metadataElement );  
    
    listOfElement = metadataElement.getListElementOfType(
        TexDocElement::NEWCOMMAND
    );
DBINF << "Faunded newcommands: " <<  listOfElement.size() << "\n";
    for ( element = listOfElement.begin();
        element != listOfElement.end();
        element++
    ) {
//         TexParser::parsSections( *listElement, keyWord, type );
DBINF << "newcommand value: " <<  (*element)->getValue() << endl;

    } // end for-loop        
}

void NewcommandParser::parsRecursion( TexDocElement&  parentElement ){ 
    list<TexDocElement>::iterator subElement;
  
    if ( parentElement.subElementList.size() == 0 ) {
        NewcommandParser::cutOutNewcommandElements ( parentElement );
    }
    for ( subElement = parentElement.subElementList.begin();
        subElement != parentElement.subElementList.end();
        subElement++
    ) {
        NewcommandParser::parsRecursion( *subElement );
    } // end for-loop

}