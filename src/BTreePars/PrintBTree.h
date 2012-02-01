#ifndef PRINTELEMETTREE_H
#define PRINTELEMETTREE_H


#include <string>
#include <list>

#include "BTreeElement.h"

using namespace std;
namespace BTreePars {

class PrintBTree{
  public:


      /**
      * constructor.
      */
	  PrintBTree(): treedepth( 0 ), verboseMode(false) {};
      
      /**
      * Print the document tree.
      * @param parentElement a parent element.
      */
      void printTree( BTreeElement*  parentElement );
      
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
      void printTreeElement( BTreeElement*  parentElement );
};

}// end namespace 

#endif   