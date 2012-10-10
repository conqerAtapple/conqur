#include <istream>
#include <fstream>


#include "FileGraphLoader.h"
#include "Graph.h"

using namespace std;

void FileGraphLoader::getGraph(Graph<int> **out)
 {
    ifstream gFile (fileName.c_str());
    string line;

    if(gFile.is_open())
    {
        *out = new Graph<int>();
        while(gFile.good())
        {
            getline (gFile,line);
            debug("graph line:") << line;
            parseLine(line, out);
           
        }
        gFile.close();

        
        debug("Done reading!") ;
        std::cout << **out;
    }
 }



