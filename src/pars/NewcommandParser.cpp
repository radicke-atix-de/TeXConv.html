
#include <iostream>
#include <list>
#include <string>

#include "NewcommandParser.h"
#include "../TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
using namespace Pars;


static void NewcommandParser::pars(TexDocElement& metadataElement){
    list<TexDocElement*> listOfElement;
    list<TexDocElement*>::iterator element;
    CutOut::shortElements (
        metadataElement,
        string("newcommand"),
        TexDocElement::NEWCOMMAND
    );  
    listOfElement = TexParser::getListElementOfType(
        metadataElement,
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

