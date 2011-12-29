#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>

#include "CutOut.h"
#include "AuthorParser.h"
#include "../TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
using namespace Pars;

void AuthorParser::pars( TexDocElement& metadataElement ){

    AuthorParser::parsRecursion ( metadataElement );  
   
}

void AuthorParser::parsRecursion( TexDocElement&  parentElement ){ 
    list<TexDocElement>::iterator subElement;
   
    enum TexDocElement::ElementType  elementTyp = parentElement.getType();
    if ( elementTyp == TexDocElement::VERBATIM 
         || elementTyp == TexDocElement::VERB ){
        // all other ignore....      
        return;
    }
  
    if ( parentElement.subElementList.size() == 0 ) {
        CutOut::shortElements (
            parentElement,
            "author",
            TexDocElement::AUTHOR
        );       
    }
    for ( subElement = parentElement.subElementList.begin();
        subElement != parentElement.subElementList.end();
        subElement++
    ) {
        AuthorParser::parsRecursion( *subElement );
    } // end for-loop

}

