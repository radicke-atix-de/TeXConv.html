#ifndef TEXDOCELEMENT_H
#define TEXDOCELEMENT_H

#include <string>
#include <list>

class TexDocElement
{
public:
    TexDocElement(void);
    ~TexDocElement(void);

    // Properties ############################################################
    /**
    * supportet typs
    */
    enum ElementType
    {
        DOCUMENT,       /**< tex document                                   */
        METADATA,       /**< metadata of document                           */
        TEXT,           /**< raw text                                       */
        ROOTELEMENT,    /**< root element.                                  */
        SUBSUBSECTION,  /**< tex subsection                                 */
        SUBSECTION,     /**< tex subsubsection                              */
        SECTION,        /**< tex section                                    */
        VOID            /**< typ is not set                                 */
    };

    /**
    * if the object have other children object,
    * then it is in this list.
    */
    std::list<TexDocElement> texDocElementsList;    

    
    // Methods ###############################################################
    
    /**
    * get the typ of element.
    * @param typ an string of typ name.
    */
    int getTexElementTyp();
    
    /**
    * get the value of element.
    * @param typ an string of typ name.
    */
    std::string getTexElementValue();
    
    /**
    * set the typ of element.
    * @param typ an string of typ name.
    */
    void setTexElementTyp( int typ );
    

    /**
    * set the value of element.
    * @param typ an string of typ name.
    */
    void setTexElementValue( std::string typ );

    
private:

    // Properties ############################################################
    /**
    * The name of imput file.
    */
    int texElementTyp;
    
    /**
    * If this object only a string, thas is the value.
    */
    std::string texElementValue;


    // Methods ###############################################################


};

#endif 