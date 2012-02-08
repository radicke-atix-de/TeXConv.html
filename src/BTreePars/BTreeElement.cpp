
#include <iostream>
#include <boost/regex.hpp>
#include "BTreeElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
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

    DBINF << "BTreeElement [1.1]"  << endl;
    m_subElementList.push_back( subElement );
    DBINF << "BTreeElement [1.2]"  << endl;
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
    case BTreeElement::AUTHOR:
        return "AUTHOR";
    case BTreeElement::BEGIN:
        return "BEGIN";
    case BTreeElement::BIGSKIP:
        return "BIGSKIP";
    case BTreeElement::CHAPTER:
        return "CHAPTER";
    case BTreeElement::CURLYBRACKET:
        return "CURLYBRACKET";
    case BTreeElement::DESCRIPTION:
        return "DESCRIPTION";
    case BTreeElement::DOCUMENT:
        return "DOCUMENT";
    case BTreeElement::DOCUMENTCLASS:
        return "DOCUMENCLASS";
    case BTreeElement::END:
        return "END";        
    case BTreeElement::FOOTNOTE:
        return "FOOTNOTE";
    case BTreeElement::INDEX:
        return "INDEX";
    case BTreeElement::INPUT:
        return "INPUT";
    case BTreeElement::ITEM:
        return "ITEM";
    case BTreeElement::ITEMIZE:
        return "ITEMIZE";
    case BTreeElement::LABEL:
        return "LABEL";
    case BTreeElement::LSTLISTING:
        return "LSTLISTING";
    case BTreeElement::MAKETITLE:
        return "MAKETITLE";
    case BTreeElement::METADATA:
        return "METADATA";
    case BTreeElement::NEWCOMMAND:
        return "NEWCOMMAND";
    case BTreeElement::NEWCOMMAND_NAME:
        return "NEWCOMMAND_NAME";
    case BTreeElement::NEWCOMMAND_PARAM_COUNT:
        return "NEWCOMMAND_PARAM_COUNT";
    case BTreeElement::NEWCOMMAND_SUBSTITUTE:
        return "NEWCOMMAND_SUBSTITUTE";      
    case BTreeElement::NO_TABCON:
        return "NO_TABCON";
    case BTreeElement::PAGEREF:
        return "PAGEREF";
    case BTreeElement::PARAGRAPH:
        return "PARAGRAPH";
    case BTreeElement::TABLEOFCONTENTS:
        return "TABLEOFCONTENTS";
    case BTreeElement::TABULAR:
        return "TABULAR";
    case BTreeElement::TEXT:
        return "TEXT";
    case BTreeElement::TEXTIT:
        return "TEXTIT"; 
    case BTreeElement::TEXTBF:
        return "TEXTBF"; 
    case BTreeElement::TEXTSC:
        return "TEXTSC"; 
    case BTreeElement::TEXTTT:
        return "TEXTTT"; 
    case BTreeElement::TITLE:
        return "TITLE";
    case BTreeElement::RAW:
        return "RAW";
    case BTreeElement::REF:
        return "REF";
    case BTreeElement::ROOTELEMENT:
        return "ROOTELEMENT";
    case BTreeElement::SECTION:
        return "SECTION";
    case BTreeElement::SHORTTITLE:
        return "SHORTTITLE";
    case BTreeElement::SQAREBRACKET:
        return "SQAREBRACKET";
    case BTreeElement::SUPPARAGRAPH:
        return "SUPPARAGRAPH";
    case BTreeElement::SUBSUBSECTION:
        return "SUBSUBSECTION";
    case BTreeElement::SUBSECTION:
        return "SUBSECTION";
    case BTreeElement::URL:
        return "URL";
    case BTreeElement::VERB:
        return "VERB";
    case BTreeElement::VERBATIM:
        return "VERBATIM";
    case BTreeElement::VOID:
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
    else if ("\\index" == withoutAsterisk) {
        return BTreeElement::INDEX;
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
