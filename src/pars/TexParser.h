#ifndef TEXPARSER_H
#define TEXPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

class TexParser{
public:
    TexParser(void);
    ~TexParser(void);
    /**
    * pars the input file.
    */
    void pars(void);
    
    /**
    * set the name of input file.
    * @param fileName a string argument is needed.
    */
    void setInputFileName(std::string fileName);

    /**
    * @throw string If the the Function not fount TexParser::METADATA.
    * @return Get back a TexDocElement with type "TexParser::METADATA".
    */       
    TexDocElement& getMetadataElement(void);    
    
    /**
    * Get back the ElementType::ROOTELEMENT.
    * @return The root element.
    */
    TexDocElement& getRootElement(void);

private:

    // Properties ------------------------------------------------------------
    /**
    * The name of input file.
    */
    std::string inputFileName;
    /**
    * Content of input file..
    */
    std::string completeDoc;

    /**
    * This is the root element.
    */
    TexDocElement rootElement;

    // Methods ---------------------------------------------------------------
    
    /**
    * @throw string If the the Function not fount TexParser::DOCUMENT.
    * @return Get back a TexDocElement with type "TexParser::DOCUMENT".
    */    
    TexDocElement& getDocumentElement(void);

    /**
    * Get a list of Element select bei type. 
    * @param  type The type of selection.
    * @param  parentElement The top element where the search starts.
    * @return Get back a list of TexDocElement with type of param type.
    */
    list<TexDocElement*>  getListElementOfType(
        TexDocElement* parentElement,
        const enum TexDocElement::ElementType& type);
    
     /**
    * It's pars the Tex document of verbatim elements.
    * @param parentElement 
    */   
    void parsVerbatim( TexDocElement& parentElement );

};

} // end namespace

#endif 