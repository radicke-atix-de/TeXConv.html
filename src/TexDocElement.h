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
        AUTOR,          /**< tex command author                             */
        DESCRIPTION,    /**< tex command description                        */
        DOCUMENT,       /**< tex command document                           */
        ITEM,           /**< tex command item                               */
        ITEMIZE,        /**< tex command itemize                            */
        LABEL,          /**< tex command label                              */
        LSTLISTING,     /**< tex command lstlisting                         */
        MAKETITLE,      /**< tex command maketitle                          */
        METADATA,       /**< metadata of document                           */
        NEWCOMMAND,     /**< tex command newcommand                         */
        PAGEREF,        /**< tex command pageref                            */
        TABLEOFCONTENTS,/**< tex command tableofcontents                    */
        TABULAR,        /**< tex command tabular                            */
        TEXT,           /**< raw text                                       */
        TITLE,          /**< tex command title                              */
        RAW,            /**< raw tex text                                   */
        REF,            /**< tex command ref                                */
        ROOTELEMENT,    /**< root element.                                  */
        SUBSUBSECTION,  /**< tex command subsection                         */
        SUBSECTION,     /**< tex command subsubsection                      */
        SECTION,        /**< tex command section                            */
        URL,            /**< tex command url                                */
        VERB,           /**< tex command verb                               */
        VERBATIM,       /**< tex command verbatim                           */
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
    */
    int getTexElementTyp();
    
    /**
    * get the value of element.
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