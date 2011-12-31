#ifndef TREEGARBAGECOLLECTOR_H
#define TREEGARBAGECOLLECTOR_H


#include <string>
#include <list>

#include "TexDocElement.h"

using namespace std;

/**
 * @class TreeGarbageCollector TreeGarbageCollector.h "TreeGarbageCollector.h"
 * class remove garbage in element tree.
 */
class TreeGarbageCollector {
  public:


      /*
      * constructor.
      */
//      TreeGarbageCollector(): treedepth( 0 ), verboseMode(false) {};
      
      /**
      * start the work.
      * @param parentElement a parent element.
      */
      void start( TexDocElement& parentElement );

      
  private:
      size_t  treedepth;
      string recordingValue;
      
      /**
      * Print one element and walking down in the tree continue.
      * @param parentElement a parent element.
      */      
      void recursiveWalk( TexDocElement& parentElement );
};

#endif   