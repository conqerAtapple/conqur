#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <ostream>
#include "compiler.h"
#include "Logger.h"


template <typename T>
struct ListNode
{
    typedef T value_type;

    ListNode(const T& v):value(v), next(NULL)
    {
    }

    ~ListNode()
    {
        debug("deleting") << value;
    }

    ListNode *next;
    T value;

} ALIGNED_CACHELINE;

template <typename T>
class LinkedList
{
public:
    typedef T value_type;

    LinkedList():head(NULL)
    {
    }

    LinkedList(struct ListNode<T> *hd):head(hd)
    {
    }

    bool insert(const value_type& item)
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

    size_t removeAll(const value_type& value)
    {
        struct ListNode<T> *curr = head, *last = NULL ;
        size_t dCount = 0;
        while(curr)
        {
            if(curr->value == value)
            {
                if(curr == head)
                {
                    head = curr->next;
                    delete curr;
                    curr = head;
                    last = NULL;
                    dCount++;
                    continue;
                }
                else
                {
                    last->next = curr->next;
                    delete curr;
                    curr = last->next;
                    dCount++;
                    continue;
                }
            }
            last = curr;
            curr = curr->next;
        }

        return  dCount;
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

template <typename T>
class LinkedList<T*>
{
public:
    typedef T* value_type;

    friend std::ostream& operator<<(std::ostream& out, const LinkedList& list)
    {
        ListNode<value_type> *currNode = list.head;
        out << std::endl << "list :";
        while(currNode)
        {
            if(currNode != list.head)
                out << "-->";

            // out << "(" << currNode << ")" << *(currNode->value);
            out << *(currNode->value);
            currNode = currNode->next;
        }

        out << "--> null";
        out << std::endl;
        return out;
    }

    bool insertSortedUnique(const value_type& item, ListNode<value_type>** insertNode)
    {
        ListNode<value_type> **ppHead = &head;
        ListNode<value_type> *curr = head, *last = NULL;

        while((curr != NULL) && (*(curr->value) < *item))
        {
            last = curr;
            curr = curr->next;
        }

        if((curr != NULL) && *(curr->value) == *item)
        {
            *insertNode = curr;
            return false;
        }

        ListNode<value_type> *newNode =  new ListNode<value_type>(item) ;
        newNode->next = curr;
        if(last)
        {
            last->next =newNode;
        }

        if(*ppHead == curr)
        {
            *ppHead = newNode;
        }

        std::cout << *this;
        return true;

    }

    struct ListNode<value_type> *head;
};
#endif 
