
#include <iostream>
#include <string>
//#include <boost/regex.hpp>
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
    // counter for open [
    unsigned int openSquareBrackets = 0;
    // counter for open {
    unsigned int openCurlyBrackets = 0;
    // counter for open {
//    unsigned int lastBracketsIndex = 0;
    enum BTreeElement::ElementType elementType = BTreeElement::VOID;
    string newValue = "";
    
    if ( m_lastParentElement == 0) {
        m_lastParentElement = m_rootElement;

    }

    m_completeDocText = BTree::readInputFile( 
        m_inputFileName
    );
    for ( unsigned int i = 0; i < m_completeDocText.size(); i++) {
        if ( m_completeDocText.at(i) == '{'){
            openCurlyBrackets++;
            
            // find a command name
            string lastTextPart = m_lastSubElement->getValue();
            size_t indexCommandBegin = lastTextPart.find_last_of("\\");
            if( indexCommandBegin != string::npos ) {
                // no masked '\\'
                if( lastTextPart[(indexCommandBegin -1)] != '\\') {
                    string commandName = lastTextPart.substr( 
                        indexCommandBegin,
                        (lastTextPart.size() - indexCommandBegin)
                    );
                    DBINF << "commandName: " << commandName << endl ;
                    elementType = BTreeElement::stringToType( commandName );
                    DBINF << "ElementType:" << BTreeElement::typeToString( elementType ) << endl ;
                    // new parent BTreeElement for located command
                    BTreeElement* newCommandBE = new BTreeElement();
                    m_elementList.push_back( newCommandBE );
                    newCommandBE->setType( elementType );
                    if( m_lastParentElement != 0 ){
                    	newCommandBE->setParentElement( m_lastParentElement );
                    }
                    if( m_lastParentElement != 0 ){
                    	m_lastParentElement->addSubElement( newCommandBE );
                    }
                    if ( m_lastSubElement != 0 ) {
                    	m_lastSubElement->setNextSubElement( newCommandBE );
                    }
                    if ( m_lastSubElement == 0 ){
                    	newCommandBE->setPreSubElement( 0 );
                    } else {
                    	newCommandBE->setPreSubElement( m_lastParentElement );
                    }
                    m_lastSubElement = newCommandBE;
                } 
            }
            // new parent BTreeElement
            BTreeElement* newSubBE = new BTreeElement();
            m_elementList.push_back( newSubBE );
            newSubBE->setType( BTreeElement::CURLYBRACKET );
            newSubBE->setParentElement( m_lastSubElement );
            m_lastSubElement->addSubElement( newSubBE );
            newSubBE->setPreSubElement( 0 );
            m_lastParentElement = m_lastSubElement;
            m_lastSubElement = newSubBE;
            
            // new parent BTreeElement
            BTreeElement* newTextBE = new BTreeElement();
            m_elementList.push_back( newTextBE );
            newTextBE->setType( BTreeElement::TEXT );
            newTextBE->setParentElement( m_lastSubElement );
            m_lastSubElement->addSubElement( newTextBE );
            newTextBE->setPreSubElement( 0 );
            m_lastParentElement = m_lastSubElement;
            m_lastSubElement = newTextBE;

        } else if ( m_completeDocText.at(i) == '['){
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
                    elementType = BTreeElement::stringToType( commandName );
                    DBINF << "ElementType:" << BTreeElement::typeToString( elementType ) << endl ;
                    BTreeElement* newCommandBE = new BTreeElement();
                    m_elementList.push_back( newCommandBE );
                    newCommandBE->setType( elementType );
                    if( m_lastParentElement != 0 ){
                    	newCommandBE->setParentElement( m_lastParentElement );
                    }
                    if( m_lastParentElement == 0 ){
                    	DBINF << "m_lastParentElement == 0" << endl;
                    }
                    if( newCommandBE == 0 ){
                    	DBINF << "newCommandBE == 0" << endl;
                    }
                    m_lastParentElement->addSubElement( newCommandBE );
                    if ( m_lastSubElement != 0 ) {
                    	m_lastSubElement->setNextSubElement( newCommandBE );
                    }
                    newCommandBE->setPreSubElement( m_lastSubElement );
                    m_lastSubElement = newCommandBE;          
                } 
            }           
            BTreeElement* newSubBE = new BTreeElement();
            m_elementList.push_back( newSubBE );
            newSubBE->setType( BTreeElement::SQAREBRACKET );
            newSubBE->setParentElement( m_lastSubElement );
            m_lastSubElement->addSubElement( newSubBE );
//             m_lastParentElement->setNextSubElement( newSubBE );
            newSubBE->setPreSubElement( 0 );
            m_lastParentElement = m_lastSubElement;
            m_lastSubElement = newSubBE; 


        } else if ( m_completeDocText.at(i) == ']'){
            openSquareBrackets--;
            if ( m_lastSubElement != 0 ) {
            	if ( m_lastSubElement->getParentElement() != 0 ) {
                        m_lastSubElement = m_lastSubElement->getParentElement() ;
            	}
            } else {
                // pass
            }
            if ( m_lastSubElement->getParentElement() != 0 ) {
            	if ( m_lastSubElement->getParentElement()->getParentElement() != 0 ) {
                        m_lastParentElement = 
                                m_lastSubElement->getParentElement()->getParentElement();
            	} else {
            	}
            }
            // one step more up ...
            if ( m_lastSubElement != 0 ) {
                    if ( m_lastSubElement->getParentElement() != 0 ) {
                            m_lastSubElement = m_lastSubElement->getParentElement() ;
                    }
            } else {
                    //pass
            }
            if ( m_lastSubElement->getParentElement() != 0 ) {
                    if ( m_lastSubElement->getParentElement()->getParentElement() != 0 ) {
                            m_lastParentElement = m_lastSubElement->getParentElement()->getParentElement();
                    } else {
                    //pass
                    }
            }
            // one step more up ...
            if ( m_lastSubElement != 0 ) {
                    if ( m_lastSubElement->getParentElement() != 0 ) {
                            m_lastSubElement = m_lastSubElement->getParentElement() ;
                    }
            } else {
                    //pass
            }
            if ( m_lastSubElement->getParentElement() != 0 ) {
                    if ( m_lastSubElement->getParentElement()->getParentElement() != 0 ) {
                            m_lastParentElement = m_lastSubElement->getParentElement()->getParentElement();
                    } else {
                    //pass
                    }
            }
            

            // new parent BTreeElement
            BTreeElement* newTextBE = new BTreeElement();
            m_elementList.push_back( newTextBE );
            newTextBE->setType( BTreeElement::TEXT );
            newTextBE->setParentElement( m_lastSubElement );
            m_lastSubElement->addSubElement( newTextBE );
            newTextBE->setPreSubElement( 0 );
            m_lastParentElement = m_lastSubElement;
            m_lastSubElement = newTextBE;
            
        } else if ( m_completeDocText.at(i) == '}'){
            DBINF << m_lastSubElement->getValue() << endl;
            openCurlyBrackets--;
            if ( m_lastSubElement != 0 ) {
            	if ( m_lastSubElement->getParentElement() != 0 ) {
                	m_lastSubElement = m_lastSubElement->getParentElement() ;
            	}
            } else {
                //pass
            }
            if ( m_lastSubElement->getParentElement() != 0 ) {
            	if ( m_lastSubElement->getParentElement()->getParentElement() != 0 ) {
            		m_lastParentElement = m_lastSubElement->getParentElement()->getParentElement();
            	} else {
                    //pass
            	}
            }
            // one step more up ...
            if ( m_lastSubElement != 0 ) {
                    if ( m_lastSubElement->getParentElement() != 0 ) {
                            m_lastSubElement = m_lastSubElement->getParentElement() ;
                    }
            } else {
                    //pass
            }
            if ( m_lastSubElement->getParentElement() != 0 ) {
                    if ( m_lastSubElement->getParentElement()->getParentElement() != 0 ) {
                            m_lastParentElement = m_lastSubElement->getParentElement()->getParentElement();
                    } else {
                    //pass
                    }
            }
            // one step more up ...
            if ( m_lastSubElement != 0 ) {
                    if ( m_lastSubElement->getParentElement() != 0 ) {
                            m_lastSubElement = m_lastSubElement->getParentElement() ;
                    }
            } else {
                    //pass
            }
            if ( m_lastSubElement->getParentElement() != 0 ) {
                    if ( m_lastSubElement->getParentElement()->getParentElement() != 0 ) {
                            m_lastParentElement = m_lastSubElement->getParentElement()->getParentElement();
                    } else {
                    //pass
                    }
            }
 
            // new parent BTreeElement
            BTreeElement* newTextBE = new BTreeElement();
            m_elementList.push_back( newTextBE );
            newTextBE->setType( BTreeElement::TEXT );
            newTextBE->setParentElement( m_lastSubElement );
            m_lastSubElement->addSubElement( newTextBE );
            newTextBE->setPreSubElement( 0 );
            m_lastParentElement = m_lastSubElement;
            m_lastSubElement = newTextBE;
            
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
            newValue = m_lastSubElement->getValue();
            newValue += m_completeDocText.at(i);
            m_lastSubElement->setValue( newValue );
            
        }
        // DBINF << "BTree::pars [7]"  << endl;

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
