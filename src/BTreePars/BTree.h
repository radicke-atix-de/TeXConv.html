#ifndef BETREE_H
#define BETREE_H

#include <fstream>
#include <string>
#include <list>
#include "BTreeElement.h"
using namespace std;

namespace BTreePars {
    
    /**
    * @class BTree this a tree like B+ Tree:
    * http://en.wikipedia.org/wiki/B%2B_tree
    * */
    class BTree{
    public:
        BTree(void);
        ~BTree(void);

        // Properties #########################################################

        // Methods ############################################################  

        /**
         * get beck complet TeX document text.
         */
        string getCompleteDocText(void);

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
        * Convert a enum ElementType in a String.
        * @param type A enum ElementType
        */
        const string typeToString( 
            const enum BTreeElement::ElementType& type
        ) const ;
        
   
        
    private:

        // Properties #########################################################
        /**
        * Content of input file.
        */
        string completeDocText;
        
        /**
        * The name of input file.
        */
        std::string inputFileName;
        
        /**
        * This is the root element.
        */
        BTreeElement* rootElement;

        /**
        * list for all BTreeElement pointer.
        */
        list<BTreeElement*> elementList;   

        // Methods ############################################################
        
        /**
        * search and remove Tex-comments in String.
        * It's a warper class.
        * @param  line Sting with comment (or not).
        * @return Return a string without comments.
        */   
        static string findAndRemoveComments(const std::string &read_line); 
        
        /**
        * Read the imput file and get back.
        * @return Value of file.
        */
        static string readInputFile(std::string& fileName);        
    };

} //end namespace
#endif 
