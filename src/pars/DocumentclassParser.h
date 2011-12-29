#ifndef DOCUMENTCLASSPARSER_H
#define DOCUMENTCLASSPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

class DocumentclassParser{
public:

    
    /**
    * It's pars the Tex document of docomentclass definition elements.
    * @param parentElement this is a recursive function and this
    */
    static void pars( TexDocElement&  parentElement );

private:
    
    static void cutOutDocumentclassElements( TexDocElement& parentElement ); 

    static void parsDocumentclassRecursion( TexDocElement&  parentElement );     
    
};
} // end namespace

#endif 