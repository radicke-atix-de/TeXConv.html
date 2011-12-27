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
    * @param  documentElement The element with document data tree.
    */
    static void pars(
        TexDocElement& metadataElement,
        TexDocElement& documentElement
    );

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
     * is a recursion proxy function for cutOutNewcommandElements().
    * @param  parentElement With this element start the search.
     */
    static void parsRecursion(
        TexDocElement& parentElement
    );
    
    /**
    * This function search and replace commands in tree part "document".
    * @param parentElement A element.
    * @param newCommandElement A TexDocElement of type NEWCOMMAND.
    */
    static void replaceNewcommandElements(
        TexDocElement& parentElement,
        TexDocElement* newCommandElement
    );
 
    
    /**
    * is a recursion proxy function for replaceNewcommandElements.
    * @param parentElement A element.
    * @param newCommandElement A TexDocElement of type NEWCOMMAND.
    */ 
    static void replaceRecursion( 
        TexDocElement&  parentElement,
        TexDocElement* newCommandElement 
    );

}; // end class;

} // end namespace

#endif 