#ifndef IGRAPHLOADER_H_
#define IGRAPHLOADER_H_

#include "Graph.h"

class IGraphLoader
{
public:
    virtual void getGraph(Graph<int>**) = 0;
    ~IGraphLoader()
    {
    }
};


#endif
