
#include <iostream>
#include <list>
#include <string>
//#include <boost/regex.hpp>

#include "DocumentParser.h"
#include "../TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
using namespace Pars;


void DocumentParser::parsDocument(
    TexDocElement& rootElement,
    const std::string& completeDoc
){
    string text_document = "";
    string document_metadata = "";
    
    size_t found_begin = completeDoc.find("\\begin{document}");
    size_t found_end = completeDoc.find("\\end{document}");
    if (found_begin!=string::npos || found_end!=string::npos) {
        // cut metadata.
        document_metadata = completeDoc.substr (
            0,
            found_begin
        );
        // cut netto document.
        found_begin += string("\\begin{document}").length();
        text_document = completeDoc.substr(
            found_begin,
            (found_end - found_begin)
        );
    }else {
        cerr << "[201111062044] No begin or end of document found." << endl;
        throw;
    }
    TexDocElement metaElement;
    metaElement.setType( TexDocElement::METADATA );
    metaElement.setValue( document_metadata );
    rootElement.subElementList.push_back(metaElement);
    
    TexDocElement docElement;
    docElement.setType( TexDocElement::DOCUMENT );
    docElement.setValue( text_document );
    rootElement.subElementList.push_back(docElement);  
    if ( rootElement.subElementList.size() > 0 ){
        rootElement.setValue("");
DBINF << "delet value of: " << rootElement.getID() << endl;
        if ( rootElement.getType() == TexDocElement::RAW ) {
            rootElement.setType( TexDocElement::VOID );
        }
    }    
}