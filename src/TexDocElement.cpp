
#include "TexDocElement.h"


TexDocElement::TexDocElement(void) //: id(TexDocElement::idCounte)
{
    TexDocElement::texElementTyp = TexDocElement::VOID;
    TexDocElement::idCounter++;
    TexDocElement::id = TexDocElement::idCounter;
}

TexDocElement::~TexDocElement(void)
{

}

// G #########################################################################

list<TexDocElement*>  TexDocElement::getListElementOfType(
    const enum TexDocElement::ElementType& type
){
    return TexDocElement::getListElementOfType( this, type);
}

list<TexDocElement*>  TexDocElement::getListElementOfType(
        TexDocElement* parentElement,
        const enum TexDocElement::ElementType& type){
  
    list<TexDocElement*> listElement;
    list<TexDocElement>::iterator itSubElement;
    string header = "";
    enum TexDocElement::ElementType  elementTyp = parentElement->getType();
   
    if(elementTyp == type){
        listElement.push_back ( parentElement );
    }

    for(
        itSubElement = parentElement->subElementList.begin();
        itSubElement != parentElement->subElementList.end();
        itSubElement++
    ) {
          list<TexDocElement*> subList = TexDocElement::getListElementOfType(
              &(*itSubElement),
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

string TexDocElement::getTypAsString(){
    return TexDocElement::typeToString( TexDocElement::texElementTyp );
}

enum TexDocElement::ElementType TexDocElement::getType(){
    return TexDocElement::texElementTyp;
}


std::string TexDocElement::getValue(){
    return TexDocElement::texElementValue;
}

// I #########################################################################

int TexDocElement::idCounter = 0;

// S #########################################################################

void TexDocElement::setType( enum TexDocElement::ElementType type){
    TexDocElement::texElementTyp = type;
}

void TexDocElement::setValue( std::string value ){
    TexDocElement::texElementValue = value;
}

// T #########################################################################

const string TexDocElement::typeToString( const enum ElementType& t) const {
    switch(t) {
    case AUTOR:
        return "AUTOR";
    case BIGSKIP:
        return "BIGSKIP";
    case CHAPTER:
        return "CHAPTER";
    case DESCRIPTION:
        return "DESCRIPTION";
    case DOCUMENT:
        return "DOCUMENT";
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
