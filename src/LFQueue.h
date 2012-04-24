#ifndef LFQUEUE_H
#define LFQUEUE_H


#include "Logger.h"

#define cas(ptr, old, new) \
({  \
    unsigned long  __ret;                                                                       \
    unsigned long  __new = reinterpret_cast<unsigned long>(new); \
    unsigned long  __old = reinterpret_cast<unsigned long>(old);     \
    volatile unsigned long *__ptr = (volatile unsigned long *)(ptr);      \
    asm volatile( "lock cmpxchgl %2,%1"                                               \
			     : "=a" (__ret), "+m" (*__ptr)      \
                 : "r" (__new), "0" (__old)            \
                 : "memory");                           \
                 (__ret == __old) ; \
})

struct RefCount
{
    RefCount(unsigned c):
    count(c)
    {
    }

    unsigned value()
    {
        return(*(volatile int *)&count);
    }

    void dec()
    {
        asm volatile( "lock;decl %0"
                      : "+m" (count));
    }

    void inc()
    {
        asm volatile( "lock;incl %0"
                      : "+m" (count));
    }

    bool decAndTest()
    {
        unsigned char c;
        debug("count :%u", count);
        asm volatile( "lock;decl %0; sete %1"
                      : "+m" (count), "=qm" (c)
                      : : "memory");
        debug("c :%u, count :%u", c, count);
        return c != 0;
    }

    unsigned count;
};

template<typename T>
struct Node
{

    Node():
    value(T()),
    next(NULL),
    rc(1)
    {
        debug("creating %d", value);
    }

    Node(const T& v):
    value(v),
    next(NULL),
    rc(1)
    {
        debug("creating %d", value);
    }

    T value;
    Node<T> *next;
    RefCount rc;

    bool get()
    {
        if (rc.value())
        {
            rc.inc();
            return true;
        }

        return false;
    }

    void put()
    {
        if (rc.decAndTest())
        {
            debug("deleting %d", value);
            delete this;
        }
    }

};

template <typename T>
class LFQueue
{

public:

    LFQueue()
    {
        Node<T> *nwNode = new Node<T>();
        head = tail = nwNode; 
    }

    ~LFQueue()
    {
        head->put();
    }

    void enq(const T& item)
    {
        Node<T> *nwNode = new Node<T>(item);
        while (true)
        {
            Node<T> *curTail = tail;
            Node<T> *curTailNxt = tail->next;
            if (curTail == tail)
            {
                // We were first among writers to get to tail
                // Now atomically try to set the new node
                // to tail's next
                if (curTailNxt == NULL)
                {
                    // No one changed the tail to add a new node
                    // So we will try to add it
                    if (cas(&tail->next, curTailNxt, nwNode))
                    {
                        // successfully set the new node as tail's next
                        // Now reset the tail
                        cas(&tail, curTail, nwNode);
                        return;
                    }
                    // tail's next changed. Someone else added a new node there
                    // so we try again
                }
                else
                {
                    // someone else added a new node to tail
                    // but could not get to setting the new tail. So
                    // we will help that thread by setting the new tail
                    cas(&tail, curTail, curTailNxt);
                }
                // We are here bcoz someone else set the new tail
                // So we try again
            }
        }
    }

    bool deq(T& out)
    {
        Node<T> *currTail = tail, *currHead = head, *currHeadNext = head->next;

        while (true)
        {
            // if head and tail point to the same item, 
            // then there are 2 possibilities:
            //  - head is pointing to the sentinel if next is NULL
            //  - tail is in the process of being moved if next is NOT NULL
            if (currHead == currTail)
            {
                currHead->get();
                if (currHeadNext == NULL)
                {
                    // ok head is a sentinel.So no readable items
                    currHead->put();
                    return false;
                }
                // We are here because we hit the second case
                // So we help the thread thats moving the tail.
                cas(&tail, currTail, currHeadNext);
                currHead->put();
            }
            else
            {
                T temp = currHeadNext->value;
                if (cas(&head, currHead, currHeadNext))
                {
                    out = temp;
                    currHead->put();
                    return true;
                }
            }
        }
        return true;
    }

    void print()
    {
        debug("list :"); 
        Node<T> *curr = head->next;
        while (curr != NULL && curr->get())
        {
            debug("value :%d", curr->value); 
            curr = curr->next;
        }
    }

private:
    Node<T> *tail, *head;
};

#endif
