#ifndef SKIPLIST_HPP
#define SKIPLIST_HPP

#include "Logger.h"

typedef unsigned level_type;

template <typename T>
struct SkipListNode
{
    typedef T value_type;

    SkipListNode(const level_type& levels):
    numLevels(levels), value(-999)// TODO: delete default value
    {     
        next = new SkipListNode<T>*[levels];
        initialize();
    }

    SkipListNode(const level_type& levels, const value_type& v ):
    numLevels(levels), value(v)
    {     
        next = new SkipListNode<T>*[levels];
        initialize();
    }

    level_type numLevels;
    value_type value;
    struct SkipListNode<T> **next;

    void initialize()
    {
        for (int i=0; i < numLevels; i++)
        {
            next[i] = NULL;
        }
    }

    ~SkipListNode()
    {
        debug("deleting ") << value;
        //TODO: impl
    }
};

template <typename T>
class SkipList
{
public:
    typedef T value_type;

    SkipList(level_type lvl):
    numLevels(lvl)
    {
        initialize(lvl);
    }

private:
    level_type numLevels;
    struct SkipListNode<T> *head, *tail;

    // 
    // Private Methods
    // 
    void initialize(level_type lvl)
    {
        head = new SkipListNode<T>(lvl);
        tail = new SkipListNode<T>(lvl);

        for (level_type i = 0; i < lvl; i++)
        {
            head->next[i] = tail;
        }

        srand ( time(NULL) );

    }

public:

    level_type find(const T& value, 
                    SkipListNode<T>** predNodes, 
                    SkipListNode<T>** succNodes) const
    {
        int currLevel = numLevels - 1;
        SkipListNode<T>* currNode = head;
        predNodes[currLevel] = head;
        succNodes[currLevel] = tail;

        while (currLevel >= 0)
        {
            debug("curr node at :") << "level :" << currLevel << " : " <<  currNode->value;
            predNodes[currLevel] = currNode;
            succNodes[currLevel] = currNode->next[currLevel];

            if (currNode->value == value)
            {
                debug("found value :") << value;
                return currLevel;
            }

            if ((currNode->next[currLevel] != NULL) &&
                ((currNode->next[currLevel] == tail) ||
                 (currNode->next[currLevel]->value > value)))
            {
                debug("descending down .. next :") << currNode->next[currLevel]->value;
              
                currLevel--;
            }
            else
            {
                currNode = currNode->next[currLevel];
                debug("moving to next :") << currNode->value;
            }
        }

        return(numLevels );
    }

    void printAll() const
    {
        SkipListNode<T>* currNode = head;

        for (int i= numLevels-1, j=0; i >=0; i--)
        {
            j=0;
            currNode = head;

            do
            {
                debug("Node [") << i << "][" << j++ << "]" << currNode->value;
                currNode = currNode->next[i];
            }while (currNode != NULL);
        }
    }

    bool add(const T& value)
    {
        {
            debug("") << "adding " << value;
        }
        SkipListNode<T>* predNodes[numLevels];
        SkipListNode<T>* succNodes[numLevels];

        level_type f = find(value, predNodes, succNodes);
        if(f == numLevels)
        {
            debug("value ") << value << "already in the set";
            return false;
        }

        int randTop = rand() % numLevels;
        debug("adding new node at top level :") << randTop;

        SkipListNode<T>* newNode = new SkipListNode<T>(numLevels, value);
        for (int i = randTop; i >= 0 ; i--)
        {
            
            debug("connecting new node at level ") << i 
            << " pred :" << predNodes[i]->value
            << " succ :" << succNodes[i]->value;
            
            predNodes[i]->next[i] = newNode;
            newNode->next[i] = succNodes[i];

            {
                debug("done adding at level :") << i;
            }
        }
        printAll();

        return true;
    }
};


#endif
