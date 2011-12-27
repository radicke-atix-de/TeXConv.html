
#include <stdlib.h>
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
    int open_curly_bracket = 0;
    enum TexDocElement::ElementType  elementTyp = parentElement.getType();
    if ( elementTyp != TexDocElement::RAW ){
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
DBINF << "...Faunded newcommand! \n";
            // text before found the right element.
            rawPreSubString = texElementValue.substr (
                searchBegin + 1,
                found_begin - (searchBegin + 1)
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
            for ( unsigned int i=found_begin ; i < texElementValue.size() ; i++){
                if ( texElementValue.at(i) == '{' ){
                    open_curly_bracket++;
                }
                if ( texElementValue.at(i) == '}' ){
                    open_curly_bracket--;
                }
                if (open_curly_bracket == 0) {
                    found_end = i;
DBINF << "searchBegin [1]: " << searchBegin << "\n";   
DBINF << "found_begin: " << found_begin << "\n";   
                    break;
                }
            }
//             searchBegin = found_end; 
DBINF << "searchBegin [2]: " << searchBegin << "\n";  
DBINF << "found_begin: " << found_begin << "\n";  
DBINF << "found_end: " << found_end << "\n";  
            string substitute_string = texElementValue.substr (
                found_begin + 1,
                found_end - ( found_begin + 1 )
            ); 
            searchBegin =  found_end;
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
DBINF << "cut off set\n";           
DBINF << "searchBegin [3]: " << searchBegin << "\n";       
DBINF << "texElementValue.size(): " << texElementValue.size() << "\n";      
                rawPostSubString = texElementValue.substr ( 
                    (searchBegin + 1),
                    (texElementValue.size() - 1) 
                );
DBINF << "rawPostSubString: " << rawPostSubString  << "\n";   
                TexDocElement postElement;
                postElement.setType( TexDocElement::RAW );
                postElement.setValue( rawPostSubString );
                parentElement.subElementList.push_back( postElement );
            }
            break;
        }
    } // end while-loop
}

void NewcommandParser::pars(
    TexDocElement& metadataElement,
    TexDocElement& documentElement
){
    list<TexDocElement*> listOfNewcommand;
    list<TexDocElement*>::iterator newcommand;
    NewcommandParser::parsRecursion ( metadataElement );  
    
    listOfNewcommand = metadataElement.getListElementOfType(
        TexDocElement::NEWCOMMAND
    );
DBINF << "Faunded newcommands: " <<  listOfNewcommand.size() << "\n";
    for ( newcommand = listOfNewcommand.begin();
        newcommand != listOfNewcommand.end();
        newcommand++
    ) {
//         TexParser::parsSections( *listElement, keyWord, type );
DBINF << "newcommand value: " <<  (*newcommand)->getValue() << endl;
        NewcommandParser::replaceRecursion(
            documentElement,
            (*newcommand)
        );
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

void NewcommandParser::replaceRecursion( 
    TexDocElement&  parentElement,
    TexDocElement* newCommandElement 
){ 
    list<TexDocElement>::iterator subElement;
  
    if ( parentElement.subElementList.size() == 0 ) {
        NewcommandParser::replaceNewcommandElements(
            parentElement,
            newCommandElement
        );
    }
    for ( subElement = parentElement.subElementList.begin();
        subElement != parentElement.subElementList.end();
        subElement++
    ) {
DBINF << "eins tiefer.... " << endl;
        NewcommandParser::replaceRecursion( 
            *subElement,
            newCommandElement 
        );
    } // end for-loop

}

void NewcommandParser::replaceNewcommandElements(
    TexDocElement& parentElement,
    TexDocElement* newCommandElement
){
    // Pre test RAW-only....
    enum TexDocElement::ElementType  elementTyp = parentElement.getType();
    if ( elementTyp != TexDocElement::RAW ){
        // all other ignore....      
        return;
    }   
    
    list<TexDocElement*>::iterator      element;
    list<TexDocElement>::iterator       subElement;
    list<string>::iterator              commandParam;
    unsigned int    paramCount          = 1;
    string          commandName         = "";
    string          substituteTamlate   = "";
    string          firstCharacter      = "";
    string          rawPreSubString     = "";
    string          texSubstring        = "";
    string          rawPostSubString    = "";

    string          texElementValue     = parentElement.getValue();
    size_t          searchBegin         = 0;
    size_t          found_begin         = string::npos;
    size_t          cutBegin            = 0;
//    size_t          found_end           = string::npos;
//    string          beginKeyWord        = "";
//    string          endKeyWord          = "}";
    string          substituteString    = "";
    // open "{"
    int             open_curly_bracket  = 0;
    
 

    for ( subElement = newCommandElement->subElementList.begin();
        subElement != newCommandElement->subElementList.end();
        subElement++
    ) {
        if (subElement->getType() == TexDocElement::NEWCOMMAND_NAME){
            commandName = subElement->getValue();
DBINF << "commandName[1]: " << commandName << endl; 
        };
        if (subElement->getType() == TexDocElement::NEWCOMMAND_PARAM_COUNT){
            paramCount = atoi( (subElement->getValue()).c_str() );
        };
        if (subElement->getType() == TexDocElement::NEWCOMMAND_SUBSTITUTE){
            substituteTamlate = subElement->getValue();
        };
    } // end for-loop    
    if ( commandName == "" )
    {
        throw "[20112827142839] error: emty command name!";
    }
    while ( true) {
DBINF << "searchBegin[1]: " << searchBegin << endl; 
        found_begin = texElementValue.find ( 
            commandName,
            searchBegin 
        );
        if ( found_begin!=string::npos )  {
DBINF << "...newcomand gefunden! " << endl;  
            // text before found the right element.
            rawPreSubString = texElementValue.substr (
                searchBegin + 1,
                found_begin - (searchBegin + 1)
            );
            TexDocElement preElement;
            preElement.setType( TexDocElement::RAW );
            preElement.setValue( rawPreSubString );
            parentElement.subElementList.push_back(preElement);

            // the founded element
            list<string> commandPart;
            TexDocElement subElement;
            subElement.setType( TexDocElement::RAW );
            
            // cut out command parts
            searchBegin = found_begin + commandName.size()  ;  
            cutBegin = found_begin + commandName.size() ;
DBINF << "searchBegin[2]: " << searchBegin << endl;        
DBINF << "commandName: " << commandName << endl;  
DBINF << "muss null - commandPart.size(): " << commandPart.size() << endl;   
            

            // cut out substitute string
            for ( unsigned int i=searchBegin ; i < texElementValue.size() ; i++){        
DBINF << "i: " << i << endl;         
DBINF << "texElementValue.at(i): " << texElementValue.at(i) << endl;   
                if ( texElementValue.at(i) == '{' ){
                    open_curly_bracket++;
                }
                if ( texElementValue.at(i) == '}' ){
                    open_curly_bracket--;
                }
DBINF << "open_curly_bracket: " << open_curly_bracket << endl;     
                if (open_curly_bracket == 0) {
                    commandPart.push_back( 
                        texElementValue.substr (
                            cutBegin + 1,
                            ( i -  cutBegin) - 1
                        )
                    );
DBINF << "paramCount: " << paramCount << endl;      
DBINF << "commandPart.size(): " << commandPart.size() << endl;              
                    if( paramCount == commandPart.size() ) {
                        searchBegin = i;
DBINF << "searchBegin [3]: " << searchBegin << endl;    
DBINF << "...newcomand ende! " << endl;                         
                        break;
                    }else{
                        cutBegin = texElementValue.find ( 
                            "{",
                            i 
                        );
                        i = cutBegin -1;
                    }
                }
            }
            // reorganice substitute string.
            for (   commandParam = commandPart.begin();
                    commandParam != commandPart.end();
                    commandParam++
            ) {
                substituteString += (*commandParam);
DBINF << "baue zusammen (commandParam): " << (*commandParam) << endl;  
DBINF << "baue zusammen (sum): " << substituteString << endl;     
            }
DBINF << "searchBegin [4]: " << searchBegin << endl;    
            subElement.setValue( substituteString );
            parentElement.subElementList.push_back( subElement );
        }else
        {     
DBINF << "....ELSE..."  << endl;  
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
                postElement.setType( TexDocElement::RAW );
                postElement.setValue( rawPostSubString );
                parentElement.subElementList.push_back( postElement );
            }
            break;
        }
    } // end while-loop
}