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

    // Properties
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

    // Methods
    /**
    * search and convert elements of texElementValue in TexDocElement objekts.
    * @param  element parents element.
    * @param  keyWord parents element.
    * @return Return a Stnin without comments.
    */   
    void TexParser::cutOfBeginEnd
    (
        TexDocElement &element,
        std::string keyWord
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
    * It's pars the Tex document and get back the value of "document".
    */
    void parsDocument(void);
    
    /**
    * Tread the imput file and copy to propertie completeDoc.
    */
    void readImputFile(void);


};

#endif 