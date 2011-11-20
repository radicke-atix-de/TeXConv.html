
#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "PrintElementTree.h"
#include "TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;

void PrintElementTree::printTree( TexDocElement& parentElement )
{
    PrintElementTree::printTreeElement( parentElement );
    cout << PrintElementTree::recordingValue << endl;    
}

void PrintElementTree::printTreeElement( TexDocElement& parentElement )
{
    list<TexDocElement>::iterator itSubElement;
    string header = "";
    cout << string(PrintElementTree::treedepth, '\t')
    << "[ID: " << parentElement.getID() 
    << "][Typ: "
    <<  parentElement.getTypAsString()
    << "][characters: "
    << (parentElement.getTexElementValue()).size() 
    << "][sub elements: " << parentElement.texDocElementsList.size() << "]"
    << endl;    
    if (PrintElementTree::verboseMode == true)
    {
        header = "\n##################### [ID:" 
            + boost::lexical_cast<string>( parentElement.getID() )
            + "][Typ: " +parentElement.getTypAsString() + "]"
            + " #####################\n" ;
        PrintElementTree::recordingValue.append( header );
        if ( parentElement.texDocElementsList.size() == 0 )
        {
            PrintElementTree::recordingValue.append( parentElement.getTexElementValue() );
        }
    }
    
    PrintElementTree::treedepth++;
    for
    (
        itSubElement = parentElement.texDocElementsList.begin();
        itSubElement != parentElement.texDocElementsList.end();
        itSubElement++
    )
    {
//         cout << string(PrintElementTree::treedepth, '=')
//         << "[Typ: "
//         <<  (*itSubElement).getTypAsString()
//         << "][characters: "
//         << ((*itSubElement).getTexElementValue()).size() 
//         << "][sub elements: " << parentElement.texDocElementsList.size() << "]"
//         << endl;
        // got depth. 
        PrintElementTree::printTreeElement(*itSubElement);
    }
    PrintElementTree::treedepth--;
}

void PrintElementTree::setVerbose ( bool mode )
{
    PrintElementTree::verboseMode = mode;
}