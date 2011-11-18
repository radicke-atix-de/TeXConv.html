
#include "TexDocElement.h"


TexDocElement::TexDocElement(void)
{
    TexDocElement::texElementTyp = TexDocElement::VOID;
}

TexDocElement::~TexDocElement(void)
{

}

// G #########################################################################

enum TexDocElement::ElementType TexDocElement::getTexElementTyp()
{
    return TexDocElement::texElementTyp;
}


std::string TexDocElement::getTexElementValue()
{
    return TexDocElement::texElementValue;
}

 // S #########################################################################

void TexDocElement::setTexElementTyp( enum TexDocElement::ElementType typ)
{
    TexDocElement::texElementTyp = typ;
}

void TexDocElement::setTexElementValue( std::string value )
{
    TexDocElement::texElementValue = value;
}

// T #########################################################################

string TexDocElement::typToString(enum ElementType t) const {
    switch(t) {
    case AUTOR:
        return "AUTOR";
    case BIGSKIP:
        return "BIGSKIP";
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
    case PAGEREF:
        return "PAGEREF";
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
    case SUBSUBSECTION:
        return "SUBSUBSECTION";
    case SUBSECTION:
        return "SUBSECTION";
    case SECTION:
        return "SECTION";
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
