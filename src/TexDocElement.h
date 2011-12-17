#ifndef TEXDOCELEMENT_H
#define TEXDOCELEMENT_H

#include <string>
#include <list>

using namespace std;

class TexDocElement{
public:
    TexDocElement(void);
    ~TexDocElement(void);

    // Properties ############################################################
    /**
    * supportet typs
    */
    enum ElementType {
        AUTOR ,         /**< tex command author                             */
        BIGSKIP,        /**< tex command bigskip                            */
        CHAPTER,        /**< tex command chapter                            */
        DESCRIPTION,    /**< tex command description                        */
        DOCUMENT,       /**< tex command document                           */
        INPUT,          /**< tex command input                              */
        ITEM,           /**< tex command item                               */
        ITEMIZE,        /**< tex command itemize                            */
        LABEL,          /**< tex command label                              */
        LSTLISTING,     /**< tex command lstlisting                         */
        MAKETITLE,      /**< tex command maketitle                          */
        METADATA,       /**< metadata of document                           */
        NEWCOMMAND,     /**< tex command newcommand                         */
        NO_TABCON,      /**< No add section in tableofcontents              */
        PAGEREF,        /**< tex command pageref                            */
        PARAGRAPH,      /**< tex command paragraph                          */
        TABLEOFCONTENTS,/**< tex command tableofcontents                    */
        TABULAR,        /**< tex command tabular                            */
        TEXT,           /**< text                                           */
        TITLE,          /**< tex command title                              */
        RAW,            /**< raw tex text                                   */
        REF,            /**< tex command ref                                */
        ROOTELEMENT,    /**< root element.                                  */
        SECTION,        /**< tex command section                            */
        SHORTTITLE,     /**< short title of a section                       */
        SUPPARAGRAPH,   /**< tex command subparagraph                       */
        SUBSUBSECTION,  /**< tex command subsubsection                      */
        SUBSECTION,     /**< tex command subsection                         */
        URL,            /**< tex command url                                */
        VERB,           /**< tex command verb                               */
        VERBATIM,       /**< tex command verbatim                           */
        VOID            /**< typ is not set                                 */
    };
    
    /**
    * if the object have other children object,
    * then it is in this list.
    */
    list<TexDocElement> subElementList;
    
    /**
    * All objects have a own id. This is store the last using number.
    */    
    static int idCounter;    

    // Methods ###############################################################

    /**
    * @return get beck the typ of element as string.
    */
    string getTypAsString();
    
    /**
    * get the typ of element.
    */
    enum ElementType getType();
    
    /**
    * get the value of element.
    */
    string getValue();
    
    /**
    * set the typ of element.
    * @param type an string of typ name.
    */
    void setType( enum TexDocElement::ElementType type );
    

    /**
    * set the value of element.
    * @param value an string of typ name.
    */
    void setValue( string value );

    /**
    * Convert a enum ElementType in a String.
    * @param type A enum ElementType
    */
    const string typeToString( const enum ElementType& type) const ;

    /**
     * Get the object id.
     * @return a object id.
     * */
    int getID(void){ return id; };
    
private:

    // Properties ############################################################
    /**
    * The name of imput file.
    */
    enum ElementType texElementTyp;
    
    /**
    * If this object only a string, thas is the value.
    */
    string texElementValue;
    
    /**
    * A Object id.
    */    
    int id;
    

    // Methods ###############################################################


};

#endif 