
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
		m_completeDocText(""),
		m_lastSubElement(0)
{
    m_rootElement = new BTreeElement();
    m_rootElement->setType( BTreeElement::ROOTELEMENT );
    m_elementList.push_back( m_rootElement );
	m_lastParentElement = m_rootElement;
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
	return m_completeDocText;
}

BTreeElement* BTree::getRootElement(void){
	return m_rootElement;
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
//    unsigned int lastBracketsIndex = 0;

    if ( m_lastParentElement == 0) {
        m_lastParentElement = m_rootElement;

    }
    DBINF << "BTree::pars [2]"  << endl;

    m_completeDocText = BTree::readInputFile( 
        m_inputFileName
    );
    for ( unsigned int i = 0; i < m_completeDocText.size(); i++) {
        if ( m_completeDocText.at(i) == '{'){
            DBINF << "BTree::pars [3.1]"  << endl;
            openCurlyBrackets++;
            
            // find a command name
            DBINF << "m_lastSubElement->getValue()"  << endl;
            DBINF << m_lastSubElement->getValue() << endl ;
            string lastTextPart = m_lastSubElement->getValue();
            size_t indexCommandBegin = lastTextPart.find_last_of("\\");
            if( indexCommandBegin != string::npos ) {
                if( lastTextPart[(indexCommandBegin -1)] != '\\') {
                    string commandName = lastTextPart.substr( 
                    		indexCommandBegin,
                    		(lastTextPart.size() - indexCommandBegin)
						);
                    DBINF << "commandName: " << commandName << endl ;
                } 
            }
            
            // new parent BTreeElement
            BTreeElement* newParentBE = new BTreeElement();
            m_elementList.push_back( newParentBE );
            newParentBE->setType( BTreeElement::CURLYBRACKET );
            newParentBE->setParentElement( m_lastParentElement );
            m_lastParentElement->addSubElement( newParentBE );
            m_lastParentElement->setNextSubElement( newParentBE );
            newParentBE->setPreSubElement( m_lastParentElement );
            m_lastParentElement = newParentBE;
            m_lastSubElement = 0;
            
            // new sub element.
            BTreeElement* newSubBE = new BTreeElement();
            m_elementList.push_back( newSubBE );
            newSubBE->setType( BTreeElement::RAW );
            newSubBE->setValue( "" );
            newSubBE->setParentElement( m_lastParentElement );
            newSubBE->setPreSubElement( m_lastSubElement );
            if ( m_lastSubElement != 0 ) {
            	m_lastSubElement->setNextSubElement( newSubBE );
            }
            m_lastSubElement = newSubBE;

        } else if ( m_completeDocText.at(i) == '['){
            DBINF << "BTree::pars [4]"  << endl;
            openSquareBrackets++;
          
            // find a command name
            DBINF << "m_lastSubElement->getValue()"  << endl;
            DBINF << m_lastSubElement->getValue() << endl ;
            string lastTextPart = m_lastSubElement->getValue();
            size_t indexCommandBegin = lastTextPart.find_last_of("\\");
            if( indexCommandBegin != string::npos ) {
                if( lastTextPart[(indexCommandBegin -1)] != '\\') {
                    string commandName = lastTextPart.substr( 
                    		indexCommandBegin,
                    		(lastTextPart.size() - indexCommandBegin)
						);
                    DBINF << "commandName: " << commandName << endl ;
                } 
            }            
            
            // new parent BTreeElement
            BTreeElement* newParentBE = new BTreeElement();
            m_elementList.push_back( newParentBE );
            newParentBE->setType( BTreeElement::SQAREBRACKET );
            newParentBE->setParentElement( m_lastParentElement );
            m_lastParentElement->addSubElement( newParentBE );
            m_lastParentElement->setNextSubElement( newParentBE );
            newParentBE->setPreSubElement( m_lastParentElement );
            m_lastParentElement = newParentBE;
            m_lastSubElement = 0;
            
            // new sub element.
            BTreeElement* newSubBE = new BTreeElement();
            m_elementList.push_back( newSubBE );
            newSubBE->setType( BTreeElement::RAW );
            newSubBE->setValue( "" );
            newSubBE->setParentElement( m_lastParentElement );
            newSubBE->setPreSubElement( m_lastSubElement );
            if ( m_lastSubElement != 0 ) {
            	m_lastSubElement->setNextSubElement( newSubBE );
            }
            m_lastSubElement = newSubBE;
            DBINF << "BTree::pars [4.3]"  << endl;

        } else if ( m_completeDocText.at(i) == ']'){
            DBINF << "BTree::pars [5]"  << endl;
            openSquareBrackets--;
            m_lastSubElement = m_lastParentElement ;
            m_lastParentElement = m_lastParentElement->getParentElement();

        } else if ( m_completeDocText.at(i) == '}'){
            DBINF << "BTree::pars [6]"  << endl;
            openCurlyBrackets--;
            m_lastSubElement = m_lastParentElement ;
            m_lastParentElement = m_lastParentElement->getParentElement();

        } else {
//        	DBINF <<  "BTree::completeDocText.at(i): " << BTree::completeDocText.at(i) << endl;
        	// if first element not exist....
        	if ( m_lastSubElement == 0 ) {
                BTreeElement* newSubBE = new BTreeElement();
                m_elementList.push_back( newSubBE );
                newSubBE->setType( BTreeElement::RAW );
                newSubBE->setValue( "" );
                newSubBE->setParentElement( m_lastParentElement );
                newSubBE->setPreSubElement( m_lastSubElement );
                m_lastSubElement = newSubBE;
        	}
        	//            DBINF << "BTree::pars [7]"  << endl;
        	string newValue = m_lastSubElement->getValue();
        	//             DBINF << "BTree::pars [7.1]"  << endl;
		    newValue += m_completeDocText.at(i);
		    //            DBINF << "BTree::pars [7.2]"  << endl;
        	m_lastSubElement->setValue( newValue );
        	//             DBINF << "BTree::pars [7.3]"  << endl;
        }

    }

    DBINF << "...BTree::pars Ende. Anzahl Elemente: " << m_elementList.size()  << endl;
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
    m_inputFileName = fileName;
}

// T #########################################################################

} //end namespace
