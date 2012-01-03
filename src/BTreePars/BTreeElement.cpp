
#include "BTreeElement.h"


namespace BTreePars {
    
BTreeElement::BTreeElement(void) : nextElement(0)
{
    BTreeElement::texElementTyp = BTreeElement::VOID;
    BTreeElement::idCounter++;
    BTreeElement::id = BTreeElement::idCounter;
}

BTreeElement::~BTreeElement(void)
{

}

// G #########################################################################

list<BTreeElement*>  BTreeElement::getListElementOfType(
    const enum BTreeElement::ElementType& type
){
    return BTreeElement::getListElementOfType( this, type);
}

list<BTreeElement*>  BTreeElement::getListElementOfType(
        BTreeElement* parentElement,
        const enum BTreeElement::ElementType& type
){
    list<BTreeElement*> listElement;
    list<BTreeElement*>::iterator itSubElement;
    string header = "";
    enum BTreeElement::ElementType  elementTyp = parentElement->getType();
   
    if(elementTyp == type){
        listElement.push_back ( parentElement );
    }

    for(
        itSubElement = parentElement->subElementList.begin();
        itSubElement != parentElement->subElementList.end();
        itSubElement++
    ) {
          list<BTreeElement*> subList = BTreeElement::getListElementOfType(
              (*itSubElement),
              type
          );
          listElement.insert (
                listElement.end(),
                subList.begin(),
                subList.end()
          );

    }
    return listElement;
}

string BTreeElement::getTypeAsString(){
    return BTreeElement::typeToString( BTreeElement::texElementTyp );
}

enum BTreeElement::ElementType BTreeElement::getType(){
    return BTreeElement::texElementTyp;
}


std::string BTreeElement::getValue(){
    return BTreeElement::texElementValue;
}

// I #########################################################################

int BTreeElement::idCounter = 0;

// S #########################################################################

void BTreeElement::setType( enum BTreeElement::ElementType type){
    BTreeElement::texElementTyp = type;
}

void BTreeElement::setValue( std::string value ){
    BTreeElement::texElementValue = value;
}

// T #########################################################################

const string BTreeElement::typeToString( const enum ElementType& t) const {
    switch(t) {
    case AUTHOR:
        return "AUTHOR";
    case BIGSKIP:
        return "BIGSKIP";
    case CHAPTER:
        return "CHAPTER";
    case DESCRIPTION:
        return "DESCRIPTION";
    case DOCUMENT:
        return "DOCUMENT";
    case DOCUMENTCLASS:
        return "DOCUMENCLASS";
    case FOOTNOTE:
        return "FOOTNOTE";
    case INPUT:
        return "INPUT";
    case ITEM:
        return "ITEM";
    case ITEMIZE:
        return "ITEMIZE";
    case LABEL:
        return "LABEL";
    case LSTLISTING:
        return "LSTLISTING";
    case MAKETITLE:
        return "MAKETITLE";
    case METADATA:
        return "METADATA";
    case NEWCOMMAND:
        return "NEWCOMMAND";
    case NEWCOMMAND_NAME:
        return "NEWCOMMAND_NAME";
    case NEWCOMMAND_PARAM_COUNT:
        return "NEWCOMMAND_PARAM_COUNT";
    case NEWCOMMAND_SUBSTITUTE:
        return "NEWCOMMAND_SUBSTITUTE";      
    case NO_TABCON:
        return "NO_TABCON";
    case PAGEREF:
        return "PAGEREF";
    case PARAGRAPH:
        return "PARAGRAPH";
    case TABLEOFCONTENTS:
        return "TABLEOFCONTENTS";
    case TABULAR:
        return "TABULAR";
    case TEXT:
        return "TEXT";
    case TEXTIT:
        return "TEXTIT"; 
    case TEXTBF:
        return "TEXTBF"; 
    case TEXTSC:
        return "TEXTSC"; 
    case TEXTTT:
        return "TEXTTT"; 
    case TITLE:
        return "TITLE";
    case RAW:
        return "RAW";
    case REF:
        return "REF";
    case ROOTELEMENT:
        return "ROOTELEMENT";
    case SECTION:
        return "SECTION";
    case SHORTTITLE:
        return "SHORTTITLE";
    case SUPPARAGRAPH:
        return "SUPPARAGRAPH";
    case SUBSUBSECTION:
        return "SUBSUBSECTION";
    case SUBSECTION:
        return "SUBSECTION";
    case URL:
        return "URL";
    case VERB:
        return "VERB";
    case VERBATIM:
        return "VERBATIM";
    case VOID:
        return "VOID";
    default: 
        return "unknow";
    }
}

} // namenspace end