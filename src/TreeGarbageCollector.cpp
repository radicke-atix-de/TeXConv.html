
#include <iostream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "TreeGarbageCollector.h"
#include "TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;

void TreeGarbageCollector::start( TexDocElement& parentElement ){
DBINF << "TreeGarbageCollector::start...." << endl;  
    TreeGarbageCollector::recursiveWalk( parentElement );  
}

void TreeGarbageCollector::recursiveWalk( TexDocElement& parentElement ){
    list<TexDocElement>::iterator subElement;
    list<TexDocElement>::iterator subSubElement;

    for(
        subElement = parentElement.subElementList.begin();
        subElement != parentElement.subElementList.end();
        subElement++
    ) {
        if ( (*subElement).getType() != TexDocElement::RAW ) {
            continue;
        }
        if ( (*subElement).subElementList.size() > 0 ) {
DBINF << "lösche: " << (*subElement).getTypAsString() << endl;  
                (*subElement).subElementList.erase ( subElement );
            for(
                subSubElement = (*subElement).subElementList.begin();
                subSubElement != (*subElement).subElementList.end();
                subSubElement++
            ) {
                parentElement.subElementList.insert (
                    subElement, 
                    (*subSubElement)
                );
            }
            
        } else {
            continue;
        }
    }
}

