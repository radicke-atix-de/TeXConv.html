
#include <boost/regex.hpp>
#include "BTreeElement.h"

namespace BTreePars {
    
BTreeElement::BTreeElement(void) : 
		m_texElementValue(""),
		m_nextSubElement(0)
{
//	n_nextSubElement = 0;
	m_preSubElement = 0;
	m_parentElement = 0;
	m_texElementTyp = BTreeElement::VOID;
    BTreeElement::idCounter++;
    m_id = BTreeElement::idCounter;
}

BTreeElement::~BTreeElement(void)
{

}

// A ########################################################################

void BTreeElement::addSubElement( BTreeElement* subElement ){
    m_subElementList.push_back( subElement );
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
    list<BTreeElement*> subElementList = parentElement->getSubElementList();
    for(
        itSubElement = subElementList.begin();
        itSubElement != subElementList.end();
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

BTreeElement* BTreeElement::getNextSubElement( ){
	return m_nextSubElement;
}

BTreeElement* BTreeElement::getPreSubElement( ){
	return m_preSubElement;
}

BTreeElement* BTreeElement::getParentElement( ){
	return m_parentElement;
}

string BTreeElement::getTypeAsString(){
    return BTreeElement::typeToString( m_texElementTyp );
}

enum BTreeElement::ElementType BTreeElement::getType(){
    return m_texElementTyp;
}


std::string BTreeElement::getValue(){
    return m_texElementValue;
}

// I #########################################################################

int BTreeElement::idCounter = 0;

// S #########################################################################

void BTreeElement::setNextSubElement( BTreeElement* nse ){
	m_nextSubElement = nse;
}

void BTreeElement::setPreSubElement( BTreeElement* pse ){
	m_preSubElement = pse;
}

void BTreeElement::setParentElement( BTreeElement* pe ){
	m_parentElement = pe;
}

void BTreeElement::setType( enum BTreeElement::ElementType type){
    m_texElementTyp = type;
}

void BTreeElement::setValue( std::string value ){
    m_texElementValue = value;
}

// T #########################################################################

string BTreeElement::typeToString( const enum ElementType& t) {
    switch(t) {
    case AUTHOR:
        return "AUTHOR";
    case BEGIN:
        return "BEGIN";
    case BIGSKIP:
        return "BIGSKIP";
    case CHAPTER:
        return "CHAPTER";
    case CURLYBRACKET:
        return "CURLYBRACKET";
    case DESCRIPTION:
        return "DESCRIPTION";
    case DOCUMENT:
        return "DOCUMENT";
    case DOCUMENTCLASS:
        return "DOCUMENCLASS";
    case END:
        return "END";        
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
    case SQAREBRACKET:
        return "SQAREBRACKET";
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

// S ##########################################################################

enum BTreeElement::ElementType BTreeElement::stringToType( 
		const string& stringTyp
) {
	
    boost::regex patternBlank (" ");
    string withoutBlank = boost::regex_replace (
    	stringTyp, 
    	patternBlank, 
        string("")
    );	
    
    boost::regex patternAsterisk ("\\*");
    string withoutAsterisk = boost::regex_replace (
    	stringTyp, 
    	patternAsterisk, 
        ""
    );	
	
    if ( "\\autor" == withoutAsterisk ) {
        return BTreeElement::AUTHOR;
    }
    else if ( "\\begin" == withoutAsterisk ) {
        return BTreeElement::BEGIN;
    }
    else if ( "\\bigskip" == withoutAsterisk ) {
        return BTreeElement::BIGSKIP;
    }
    else if ( "\\chepter" == withoutAsterisk ) {
        return BTreeElement::CHAPTER;
    }
    else if ( "\\documentclass" == withoutAsterisk ) {
        return BTreeElement::DOCUMENTCLASS;
    }
    else if ( "\\end" == withoutAsterisk ) {
        return BTreeElement::END;
    }
    else if ( "\\footnote" == withoutAsterisk ) {
        return BTreeElement::FOOTNOTE;
    }
    else if ( "\\input" == withoutAsterisk ) {
        return BTreeElement::INPUT;
    }
    else if ( "\\item" == withoutAsterisk ) {
        return BTreeElement::ITEM;
    }
    else if ( "\\label" == withoutAsterisk ) {
        return BTreeElement::LABEL;
    }
    else if ( "\\maketitle" == withoutAsterisk ) {
        return BTreeElement::MAKETITLE;
    }
    else if ( "\\newcommand" == withoutAsterisk ) {
        return BTreeElement::NEWCOMMAND;
    }
    else if ( "\\pageref" == withoutAsterisk ) {
        return BTreeElement::PAGEREF;
    }
    else if ( "\\paragraph" == withoutAsterisk ) {
        return BTreeElement::PARAGRAPH;
    }
    else if ( "\\tableofcontents" == withoutAsterisk ) {
        return BTreeElement::TABLEOFCONTENTS;
    }
    else if ( "\\textit" == withoutAsterisk ) {
        return BTreeElement::TEXTIT; 
    }
    else if ( "\\textbf" == withoutAsterisk ) {
        return BTreeElement::TEXTBF; 
    }
    else if ( "\\textsc" == withoutAsterisk ) {
        return BTreeElement::TEXTSC; 
    }
    else if ( "\\texttt" == withoutAsterisk ) {
        return BTreeElement::TEXTTT; 
    }
    else if ( "\\title" == withoutAsterisk ) {
        return BTreeElement::TITLE;
    }
    else if ( "\\ref" == withoutAsterisk ) {
        return BTreeElement::REF;
    }
    else if ( "\\section" == withoutAsterisk ) {
        return BTreeElement::SECTION;
    }
    else if ( "\\subparagraph" == withoutAsterisk ) {
        return BTreeElement::SUPPARAGRAPH;
    }
    else if ( "\\subsubsection" == withoutAsterisk ) {
        return BTreeElement::SUBSUBSECTION;
    }
    else if ( "\\subsection" == withoutAsterisk ) {
        return BTreeElement::SUBSECTION;
    }
    else if ( "\\url" == withoutAsterisk ) {
        return BTreeElement::URL;
    }
    else if ( "\\verb|" == withoutAsterisk ) {
        return BTreeElement::VERB;
    }
    else { 
    	cerr << "[201201221343] unknow type:" << withoutAsterisk << endl;
    	//throw ;
    	return BTreeElement::VOID;
    }
	
}


} // namenspace end
