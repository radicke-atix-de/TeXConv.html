
#include "TexDocElement.h"


TexDocElement::TexDocElement(void)
{
    TexDocElement::texElementTyp = TexDocElement::VOID;
}

TexDocElement::~TexDocElement(void)
{

}

// G #########################################################################

int TexDocElement::getTexElementTyp()
{
    return TexDocElement::texElementTyp;
}


std::string TexDocElement::getTexElementValue()
{
    return TexDocElement::texElementValue;
}

 // S #########################################################################

void TexDocElement::setTexElementTyp( int typ)
{
    TexDocElement::texElementTyp = typ;
}

void TexDocElement::setTexElementValue( std::string value )
{
    TexDocElement::texElementValue = value;
}