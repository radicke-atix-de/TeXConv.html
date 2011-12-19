#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

class DocumentParser{
public:
//     DocumentParser(void);
//     ~DocumentParser(void);

    
    /**
    * It's pars the Tex document. Search "document" and transform in
    * TexDocElement::DOCUMENT and TexDocElement::METADATA.
    * @param  rootElement the root element of tex document.
    */
    static void parsDocument(
        TexDocElement& rootElement,
        const std::string& completeDoc
    );

private:



}; // end class;

} // end namespace

#endif 