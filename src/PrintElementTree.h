#ifndef PRINTELEMETTREE_H
#define PRINTELEMETTREE_H


#include <string>
#include <list>

#include "TexDocElement.h"

class PrintElementTree
{
public:
    static void printTree( TexDocElement& parentElement );
};

#endif   