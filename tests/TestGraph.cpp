
#include "Graph.h"
#include "GraphFactory.h"
#include "FileGraphLoader.h"
#include "TestGraph.h"

using namespace std;

void testFileGraphLoader(const string& fName)
{
    FileGraphLoader fgLoader(fName);
    Graph<int> *graph;
    fgLoader.getGraph(&graph);

}
