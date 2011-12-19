#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <list>
#include <string>

#include "../TexDocElement.h"

namespace Pars {

class InputParser{
public:

    
    /**
    * It's pars the Tex document of the part "\input{}" and
    * include the file values.
    * @param parentElement this is a recursive function and this
    * beginning element.
    */
    static void parsInput( TexDocElement&  parentElement ); 

    /**
    * Read the imput file and get back.
    * @return Value of file.
    */
    static string readInputFile(std::string& fileName);
    
    

private:
    
    /**
    * search and remove Tex-comments in String.
    * It's a warper class.
    * @param  line Sting with comment (or not).
    * @return Return a string without comments.
    */   
    static string findAndRemoveComments(const std::string &read_line); 
    
    /**
    * search and remove Tex-comments in String.
    * This function us boost-lib.
    * @warning this way is to complex and controllable.
    * @param  line Sting with comment (or not).
    * @return Return a string without comments.
    */      
    static string findAndRemoveCommentsBoost(const std::string &read_line);
    
    /**
    * search and remove Tex-comments in String.
    * This function us std::string-lib.
    * @param  line Sting with comment (or not).
    * @return Return a string without comments.
    */      
    static string findAndRemoveCommentsSTD(const std::string &read_line);

}; // end class;

} // end namespace

#endif 