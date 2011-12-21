
#include <iostream>
#include <list>
#include <string>


#include "../TexDocElement.h"
#include "CutOut.h"
#include "DocumentParser.h"
#include "InputParser.h"
#include "NewcommandParser.h"
#include "SectionParser.h"
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
/*
list<TexDocElement*>  TexParser::getListElementOfType(
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
          list<TexDocElement*> subList = TexParser::getListElementOfType(
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
}*/
        
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
    TexParser::completeDoc = InputParser::readInputFile(TexParser::inputFileName);
    DocumentParser::parsDocument( 
        TexParser::rootElement,
        TexParser::completeDoc
    );
    TexParser::parsVerbatim( TexParser::getDocumentElement() );
    InputParser::parsInput( TexParser::getRootElement() );
    // second level?
    TexParser::parsVerbatim( TexParser::getDocumentElement() );
    NewcommandParser::pars( TexParser::getMetadataElement() );
    (SectionParser()).parsAllSections( TexParser::getDocumentElement() );
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
