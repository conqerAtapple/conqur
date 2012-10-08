#include <istream>
#include <fstream>


#include "FileGraphLoader.h"
#include "Graph.h"

using namespace std;

/*
void FileGraphLoader::parseLine(const string& line, Graph<int> **out)
{
    const char* pch = line.c_str();
    char tmp[100];
    int i = 0;

    *out = new Graph<int>();
    while(*pch)
    {
        i=0;
        while((*pch) && (*pch != ':' ))
        {
            debug ("*pch :") << *pch;
            if(*pch >= '0' && *pch <= '9')
            {
                tmp[i++] = *pch;
            }
            pch++;
        }
        if(! (*pch))
            break;

        tmp[i] = 0;       
       // struct vertice<int> *pVertex = new  vertice<int>();
       // pVertex->value = atoi(tmp);
       // vertice<int>::EdgeListHead *pEdgeHead = new  vertice<int>::EdgeListHead() ;


        //(*out)->addVertex(pVertex, pEdgeHead);

       // debug("vertice id:") << verticeId;
        pch++;
    }
}
*/
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
    }
 }



