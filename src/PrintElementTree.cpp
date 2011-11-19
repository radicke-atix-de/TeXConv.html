
#include <iostream>
#include <string>

#include "PrintElementTree.h"
#include "TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;

void PrintElementTree::printTree( TexDocElement& parentElement )
{
    list<TexDocElement>::iterator itSubElement;
    cout << string(PrintElementTree::treedepth, '=')
    << "[Typ: "
    <<  parentElement.getTypAsString()
    << "][Zeichelänge: "
    << (parentElement.getTexElementValue()).size() 
    << "]" << endl;    
    
    PrintElementTree::treedepth++;
    for
    (
        itSubElement = parentElement.texDocElementsList.begin();
        itSubElement != parentElement.texDocElementsList.end();
        itSubElement++
    )
    {
        cout << string(PrintElementTree::treedepth, '=')
        << "[Typ: "
        <<  (*itSubElement).getTypAsString()
        << "][Zeichelänge: "
        << ((*itSubElement).getTexElementValue()).size() 
        << "]" << endl;
        // got depth. 
        PrintElementTree::printTree(*itSubElement);
    }
    PrintElementTree::treedepth--;
}