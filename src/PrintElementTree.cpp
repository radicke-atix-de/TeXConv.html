
#include <iostream>
#include <string>

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
    cout << string(PrintElementTree::treedepth, '\t')
    << "[Typ: "
    <<  parentElement.getTypAsString()
    << "][characters: "
    << (parentElement.getTexElementValue()).size() 
    << "][sub elements: " << parentElement.texDocElementsList.size() << "]"
    << endl;    
    if (PrintElementTree::verboseMode == true)
    {
        PrintElementTree::recordingValue.append( parentElement.getTexElementValue() );
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