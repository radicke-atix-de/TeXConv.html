#ifndef TEXTOHTML_H
#define TEXTOHTML_H

#include <string>

class TexToHtml
{
public:
    TexToHtml(void);    
    ~TexToHtml(void);
    void start(void);
    void setInputFileName(std::string);
    void setOutputFileName(std::string);
    
private: 
    std::string inputFileName;
    std::string outputFileName;
    std::string tmpFileName;
    void newcommandLexer(void);
    void htmlLexer(void);
    void openTexFile(void);
    void openTmpTexFile(void);
    void openHtmlFile(void);
  
};

#endif 