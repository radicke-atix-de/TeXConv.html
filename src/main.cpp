// Creating error-no: date +"%Y%m%d%H%M"

#include "TexParser.h"
#include <string>
#include <iostream>

#include "PrintElementTree.h"
#include "TexParser.h"

/** get debugging info */
#define DBINF  cout << "[debug]"

using namespace std;

void get_help(void)
{
    cout << "\ntexconv [pars|doctree|--help] --output=[file name] " << endl;
    cout << "\n--help" << endl;
    cout << "\t\t Help text." << endl;
    cout << "\n--input=[file name]" << endl;
    cout << "\t\t Name of input file." << endl;
    cout << "\n--output=[file name]" << endl;
    cout << "\t\t Name of output file." << endl;


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


    for ( int i = 1; i < argc; i++)
    {
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
        if (found!=std::string::npos)
        {
            size_t endIdentifier = std::string("--input=").length();
            imputFileName = str_arg.substr( endIdentifier );
        }
        found = str_arg.find("--output=");
        if (found!=std::string::npos)
        {
            size_t endIdentifier = std::string("--output=").length();
            outputFileName = str_arg.substr( endIdentifier );
        }
    } // end for-loop
    
    if( do_command == "")
    {
        cout << "No supported command found!" << endl;
        return 1;
    }
    


    if( imputFileName == "" )
    {
        cout << "Name of input file is not set!" << endl;
        return 1;
    }
    if( do_command == "doctree")
    {
        TexParser texParser;
        texParser.setInputFileName(imputFileName);
        texParser.pars();
        PrintElementTree::printTree( texParser.getRootElement() );
        return 0;
    }
    if( do_command == "pars")
    {    
        if( outputFileName == "" )
        {
            cout << "Name of output file is not set!" << endl;
            return 1;
        }
DBINF << "convert " << imputFileName << " to " << outputFileName << endl;
        TexParser texParser;
        texParser.setInputFileName(imputFileName);
        texParser.pars();
        return 0;
    }
}




