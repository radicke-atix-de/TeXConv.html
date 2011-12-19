
#include <fstream>
#include <list>
#include <string>
#include <boost/regex.hpp>

#include "InputParser.h"
#include "CutOut.h"
#include "../TexDocElement.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;
using namespace Pars;


string InputParser::findAndRemoveComments(const string &read_line){
    return InputParser::findAndRemoveCommentsSTD(read_line);
}

string InputParser::findAndRemoveCommentsBoost(const string &read_line){
    // More detais to boost::regex see: 
    // http://www.boost.org/doc/libs/1_47_0/libs/regex/doc/html/boost_regex/syntax/basic_syntax.html
    // It is in use a case sensitive POSIX-Basic expression. The POSIX-Basic 
    // regular expression syntax is used by the Unix utility sed, and 
    // variations are used by grep and emacs. 

    boost::regex pattern (
        "(^\\(.*\\)[^\\\\]*%.*$)|(/^\\(.*\\)[^\\\\]*%.*$)",
        boost::regex::basic
    );
    string replace ("");
    return boost::regex_replace (read_line, pattern, replace);
}    


string InputParser::findAndRemoveCommentsSTD(const string &read_line) {
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


void InputParser::parsInput(TexDocElement&  parentElement) {
    list<TexDocElement>::iterator subElement;
    
    if( parentElement.getType() == TexDocElement::VERBATIM
        || parentElement.getType() == TexDocElement::VERB
    ) { 
        return;
    }else{
        if( parentElement.getType() == TexDocElement::INPUT ) {         
            string fileName = parentElement.getValue();
            parentElement.setValue ( InputParser::readInputFile(fileName) );
            parentElement.setType( TexDocElement::RAW );
        }else {
            if ( parentElement.subElementList.size() == 0 ) {
                CutOut::shortElements( parentElement, 
                    string("input"),
                    TexDocElement::INPUT );
            } 
            for ( subElement = parentElement.subElementList.begin();
                subElement != parentElement.subElementList.end();
                subElement++
            ) {
                InputParser::parsInput( *subElement );
            } // end for-loop
        }
    }
}

string InputParser::readInputFile(string& fileName){
    string completString = "";
    // open fiele to read....
    ifstream tex_file(fileName.c_str());
    if (tex_file.is_open()) {
        while ( tex_file.good() ) {
            string line;
            getline (tex_file,line);
            completString.append( InputParser::findAndRemoveComments(line) );
            completString.append("\n");
        }
    }else{
        cerr << "[201111062048] couldn't open \"" << fileName \
            << "\" for reading\n" << endl;
        throw;
    }
    tex_file.close();
    return completString;
}
