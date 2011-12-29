#ifndef LABELPARSER_H
#define LABELPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

class LabelParser{
public:

    
    /**
    * It's pars the Tex document of docomentclass definition elements.
    * @param parentElement this is a recursive function and this
    */
    static void pars( TexDocElement&  parentElement );

private:
    
    static void cutOutElements( TexDocElement& parentElement ); 

    static void parsRecursion( TexDocElement&  parentElement );     
    
};
} // end namespace

#endif 