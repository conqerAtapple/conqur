#ifndef FILEGRAPHLOADER_H
#define FILEGRAPHLOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "IGraphLoader.h"
#include "Graph.h"


class FileGraphLoader:public IGraphLoader
{
public:
    FileGraphLoader(const std::string& file):
    fileName(file)
    {
    }

    void getGraph(Graph<int> **out);

private:
    std::string fileName;

    void parseLine(const std::string& line, Graph<int> **out)
    {
        const char* pch = line.c_str();
        char tmp[100];
        int i = 0;

       // Graph<int> *pOut = new Graph<int>();
        
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
            vertice<int> *pVertex = new  vertice<int>();
            pVertex->value = atoi(tmp);
            vertice<int>::EdgeList_t *pEdgeHead = new  vertice<int>::EdgeList_t();


            (*out)->addVertex(pVertex, pEdgeHead);

            // debug("vertice id:") << verticeId;
            pch++;
        }
    }

};

/*
template<>
void FileGraphLoader::parseLine(const std::string& line, Graph<int> **out)
{
    const char* pch = line.c_str();
    char tmp[100];
    int i = 0;

    Graph<int> *pOut = new Graph<int>();
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
#endif
