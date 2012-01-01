#ifndef BEGINENDELEMENTPARSER_H
#define BEGINENDELEMENTPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

/**
* universal parser for begin-end tex cammands. 
*/
class BeginEndElementParser{
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
    
    /**
    * search and convert elements of texElementValue in a list
    * of TexDocElement objects. With this form:
    * \begin{keyword}text part \end{keyword}
    * @param  parentElement parent element.
    * @param  keyWord parents element.
    * @param  type a enum ElementType from TexDocElement class.
    */   
    static void beginToEnd (
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