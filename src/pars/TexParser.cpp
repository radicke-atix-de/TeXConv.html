
#include <iostream>
#include <list>
#include <string>


#include "../TexDocElement.h"
#include "BeginEndElementParser.h"
#include "CutOut.h"
#include "DocumentclassParser.h"
#include "DocumentParser.h"
#include "InputParser.h"
#include "NewcommandParser.h"
#include "SectionParser.h"
#include "SimpleElementParser.h"
#include "TexParser.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
using namespace Pars;

TexDocElement& TexParser::getDocumentElement(void){
    for ( list<TexDocElement>::iterator i = TexParser::rootElement.subElementList.begin();
        i != TexParser::rootElement.subElementList.end();
        i++
    ) { int type = i->getType();
        if(type == TexDocElement::DOCUMENT) {
            return *i;
        }
    }
    cerr << "[201111171814] No Document found." << endl;
    throw;    
}

TexDocElement& TexParser::getMetadataElement(void){
    for (
        list<TexDocElement>::iterator i = TexParser::rootElement.subElementList.begin();
        i != TexParser::rootElement.subElementList.end();
        i++
    ) {
        int type = i->getType();
        if(type == TexDocElement::METADATA) {
            return *i;
        }
    }
    cerr << "[201111192151] No Metadata found." << endl;
    throw;    
}

TexDocElement& TexParser::getRootElement(void){
    return TexParser::rootElement;
}

void TexParser::pars(){
DBINF << "TexParser::pars... "  << endl;  
    TexParser::completeDoc = InputParser::readInputFile( 
        TexParser::inputFileName
    );
    DocumentParser::parsDocument( 
        TexParser::rootElement,
        TexParser::completeDoc
    );
    //TexParser::parsVerbatim( TexParser::getDocumentElement() );
    BeginEndElementParser::pars( 
        TexParser::getDocumentElement(), 
        "verbatim",
        TexDocElement::VERBATIM
    );
    
    InputParser::parsInput( TexParser::getRootElement() );
    // verbatim second cycle...
    //TexParser::parsVerbatim( TexParser::getDocumentElement() );
    BeginEndElementParser::pars( 
        TexParser::getDocumentElement(), 
        "verbatim",
        TexDocElement::VERBATIM
    );
    NewcommandParser::pars( 
        TexParser::getMetadataElement(), 
        TexParser::getRootElement()
    );
/*    DocumentclassParser::pars( TexParser::getMetadataElement() );
    SectionParser::parsAllSections( TexParser::getDocumentElement() );
    // ---------- BeginEndElementParser ------------------
    BeginEndElementParser::pars( 
        TexParser::getDocumentElement(), 
        "itemize",
        TexDocElement::ITEMIZE
    );
    BeginEndElementParser::pars( 
        TexParser::getDocumentElement(), 
        "lstlisting",
        TexDocElement::LSTLISTING
    );
    // ---------- SimpleElementParser ------------------
    SimpleElementParser::pars( 
        TexParser::getMetadataElement(),
        "title",
        TexDocElement::TITLE
    );
    SimpleElementParser::pars( 
        TexParser::getMetadataElement(),
        "author",
        TexDocElement::AUTHOR
    );
    SimpleElementParser::pars( 
        TexParser::getDocumentElement(), 
        "footnote",
        TexDocElement::FOOTNOTE
    );
    SimpleElementParser::pars( 
        TexParser::getDocumentElement(), 
        "label",
        TexDocElement::LABEL
    );
    SimpleElementParser::pars( 
        TexParser::getDocumentElement(),
        "emph",
        TexDocElement::TEXTIT
    );
    SimpleElementParser::pars( 
        TexParser::getDocumentElement(),
        "textit",
        TexDocElement::TEXTIT
    );
    */
//     SimpleElementParser::pars( 
//         TexParser::getDocumentElement(),
//         "textbf",
//         TexDocElement::TEXTBF
//     );
//     SimpleElementParser::pars( 
//         TexParser::getDocumentElement(),
//         "textsc",
//         TexDocElement::TEXTSC
//     );
//     SimpleElementParser::pars( 
//         TexParser::getDocumentElement(),
//         "texttt",
//         TexDocElement::TEXTTT
//     );
    return;
}


void TexParser::parsVerbatim(TexDocElement&  parentElement){
    list<TexDocElement>::iterator subElement;   
    if( parentElement.getType() == TexDocElement::VERB
        || parentElement.getType() == TexDocElement::VERBATIM
    ) {    
        return;
    }
    if( parentElement.subElementList.size() == 0 ) {
        CutOut::beginToEnd (
            parentElement,
            string("verbatim"),
            TexDocElement::VERBATIM
        );  
        return;
    }
    for( subElement = parentElement.subElementList.begin();
        subElement != parentElement.subElementList.end();
        subElement++
    ) {
        if( (*subElement).getType() == TexDocElement::VERB
            || (*subElement).getType() == TexDocElement::VERBATIM
        ) {
            return;
        } 
        TexParser::parsVerbatim( *subElement );
    }    
}

void TexParser::setInputFileName(string fileName){
    TexParser::inputFileName = fileName;
}


TexParser::TexParser(){
    TexParser::rootElement = TexDocElement();
    TexParser::rootElement.setType( TexDocElement::ROOTELEMENT );
}

TexParser::~TexParser(){
    // pass
}
