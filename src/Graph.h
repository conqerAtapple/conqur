#ifndef GRAPH_H_
#define GRAPH_H_

#include <assert.h>
#include "LinkedList.h"


template <typename T>
class vertice;

template <typename T>
class edge
{
    struct vertice<T> *vertex;
};

template <typename T>
class vertice
{
public:

    typedef T value_type;
    typedef edge<T> Edge_t;
    typedef LinkedList<struct edge<T> > EdgeList_t;

    bool operator==(const vertice<T>& rhs)
    {
        return this->value == rhs.value;
    }

    bool operator <(const vertice<T>& rhs)
    {
        return this->value < rhs.value;
    }

    friend std::ostream& operator<<(std::ostream& out, const vertice& v)
    {
        out << "{";
        out << v.value;
        out << "}";
    }

    value_type value;
    EdgeList_t edgeHead;
};

template <typename T>
class Graph
{
public:
    typedef T value_type;
    typedef  vertice<T> VerticeType;
    typedef typename VerticeType::EdgeList_t VerticeEdgeType;

    Graph()
    {
    }

    bool addVertex(VerticeType* v, VerticeEdgeType *edgeList)
    {
        assert(v);
        assert(edgeHead);

        ListNode<VerticeType*> *insertNode = NULL;
        verticeList.insertSortedUnique(v, &insertNode);

        if(insertNode != NULL)
        {
            debug("found existing vertice") << *(insertNode->value);
            addEdgesToVertice(insertNode, edgeList);
        }
        else
        {
             addEdgesToVertice(v, edgeList);
        }

        std::cout << verticeList;
        return true;
    }

private:
    LinkedList<VerticeType*>  verticeList;

    //
    // Methods
    // //////
    
    void addEdgesToVertice(VerticeType *v, VerticeEdgeType *edgeHead)
    {



    }

};


#endif
