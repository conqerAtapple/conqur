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

    LinkedList(struct ListNode<T> *hd):head(hd)
    {
    }

    bool insert(const T& item)
    {
        ListNode<T> *newNode = new ListNode<T>(item);
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

    void split(LinkedList& first, LinkedList& second)
    {
        first.head = head; 
        second.head = head->next;

        struct ListNode<T> *head1 = first.head, *head2 = second.head;

        // a ->b ->c ->d -> e ->f ->null
        // a - c - e - null
        // b - d - f 
        while(head1 && head2)
        {
            head1->next = head2 ? head2->next : NULL;
            head1 = head1->next;

            head2->next = head1 ? head1->next : NULL;
            head2 = head2->next;
        }
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
