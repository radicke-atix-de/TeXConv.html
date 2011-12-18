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
    * search and convert elements of texElementValue in a list
    * of TexDocElement objects. With this form:
    * \begin{keyword}text part \end{keyword}
    * @param  parentElement parent element.
    * @param  keyWord parents element.
    * @param  type a enum ElementType from TexDocElement class.
    * @return Return a string without comments.
    */   
    void cutOutBeginEnd (
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
    void cutOutShortElements (
        TexDocElement& parentElement,
        std::string keyWord,
        const enum TexDocElement::ElementType& type
    );    
    
    /**
    * search and remove Tex-comments in String.
    * It's a warper class.
    * @param  line Sting with comment (or not).
    * @return Return a string without comments.
    */   
    std::string findAndRemoveComments(const std::string &read_line); 
    
    /**
    * search and remove Tex-comments in String.
    * This function us boost-lib.
    * @warning this way is to complex and controllable.
    * @param  line Sting with comment (or not).
    * @return Return a string without comments.
    */      
    std::string findAndRemoveCommentsBoost(const std::string &read_line);
    
    /**
    * search and remove Tex-comments in String.
    * This function us std::string-lib.
    * @param  line Sting with comment (or not).
    * @return Return a string without comments.
    */      
    std::string findAndRemoveCommentsSTD(const std::string &read_line);
    
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
    * @throw string If the the Function not fount TexParser::METADATA.
    * @return Get back a TexDocElement with type "TexParser::METADATA".
    */       
    TexDocElement& getMetadataElement(void);


    
    /**
    * It's pars the Tex document of the part "\input{}" and
    * include the file values.
    * @param parentElement this is a recursive function and this
    * beginning element.
    */
    void parsInput( TexDocElement&  parentElement );


    /**
    * It's pars the Tex document of the part "\newcommand" in
    * TexParser::METADATA and pars TexParser::DOCUMENT part
    * to find and remove definition of new commands.
    */
    void parsNewCommand(void);


    
     /**
    * It's pars the Tex document of verbatim elements.
    * @param parentElement 
    */   
    void parsVerbatim( TexDocElement& parentElement );
    
    /**
    * Tread the imput file and copy to propertie completeDoc.
    */
    std::string readInputFile(std::string& fileName);

};

} // end namespace

#endif 