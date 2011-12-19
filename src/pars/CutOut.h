#ifndef CUTOUT_H
#define CUTOUT_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

class CutOut{
public:

    
    /**
    * search and convert elements of texElementValue in a list
    * of TexDocElement objects. With this form:
    * \begin{keyword}text part \end{keyword}
    * @param  parentElement parent element.
    * @param  keyWord parents element.
    * @param  type a enum ElementType from TexDocElement class.
    * @return Return a string without comments.
    */   
    static void beginToEnd (
        TexDocElement& parentElement,
        std::string keyWord,
        const enum TexDocElement::ElementType& type
    );
    

    
    /**
    * search text parts in texElementValue and convert this in a list
    * of TexDocElement objects. for example, searching string
    * with this form:
    * \kexword{text part}
    * @param  parentElement parent element.
    * @param  keyWord like this: "input" für "\input{file.txt}".
    * @param  type a enum ElementType from TexDocElement class.
    */   
    static void shortElements (
        TexDocElement& parentElement,
        std::string keyWord,
        const enum TexDocElement::ElementType& type
    ); 


private:
    


}; // end class;

} // end namespace

#endif 