#ifndef AUTHORPARSER_H
#define AUTHORPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

/**
* Class parse Tex command \autor{}.
*/
class AuthorParser{
public:

    
    /**
    * It's pars the Tex document of the commands "\autor{} in
    * TexParser::METADATA.
    * @param  metadataElement The element with document meta data tree.
    */
    static void pars(
        TexDocElement& metadataElement
    );

private:

    static void parsRecursion(
        TexDocElement& metadataElement
    );


}; // end class;

} // end namespace

#endif 