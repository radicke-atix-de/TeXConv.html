
#include <iostream>
#include <string>
#include <boost/regex.hpp>
#include "BTree.h"
#include "BTreeElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
namespace BTreePars {

BTree::BTree(void) : 
		completeDocText("")
{
	BTree::lastSubElement = 0;
    BTree::rootElement = new BTreeElement();
    BTree::rootElement->setType( BTreeElement::ROOTELEMENT );
    BTree::elementList.push_back( BTree::rootElement );
	BTree::lastParentElement = BTree::rootElement;
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

BTreeElement* BTree::getRootElement(void){
	return BTree::rootElement;
}

// I #########################################################################



// P #########################################################################

void BTree::pars(){
    DBINF << "BTree::pars [1]"  << endl;
    // counter for open [
    unsigned int openSquareBrackets = 0;
    // counter for open {
    unsigned int openCurlyBrackets = 0;
    // counter for open {
    unsigned int lastBracketsIndex = 0;

    if ( BTree::lastParentElement == 0) {
        BTree::lastParentElement = BTree::rootElement;

    }
    DBINF << "BTree::pars [2]"  << endl;

    BTree::completeDocText = BTree::readInputFile( 
        BTree::inputFileName
    );
    for ( unsigned int i = 0; i < BTree::completeDocText.size(); i++) {
        DBINF << "BTree::pars [2.1]"  << endl;
        if ( BTree::completeDocText.at(i) == '{'){
            DBINF << "BTree::pars [3.1]"  << endl;
            openCurlyBrackets++;
            // new parent BTreeElement
            DBINF << "BTree::pars [3.1.1]"  << endl;
            BTreeElement* newParentBE = new BTreeElement();
            DBINF << "BTree::pars [3.1.2]"  << endl;
            BTree::elementList.push_back( newParentBE );
            DBINF << "BTree::pars [3.1.3]"  << endl;
            newParentBE->setType( BTreeElement::CURLYBRACKET );
            DBINF << "BTree::pars [3.1.5]"  << endl;
            newParentBE->setParentElement( BTree::lastParentElement );
            DBINF << "BTree::pars [3.1.6]"  << endl;
            BTree::lastParentElement->addSubElement( newParentBE );
            DBINF << "BTree::pars [3.1.7]"  << endl;
            BTree::lastParentElement->setNextSubElement( newParentBE );
            DBINF << "BTree::pars [3.1.8]"  << endl;
            newParentBE->setPreSubElement( BTree::lastParentElement );
            DBINF << "BTree::pars [3.1.9]"  << endl;
            BTree::lastParentElement = newParentBE;
            DBINF << "BTree::pars [3.1.10]"  << endl;
            BTree::lastSubElement = 0;
            DBINF << "BTree::pars [3.2]"  << endl;
            
            // new sub element.
            BTreeElement* newSubBE = new BTreeElement();
            BTree::elementList.push_back( newSubBE );
            newSubBE->setType( BTreeElement::RAW );
            newSubBE->setValue( "" );
            newSubBE->setParentElement( BTree::lastParentElement );
            newSubBE->setPreSubElement( BTree::lastSubElement );
            if ( BTree::lastSubElement != 0 ) {
            	BTree::lastSubElement->setNextSubElement( newSubBE );
            }
            BTree::lastSubElement = newSubBE;
            DBINF << "BTree::pars [3.3]"  << endl;

            lastBracketsIndex = i;
        } else if ( BTree::completeDocText.at(i) == '['){
            DBINF << "BTree::pars [4]"  << endl;
            openSquareBrackets++;
            
            // new parent BTreeElement
            DBINF << "BTree::pars [4.1.1]"  << endl;
            BTreeElement* newParentBE = new BTreeElement();
            DBINF << "BTree::pars [4.1.2]"  << endl;
            BTree::elementList.push_back( newParentBE );
            DBINF << "BTree::pars [4.1.3]"  << endl;
            newParentBE->setType( BTreeElement::SQAREBRACKET );
            DBINF << "BTree::pars [4.1.5]"  << endl;
            newParentBE->setParentElement( BTree::lastParentElement );
            DBINF << "BTree::pars [4.1.6]"  << endl;
            BTree::lastParentElement->addSubElement( newParentBE );
            DBINF << "BTree::pars [4.1.7]"  << endl;
            BTree::lastParentElement->setNextSubElement( newParentBE );
            DBINF << "BTree::pars [4.1.8]"  << endl;
            newParentBE->setPreSubElement( BTree::lastParentElement );
            DBINF << "BTree::pars [4.1.9]"  << endl;
            BTree::lastParentElement = newParentBE;
            DBINF << "BTree::pars [4.1.10]"  << endl;
            BTree::lastSubElement = 0;
            DBINF << "BTree::pars [4.2]"  << endl;
            
            // new sub element.
            BTreeElement* newSubBE = new BTreeElement();
            BTree::elementList.push_back( newSubBE );
            newSubBE->setType( BTreeElement::RAW );
            newSubBE->setValue( "" );
            newSubBE->setParentElement( BTree::lastParentElement );
            newSubBE->setPreSubElement( BTree::lastSubElement );
            if ( BTree::lastSubElement != 0 ) {
            	BTree::lastSubElement->setNextSubElement( newSubBE );
            }
            BTree::lastSubElement = newSubBE;
            DBINF << "BTree::pars [4.3]"  << endl;

            lastBracketsIndex = i;
        } else if ( BTree::completeDocText.at(i) == ']'){
            DBINF << "BTree::pars [5]"  << endl;
            openSquareBrackets--;

            lastBracketsIndex = i;
        } else if ( BTree::completeDocText.at(i) == '}'){
            DBINF << "BTree::pars [6]"  << endl;
            openCurlyBrackets--;

            lastBracketsIndex = i;
        } else {
//        	DBINF <<  "BTree::completeDocText.at(i): " << BTree::completeDocText.at(i) << endl;
        	// if first element not exist....
        	if ( BTree::lastSubElement == 0 ) {
                BTreeElement* newSubBE = new BTreeElement();
                BTree::elementList.push_back( newSubBE );
                newSubBE->setType( BTreeElement::RAW );
                newSubBE->setValue( "" );
                newSubBE->setParentElement( BTree::lastParentElement );
                newSubBE->setPreSubElement( BTree::lastSubElement );
                BTree::lastSubElement = newSubBE;
        	}
        	//            DBINF << "BTree::pars [7]"  << endl;
        	string newValue = BTree::lastSubElement->getValue();
        	//             DBINF << "BTree::pars [7.1]"  << endl;
		    newValue += BTree::completeDocText.at(i);
		    //            DBINF << "BTree::pars [7.2]"  << endl;
        	BTree::lastSubElement->setValue( newValue );
        	//             DBINF << "BTree::pars [7.3]"  << endl;
        }

    }

    DBINF << "...BTree::pars Ende. Anzahl Elemente: " << BTree::elementList.size()  << endl;
    return;
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
