#ifndef BTREEPRINT_H
#define BTREEPRINT_H


#include <string>
#include <list>

#include "BTreePrint.h"
#include "BTreeElement.h"

using namespace std;

namespace BTreePars {

class BTreePrint{
  public:


      /**
      * constructor.
      */
	 BTreePrint(): treedepth( 0 ), verboseMode(false) {};
      
      /**
      * Print the document tree.
      * @param parentElement a parent element.
      */
      void printTree( BTreeElement* parentElement );
      
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
      void printTreeElement( BTreeElement* parentElement );
};

} // end namespace BTreePars

#endif   
