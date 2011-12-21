#ifndef SECTIONPARSER_H
#define SECTIONPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

class SectionParser{
public:

    
    /**
    * It's pars the Tex document of sections elements.
    * @param parentElement this is a recursive function and this
    */
    static void parsAllSections( TexDocElement&  parentElement );

private:
    
    /**
    * search sections in text of texElementValue and convert in a list
    * of TexDocElement objects. for example, searching string
    * with this form:
    * \section*[shot title]{long title}
    * @param  parentElement parent element.
    * @param  keyWord section element. For example: "section*".
    * @param  type a enum ElementType from TexDocElement class.
    */
    static void cutOutSectionElements (
        TexDocElement& parentElement,
        std::string keyWord,
        const enum TexDocElement::ElementType& type
    );      

    /**
    * It's pars the Tex document of sections elements.
    * @param parentElement this is a recursive function and this
    * beginning element.
    * @param  keyWord parents element.
    * @param  typ a enum ElementType from TexDocElement class.
    */
    static void parsSections(
        TexDocElement&  parentElement,
        std::string keyWord,
        const enum TexDocElement::ElementType& type
    );

}; // end class;

} // end namespace

#endif 