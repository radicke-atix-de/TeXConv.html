#ifndef PRINTELEMETTREE_H
#define PRINTELEMETTREE_H


#include <string>
#include <list>

#include "TexDocElement.h"

using namespace std;

class PrintElementTree
{
  public:

      /**
      * Print the document tree.
      * @param parentElement a parent element.
      */
      void printTree( TexDocElement& parentElement );

      /**
      * constructor.
      */
      PrintElementTree(): treedepth( 0 ) {};
      
  private:
      size_t  treedepth;
};

#endif   