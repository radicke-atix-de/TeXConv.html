#ifndef NEWCOMMANDPARSER_H
#define NEWCOMMANDPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

class NewcommandParser{
public:

    
    /**
    * It's pars the Tex document of the part "\newcommand" in
    * TexParser::METADATA and pars TexParser::DOCUMENT part
    * to find and remove definition of new commands.
    * @param  metadataElement The element with document meta data tree.
    */
    static void pars(TexDocElement&  metadataElement);

private:

    /**
    * Function is search tex command "\newcommand", and
    * convert to TexDocElement::NEWCOMMAND.
    * @param  parentElement this element us.
    */
    static void cutOutNewcommandElements(
        TexDocElement& parentElement
    );

    /**
     * is a recursion proxy function.
    * @param  parentElement With this element start the search.
     */
    static void parsRecursion(
        TexDocElement& parentElement
    );

}; // end class;

} // end namespace

#endif 