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

    void parseEdges(const char** txt, Graph<int> *g, int v)
    {
        const char* pch = *txt;
        int i = 0;
        char tmp[100];
        while(*pch)
        {
            i=0;
            while((*pch) && (*pch != ',' ))
            {
                //debug ("*pch :") << *pch;
                if(*pch >= '0' && *pch <= '9')
                {
                    tmp[i++] = *pch;
                }
                pch++;
            }
            tmp[i] = 0; 
            //debug("tmp:") << tmp;
            vertice<int>::Edge_t edge;
            g->addEdge(v, edge, atoi(tmp));
            
            if(*pch)
                pch++;
         }
        *txt = pch;
    }

    void parseLine(const std::string& line, Graph<int> **out)
    {
        const char* pch = line.c_str();
        char tmp[100];
        int i = 0;
       
        while(*pch)
        {
            i=0;
            while((*pch) && (*pch != ':' ))
            {
                //debug ("*pch :") << *pch;
                if(*pch >= '0' && *pch <= '9')
                {
                    tmp[i++] = *pch;
                }
                pch++;
            }
           
            tmp[i] = 0;     
            //debug("tmp :") << tmp;

            vertice<int> *pVertex = new vertice<int>();
            pVertex->value = atoi(tmp);
            parseEdges(&pch, *out, pVertex->value);
            
            (*out)->addVertex(pVertex);

            if(*pch)
            {                
                pch++;
            }
        }
    }

};

#endif
