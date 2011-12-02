#ifndef PRINTELEMETTREE_H
#define PRINTELEMETTREE_H


#include <string>
#include <list>

#include "TexDocElement.h"

using namespace std;

class PrintElementTree{
  public:


      /**
      * constructor.
      */
      PrintElementTree(): treedepth( 0 ), verboseMode(false) {};
      
      /**
      * Print the document tree.
      * @param parentElement a parent element.
      */
      void printTree( TexDocElement& parentElement );
      
      /**
      * Set verbose mode.
      * @param mode it is "true" then it's more infomations.
      */      
      void setVerbose ( bool mode );
      
  private:
      size_t  treedepth;
      bool verboseMode;
      string recordingValue;
      
      /**
      * Print one element and walking down in the tree continue.
      * @param parentElement a parent element.
      */      
      void printTreeElement( TexDocElement& parentElement );
};

#endif   