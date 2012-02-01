
#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "PrintBTree.h"
#include "BTreeElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
namespace BTreePars {

void PrintBTree::printTree( BTreeElement*  parentElement ){
    PrintBTree::printTreeElement( parentElement );
    cout << PrintBTree::recordingValue << endl;    
}

void PrintBTree::printTreeElement(  BTreeElement*  parentElement ){
    list<BTreeElement*>::iterator itSubElement;
    string header = "";
    list<BTreeElement*> subBTList = parentElement->getSubElementList();
    cout << string(PrintBTree::treedepth, '\t')
    << "[ID: " << parentElement->getID() 
    << "][Typ: "
    <<  parentElement->getTypeAsString()
    << "][characters: "
    << (parentElement->getValue()).size() 
    << "][sub elements: " << subBTList.size() << "]"
    << endl;    
    if (PrintBTree::verboseMode == true) {
        header = "\n##################### [ID:" 
            + boost::lexical_cast<string>( parentElement->getID() )
            + "][Typ: " +parentElement->getTypeAsString() + "]"
            + " #####################\n" ;
        PrintBTree::recordingValue.append( header );
        if ( subBTList.size() == 0 ) {
            PrintBTree::recordingValue.append( parentElement->getValue() );
        }
    }
    
    PrintBTree::treedepth++;
    for(
        itSubElement = subBTList.begin();
        itSubElement != subBTList.end();
        itSubElement++
    ) {
//         cout << string(PrintBTree::treedepth, '=')
//         << "[Typ: "
//         <<  (*itSubElement).getTypeAsString()
//         << "][characters: "
//         << ((*itSubElement).getValue()).size() 
//         << "][sub elements: " << parentElement.subElementList.size() << "]"
//         << endl;
        // got depth. 
        PrintBTree::printTreeElement(*itSubElement);
    }
    PrintBTree::treedepth--;
}

void PrintBTree::setVerbose ( bool mode ){
    PrintBTree::verboseMode = mode;
}

}// end namespace 