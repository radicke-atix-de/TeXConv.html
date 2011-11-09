#ifndef TEXPARSER_H
#define TEXPARSER_H

#include <string>

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

    // Methods
    
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
    * Tread the imput file and copy to propertie completeDoc.
    */
    void readImputFile(void);
    
    /**
    * It's pars the Tex document and get back the value of "document".
    */
    std::string parsDocument(void);

};

#endif 