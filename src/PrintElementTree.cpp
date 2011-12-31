
#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "PrintElementTree.h"
#include "TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;

void PrintElementTree::printTree( TexDocElement& parentElement ){
    PrintElementTree::printTreeElement( parentElement );
    cout << PrintElementTree::recordingValue << endl;    
}

void PrintElementTree::printTreeElement( TexDocElement& parentElement ){
    list<TexDocElement>::iterator itSubElement;
    string header = "";
    cout << string(PrintElementTree::treedepth, '\t')
    << "[ID: " << parentElement.getID() 
    << "][Typ: "
    <<  parentElement.getTypeAsString()
    << "][characters: "
    << (parentElement.getValue()).size() 
    << "][sub elements: " << parentElement.subElementList.size() << "]"
    << endl;    
    if (PrintElementTree::verboseMode == true) {
        header = "\n##################### [ID:" 
            + boost::lexical_cast<string>( parentElement.getID() )
            + "][Typ: " +parentElement.getTypeAsString() + "]"
            + " #####################\n" ;
        PrintElementTree::recordingValue.append( header );
        if ( parentElement.subElementList.size() == 0 ) {
            PrintElementTree::recordingValue.append( parentElement.getValue() );
        }
    }
    
    PrintElementTree::treedepth++;
    for(
        itSubElement = parentElement.subElementList.begin();
        itSubElement != parentElement.subElementList.end();
        itSubElement++
    ) {
//         cout << string(PrintElementTree::treedepth, '=')
//         << "[Typ: "
//         <<  (*itSubElement).getTypeAsString()
//         << "][characters: "
//         << ((*itSubElement).getValue()).size() 
//         << "][sub elements: " << parentElement.subElementList.size() << "]"
//         << endl;
        // got depth. 
        PrintElementTree::printTreeElement(*itSubElement);
    }
    PrintElementTree::treedepth--;
}

void PrintElementTree::setVerbose ( bool mode ){
    PrintElementTree::verboseMode = mode;
}