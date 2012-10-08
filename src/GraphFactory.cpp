#include <string>
#include "FileGraphLoader.h"
#include "GraphFactory.h"

GraphFactory* GraphFactory::instance = NULL;

using namespace std;

//TODO: add support for multithread
GraphFactory* GraphFactory::getInstance()
{
    if(instance == NULL)
    {
        instance = new GraphFactory();
    }

    return instance;
}

GraphFactory::GraphFactory()
{
    
}

void GraphFactory::getGraphFromFile(const string& file, Graph<int>** outGraph)
{
    FileGraphLoader  fGileLoader(file);
    fGileLoader.getGraph(outGraph);
}
