// Creating error-no: date +"%Y%m%d%H%M"

#include <string>
#include <iostream>

//#include "PrintElementTree.h"
#include "pars/TexParser.h"
#include "BTreePars/BTree.h"
#include "BTreePars/BTreePrint.h"
#include "BTreePars/PrintBTree.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;

void get_help(void)
{
    cout << "\ntexconv [pars|doctree|--help] --output=[file name] " << endl;;
    cout << "\ndoctree" << endl;
    cout << "\t\t pars a TeX document and print a tree view." << endl;
    cout << "\npars" << endl;
    cout << "\t\t pars a TeX document." << endl;
    cout << "\n--help" << endl;
    cout << "\t\t Help text." << endl;
    cout << "\n--input=[file name]" << endl;
    cout << "\t\t Name of input file." << endl;
    cout << "\n--output=[file name]" << endl;
    cout << "\t\t Name of output file." << endl;
    cout << "\n-v" << endl;
    cout << "\t\t verbose mode. explain what is being done." << endl;


}

int main(int argc,char *argv[])
{
    std::string str_arg;
    size_t found;
    std::string imputFileName;
    imputFileName="";
    std::string outputFileName;
    outputFileName="";
    string do_command = "";
    bool verbose = false;

    for ( int i = 1; i < argc; i++) {
        str_arg = std::string(argv[i]);
// DBINF << "Arg Nr.: " << i << " Wert: " << argv[i] << endl;
        if(i == 1)
        {
            if (str_arg == "--help")
            {
                get_help();
                return 0;
            }
            if (str_arg == "pars")
            {
                do_command = str_arg;
            }
            if (str_arg == "doctree")
            {
                do_command = str_arg;
            }

        }
        found = str_arg.find("--input=");
        if (found!=std::string::npos)  {
            size_t endIdentifier = std::string("--input=").length();
            imputFileName = str_arg.substr( endIdentifier );
        }
        found = str_arg.find("--output=");
        if (found!=std::string::npos) {
            size_t endIdentifier = std::string("--output=").length();
            outputFileName = str_arg.substr( endIdentifier );
        }
        found = str_arg.find("-v");
        if (found!=std::string::npos)  {
            verbose = true;
        }        
    } // end for-loop
    
    if( do_command == "")  {
        cout << "No supported command found!" << endl;
        return 1;
    }
    
    if( imputFileName == "" ) {
        cout << "Name of input file is not set!" << endl;
        return 1;
    }
    if( do_command == "doctree")  {

        BTreePars::BTree btree;
        btree.setInputFileName(imputFileName);
        btree.pars();
DBINF << "btree.getCompleteDocText(): " << btree.getCompleteDocText() << endl;

		
		BTreePars::PrintBTree treePrinter;
DBINF << "verbose" << verbose << endl;
        treePrinter.setVerbose ( verbose );
		treePrinter.printTree( btree.getRootElement() );
        return 0;
    }
    if( do_command == "pars")  {
        if( outputFileName == "" ) {
            cout << "Name of output file is not set!" << endl;
            return 1;
        }
DBINF << "convert " << imputFileName << " to " << outputFileName << endl;
//         Pars::TexParser texParser;
//         texParser.setInputFileName(imputFileName);
//         texParser.pars();
        
        BTreePars::BTree btree;
        btree.setInputFileName(imputFileName);
        btree.pars();
        return 0;
    }
}




