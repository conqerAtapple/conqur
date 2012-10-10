#ifndef GRAPH_H_
#define GRAPH_H_

#include <assert.h>
#include "LinkedList.h"


template <typename T>
class vertice;

template <typename T>
class edge
{
public:
    struct vertice<T> *vertex;

    bool operator==(const edge<T>& rhs)
    {
        return(this->vertex->value == rhs.vertex->value);
    }

    bool operator <(const edge<T>& rhs)
    {
        return this->vertex->value < rhs.vertex->value;
    }

    friend std::ostream& operator<<(std::ostream& out, const edge& v)
    {
        out << "{";
        out << v.vertex->value;
        out << "}";
    }

    ~edge()
    {
        debug("deleting edge :") << vertex->value;
    }
};

template <typename T>
class vertice
{
public:

    typedef T value_type;
    typedef edge<T> Edge_t;
    typedef LinkedList<edge<T> > EdgeList_t;

    vertice():thisptr((unsigned int)this)
    {
    }

    bool operator==(const vertice<T>& rhs)
    {
        return this->value == rhs.value;
    }

    bool operator <(const vertice<T>& rhs)
    {
        return this->value < rhs.value;
    }

    unsigned long thisptr;
    value_type value;
    EdgeList_t edgeList;

    friend std::ostream& operator<<(std::ostream& out, const vertice* v)
    {
        out << std::endl;
        out << "vertice :{";
        out << "(";
        out << std::hex << v->thisptr;
        out << ")";
        out << v->value;
        out << ":";

        out << "edges :{";
        out << "list head :{";
        out << &(v->edgeList);
        out << "}";
        out << v->edgeList;
        out << "}";
        out << "}";
        out << std::endl;
    }

};

template <typename T>
class Graph
{
public:
    typedef T value_type;
    typedef  vertice<T> VerticeType;
    typedef typename VerticeType::EdgeList_t EdgeListType;
    typedef typename VerticeType::Edge_t EdgeType;

    Graph()
    {
    }

    friend std::ostream& operator<<(std::ostream& out, const Graph<value_type>& g)
    {
        out << std::endl;
        out << "graph :{" ;
        out << g.verticeList;
        out << std::endl;
    }

    bool addEdge(const T& destV, EdgeType& edge, const T& edgeVertice)
    {
        //debug("Adding edge  :") << edgeVertice << " for vertice " << destV ;
        VerticeType *finalDestVertice, tmpVertice;
        tmpVertice.value = destV;
        typename LinkedList<VerticeType*>::node_type *insNode;

        if(verticeList.findFirst(&tmpVertice, &insNode))
        {
            //debug("found  existing vertice for destination vertex :") << destV;
            finalDestVertice = insNode->value;
        }
        else
        {
            //debug("could not find existing vertice for destinaion vertex:") << destV;
            finalDestVertice = new VerticeType();
            finalDestVertice->value = destV;
            if(!verticeList.insertUniqueSorted(finalDestVertice, &insNode))
            {
                return false;
            }
        }

        VerticeType *finalEdgeVertice;
        tmpVertice.value = edgeVertice;
        if(verticeList.findFirst(&tmpVertice, &insNode))
        {
            //debug("found  existing vertice for edge vertex :") << edgeVertice;
            finalEdgeVertice = insNode->value;
        }
        else
        {
            //debug("could not find existing vertice for edge vertex:") << edgeVertice;
            finalEdgeVertice = new VerticeType();
            finalEdgeVertice->value = edgeVertice;
            if(!verticeList.insertUniqueSorted(finalEdgeVertice, &insNode))
            {
                return false;
            }
        }

        edge.vertex = finalEdgeVertice;
        typename EdgeListType::node_type *edgeInsNode;
        finalDestVertice->edgeList.insertUniqueSorted(edge, &edgeInsNode);

        return true;
    }

    bool addVertex(VerticeType* v)
    {
        assert(v);

        ListNode<VerticeType*> *insertNode = NULL;
        verticeList.insertUniqueSorted(v, &insertNode);

        return true;
    }

private:
    LinkedList<VerticeType*>  verticeList;
};


#endif
