
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
//         << (*itSubElement).typToString((*itSubElement).getTexElementTyp())
        <<  (*itSubElement).getTypAsString()
        << "][Zeiche: "
        << ((*itSubElement).getTexElementValue()).size() << endl;
        // got depth. 
        PrintElementTree::printTree(*itSubElement);
    }
    PrintElementTree::treedepth--;
}