#ifndef BTREEELEMENT_H
#define BTREEELEMENT_H

#include <string>
#include <list>
#include "BTreeElement.h"

using namespace std;

namespace BTreePars {
    
class BTreeElement{
public:
    BTreeElement(void);
    ~BTreeElement(void);

    /**
    * supportet typs
    */
    enum ElementType {
        AUTHOR ,        /**< tex command author                             */
        BIGSKIP,        /**< tex command bigskip                            */
        CHAPTER,        /**< tex command chapter                            */
        DESCRIPTION,    /**< tex command description                        */
        DOCUMENT,       /**< tex command document                           */
        DOCUMENTCLASS,  /**< tex command documentclass                      */
        FOOTNOTE,       /**< tex command footnote                           */
        INPUT,          /**< tex command input                              */
        ITEM,           /**< tex command item                               */
        ITEMIZE,        /**< tex command itemize                            */
        LABEL,          /**< tex command label                              */
        LSTLISTING,     /**< tex command lstlisting                         */
        MAKETITLE,      /**< tex command maketitle                          */
        METADATA,       /**< metadata of document                           */
        NEWCOMMAND,     /**< tex command newcommand                         */
        NEWCOMMAND_NAME,        /**< name of newcommand                     */
        NEWCOMMAND_PARAM_COUNT, /**< count of newcommand params             */
        NEWCOMMAND_SUBSTITUTE,  /**< The substitude text for newcommand     */
        NO_TABCON,      /**< No add section in tableofcontents              */
        PAGEREF,        /**< tex command pageref                            */
        PARAGRAPH,      /**< tex command paragraph                          */
        RAW,            /**< raw tex text                                   */
        REF,            /**< tex command ref                                */
        ROOTELEMENT,    /**< root element.                                  */
        SECTION,        /**< tex command section                            */
        SHORTTITLE,     /**< short title of a section                       */
        SUPPARAGRAPH,   /**< tex command subparagraph                       */
        SUBSUBSECTION,  /**< tex command subsubsection                      */
        SUBSECTION,     /**< tex command subsection                         */
        TABLEOFCONTENTS,/**< tex command tableofcontents                    */
        TABULAR,        /**< tex command tabular                            */
        TEXT,           /**< text                                           */
        TEXTIT,         /**< tex command emph and textit                    */
        TEXTBF,         /**< tex command textbf                             */
        TEXTSC,         /**< tex command textsc                             */
        TEXTTT,         /**< tex command texttt                             */
        TITLE,          /**< tex command title                              */
        URL,            /**< tex command url                                */
        VERB,           /**< tex command verb                               */
        VERBATIM,       /**< tex command verbatim                           */
        VOID            /**< typ is not set                                 */
    };
    

    
    /**
    * if the object have other children object,
    * then it is in this list.
    */
    list<BTreeElement*> subElementList;
    
    /**
    * All objects have a own id. This is store the last using number.
    */    
    static int idCounter;    
   
    /**
    * This is a poninter to next elment. the last element have a 0 poninter
    */    
    BTreeElement* nextElement;

    // Methods ###############################################################

    /**
    * @return get beck the typ of element as string.
    */
    string getTypeAsString();
    
    /**
    * get the typ of element.
    */
    enum BTreeElement::ElementType getType();
    
    /**
    * get the value of element.
    */
    string getValue();
    
    /**
    * set the typ of element.
    * @param type an string of typ name.
    */
    void setType( enum BTreeElement::ElementType type );
    

    /**
    * set the value of element.
    * @param value an string of typ name.
    */
    void setValue( string value );

    /**
     * Get the object id.
     * @return a object id.
     * */
    int getID(void){ return id; };
    
    /**
    * Get a list of Element select bei type. 
    * @param  type The type of selection.
    * @param  parentElement The top element where the search starts.
    * @return Get back a list of BTreeElement with type of param type.
    */
    list<BTreeElement*>  getListElementOfType(
        const enum BTreeElement::ElementType& type);    
    
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
    /**
    * Get a list of Element select bei type. 
    * @param  type The type of selection.
    * @param  parentElement The top element where the search starts.
    * @return Get back a list of BTreeElement with type of param type.
    */
    list<BTreeElement*>  getListElementOfType(
        BTreeElement* parentElement,
        const enum BTreeElement::ElementType& type);  

    /**
    * Convert a enum ElementType in a String.
    * @param type A enum ElementType
    */
    const string typeToString( const enum ElementType& type) const ;    
};

} //end namespace
#endif 