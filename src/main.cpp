// Creating error-no: date +"%Y%m%d%H%M"

#include "TexParser.h"
#include <string>
#include <iostream>
#include "TexParser.h"

/** get debugging info */
#define DBINF  std::cout << "[debug]"

void get_help(void)
{
    std::cout << "\n--help" << std::endl;
    std::cout << "\t\t Help text." << std::endl;
    std::cout << "\n--input=[file name]" << std::endl;
    std::cout << "\t\t Name of input file." << std::endl;
    std::cout << "\n--output=[file name]" << std::endl;
    std::cout << "\t\t Name of output file." << std::endl;


}

int main(int argc,char *argv[])
{
    std::string str_arg;
    size_t found;
    std::string imputFileName;
    imputFileName="";
    std::string outputFileName;
    outputFileName="";


    for ( int i = 1; i < argc; i++)
    {
//         std::cout << argv[i] << std::endl;
        str_arg = std::string(argv[i]);
        found = str_arg.find("--help");
        if (found!=std::string::npos)
        {
            get_help();
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


    }

    if( imputFileName == "" )
    {
        std::cout << "Name of input file is not set!" << std::endl;
        return 1;
    }
    if( outputFileName == "" )
    {
        std::cout << "Name of output file is not set!" << std::endl;
        return 1;
    }
DBINF << "convert " << imputFileName << " to " << outputFileName << std::endl;
    TexParser texParser;
    texParser.setInputFileName(imputFileName);
    texParser.pars();
    
    return 0;
}




