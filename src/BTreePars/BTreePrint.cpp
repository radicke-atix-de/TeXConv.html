
#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "BTreePrint.h"
#include "BTreeElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;

namespace BTreePars {

void BTreePrint::printTree( BTreeElement* parentElement ){
    BTreePrint::printTreeElement( parentElement );
    cout << BTreePrint::recordingValue << endl;
}

void BTreePrint::printTreeElement( BTreeElement* parentElement ){
    string header = "";
    list<BTreeElement*> subElementList = parentElement->getSubElementList();
    cout << string(BTreePrint::treedepth, '\t')
    << "[ID: " << parentElement->getID()
    << "][Typ: "
    <<  parentElement->getTypeAsString()
    << "][characters: "
    << (parentElement->getValue()).size()
    << "][sub elements: " << subElementList.size() << "]"
    << endl;    
    if (BTreePrint::verboseMode == true) {
        header = "\n##################### [ID:" 
            + boost::lexical_cast<string>( parentElement->getID() )
            + "][Typ: " +parentElement->getTypeAsString() + "]"
            + " #####################\n" ;
        BTreePrint::recordingValue.append( header );
        if ( subElementList.size() == 0 ) {
            BTreePrint::recordingValue.append( parentElement->getValue() );
        }
    }
    
    BTreePrint::treedepth++;
    for(
    	list<BTreeElement*>::iterator itSubElement = subElementList.begin();
        itSubElement != subElementList.end();
        itSubElement++
    ) {
//         cout << string(BTreePrint::treedepth, '=')
//         << "[Typ: "
//         <<  (*itSubElement).getTypeAsString()
//         << "][characters: "
//         << ((*itSubElement).getValue()).size() 
//         << "][sub elements: " << parentElement.subElementList.size() << "]"
//         << endl;
        // got depth. 
        BTreePrint::printTreeElement( (*itSubElement) );
    }
    BTreePrint::treedepth--;
}

void BTreePrint::setVerbose ( bool mode ){
    BTreePrint::verboseMode = mode;
}

} // end namespace BTreePars
