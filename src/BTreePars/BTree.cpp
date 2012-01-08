
#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include "BTree.h"
#include "BTreeElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
namespace BTreePars {

BTree::BTree(void) : completeDocText(""), lastElement(0)
{
    BTree::rootElement = new BTreeElement();
    BTree::rootElement->setType( BTreeElement::ROOTELEMENT );
    BTree::elementList.push_back( BTree::rootElement );
}

BTree::~BTree(void)
{

}

// F #########################################################################


string BTree::findAndRemoveComments(const string &read_line) {
    string line = read_line;
    if( line.size() == 0 ) {
        return "";
    }
    size_t found_index = line.find("%");
    if(found_index == string::npos)  {
        // no '%' found. Get back all.
        return line;
    }
    if( found_index == 0) {
        // is on the begin of the line.
        return "";        
    }
    if( line.at(found_index -1) != '\\') {
        return line.substr( 0, found_index );
    }    

    do {
        found_index = line.find("%", (found_index + 1));
        if(found_index != string::npos) {
            if( line[(found_index -1)] != '\\') {
                line = line.substr( 0, found_index );
                break;
            } 
        } else {
            break;
        }
    }while( true );
    // no more  '%' found. Get back all.
    return line;
}

// G #########################################################################

string BTree::getCompleteDocText(void){
	return BTree::completeDocText;
}

// I #########################################################################



// P #########################################################################

void BTree::pars(){
    DBINF << "BTree::pars... "  << endl;
    // counter for open [
    unsigned int openSquareBrackets = 0;
    // counter for open {
    unsigned int openCurlyBrackets = 0;
    // counter for open {
    unsigned int lastBracketsIndex = 0;

    if ( BTree::lastElement == 0) {
        BTree::lastElement = BTree::rootElement;

    }

    BTree::completeDocText = BTree::readInputFile( 
        BTree::inputFileName
    );
    for ( unsigned int i = 0; i < BTree::completeDocText.size(); i++) {
//    	DBINF <<  BTree::completeDocText.at(i) << endl;
        if ( BTree::completeDocText.at(i) == '{'){
            openCurlyBrackets++;
            string textPart = BTree::completeDocText.substr (
                lastBracketsIndex,
                (i - lastBracketsIndex)
            );
            DBINF <<  "lastBracketsIndex: " << lastBracketsIndex << endl;
            DBINF <<  "i: " << i << endl;
            DBINF <<  "zeichen: " << (i - lastBracketsIndex) << endl;
            BTree::createNewElement( textPart );

            lastBracketsIndex = i;
        }
        if ( BTree::completeDocText.at(i) == '['){
            openSquareBrackets++;
            string textPart = BTree::completeDocText.substr (
                lastBracketsIndex,
                i - lastBracketsIndex
            );
            DBINF <<  "lastBracketsIndex: " << lastBracketsIndex << endl;
            DBINF <<  "i: " << i << endl;
            DBINF <<  "zeichen: " << (i - lastBracketsIndex) << endl;
            BTree::createNewElement( textPart );

            lastBracketsIndex = i;
        }
        if ( BTree::completeDocText.at(i) == ']'){
            openSquareBrackets--;

            lastBracketsIndex = i;
        }
        if ( BTree::completeDocText.at(i) == '}'){
            openCurlyBrackets--;

            lastBracketsIndex = i;
        }

    }

    DBINF << "...BTree::pars Ende. "  << endl;
    return;
}

void BTree::createNewElement( const string& textPart){

    BTreeElement* be = new BTreeElement();
    BTree::elementList.push_back( be );
    BTree::lastElement->addSubElement( be );
    boost::regex re("\\section");
    if ( boost::regex_search(textPart, re) ) {
       DBINF << "found: BTreeElement::SECTION "  << endl;
       be->setType( BTreeElement::BTreeElement::SECTION );
    }

    size_t found_index = textPart.find("\\section");
    if(found_index != string::npos)  {
        DBINF << "found (2): BTreeElement::SECTION "  << endl;
        DBINF << "Text part: " << textPart  << endl;
    }
//    be->setValue( value );

}

string BTree::readInputFile(string& fileName){
    string completString = "";
    // open fiele to read....
    ifstream tex_file(fileName.c_str());
    if (tex_file.is_open()) {
        while ( tex_file.good() ) {
            string line;
            getline (tex_file,line);
            completString.append( BTree::findAndRemoveComments(line) );
            completString.append("\n");
        }
    }else{
        cerr << "[201201031622] couldn't open \"" << fileName \
            << "\" for reading\n" << endl;
        throw;
    }
    tex_file.close();
    return completString;
}

// S #########################################################################

void BTree::setInputFileName(string fileName){
    BTree::inputFileName = fileName;
}

// T #########################################################################

} //end namespace
