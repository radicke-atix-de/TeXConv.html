#ifndef TEXPARSER_H
#define TEXPARSER_H

#include <string>

#include "TexDocElement.h"

class TexParser
{
public:
    TexParser(void);
    ~TexParser(void);
    /**
    * pars the imput file.
    */
    void pars(void);
    /**
    * set the name of imput file.
    * @param fileName an integer argument.
    */
    void setInputFileName(std::string);

private:

    // Properties ------------------------------------------------------------
    /**
    * The name of imput file.
    */
    std::string inputFileName;
    /**
    * Content of imput file..
    */
    std::string completeDoc;

    /**
    * This ist the root element.
    */
    TexDocElement rootElement;

    // Methods ---------------------------------------------------------------
    /**
    * search and convert elements of texElementValue in a list
    * of TexDocElement objekts. With this form:
    * \begin{keyword}text part \end{keyword}
    * @param  parentElement parent element.
    * @param  keyWord parents element.
    * @param  typ a enum ElementType from TexDocElement class.
    * @return Return a Stnin without comments.
    */   
    void cutOutBeginEnd
    (
        TexDocElement& parentElement,
        std::string keyWord,
        const int& typ
    );
    
    /**
    * search and convert elements of texElementValue in a list 
    * of TexDocElement objekts. With this form:
    * \kexword{text part}
    * @param  parentElement parent element.
    * @param  keyWord parents element.
    * @param  typ a enum ElementType from TexDocElement class.
    * @return Return a Stnin without comments.
    */   
    void cutOutShortElements
    (
        TexDocElement& parentElement,
        std::string keyWord,
        const int& typ
    );    
    
    /**
    * search and remove Tex-comments in String.
    * It's a wraper class.
    * @param  line Sting with coment (or not).
    * @return Return a Stnin without comments.
    */   
    std::string findAndRemoveComments(const std::string &read_line); 
    
    /**
    * search and remove Tex-comments in String.
    * This function us boost-lib.
    * @warning this way is to complex and controllable.
    * @param  line Sting with coment (or not).
    * @return Return a Stnin without comments.
    */      
    std::string findAndRemoveCommentsBoost(const std::string &read_line);
    
    /**
    * search and remove Tex-comments in String.
    * This function us std::string-lib.
    * @param  line Sting with coment (or not).
    * @return Return a Stnin without comments.
    */      
    std::string findAndRemoveCommentsSTD(const std::string &read_line);
    
    /**
    * @throw string If the the Function not fount TexParser::DOCUMENT.
    * @return Get back a TexDocElement with typ "TexParser::DOCUMENT".
    */    
    TexDocElement& getDocumentElement(void);    

    /**
    * It's pars the Tex document of the part "document".
    */
    void parsDocument(void);
    
    /**
    * It's pars the Tex document of the part "\input{}" and
    * include the file values.
    * @param parentElement this is a recursive function ans this 
    * beginning element.
    */
    void parsInput( TexDocElement&  parentElement );
    
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

#endif 