#ifndef SIMPLEELEMENTPARSER_H
#define SIMPLEELEMENTPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

/**
* universal parser for simple tex camands. 
*/
class SimpleElementParser{
public:

    
    /**
    * It's pars the Tex document of simple elements (no pharameters).
    * @param parentElement this is a recursive function and this
    * @param  keyWord parents element.
    * @param  type a enum ElementType from TexDocElement class.
    */
    static void pars( 
        TexDocElement&  parentElement,
        std::string keyWord,
        const enum TexDocElement::ElementType& type 
    );

private:
    
    static void cutOutElements( 
        TexDocElement& parentElement,
        std::string keyWord,
        const enum TexDocElement::ElementType& type  
    ); 

    static void parsRecursion( 
        TexDocElement&  parentElement,
        std::string keyWord,
        const enum TexDocElement::ElementType& type  
    );     
    
};
} // end namespace

#endif 