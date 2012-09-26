#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <ostream>
#include "compiler.h"

template <typename T>
struct ListNode
{
    ListNode(const T& v):value(v), next(NULL)
    {
    }

    ListNode *next;
    T value;
} ALIGNED_CACHELINE;

template <typename T>
class LinkedList
{
public:
    LinkedList():head(NULL)
    {       
    }

    bool insert(const T& item)
    {
        ListNode<T> *newNode = new ListNode<T>(item); 
        printf("created new node :%p\n", newNode);
        if(head == NULL)
        {
            head = newNode;
            return true;
        }

        ListNode<T> **currNode = &head;;
        while(*currNode)
        {
            currNode = &((*currNode)->next);
        }
        *currNode = newNode;

        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list)
    {        
        ListNode<T> *currNode = list.head;;
        out << std::endl << "list :";
        while(currNode)
        {            
            if(currNode != list.head)
                out << "-->";

            out << "(" << currNode << ")" << currNode->value;
            currNode = currNode->next;
        }

        out << "--> null";
        out << std::endl;
        return out;
    }
   
    struct ListNode<T> *head;
};

#endif 
