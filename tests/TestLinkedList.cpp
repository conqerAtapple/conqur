
#include <iostream>
#include <assert.h>
#include "TestLinkedList.h"
#include "sysutils.h"

void testCreate()
{
    int arr[] = {
        6,1,2,8,100, 0, -1
    };

    LinkedList<int> list;
    for(size_t i = 0; i < ARRAY_SIZE(arr); i++)
    {
        list.insert(arr[i]);
    }

    std::cout << list;
}

void testSplit()
{

    int arr[] = {
        6,1,2,8,100, 0, -1
    };

    LinkedList<int> list;
    for(size_t i = 0; i < ARRAY_SIZE(arr); i++)
    {
        list.insert(arr[i]);
    }

    LinkedList<int> listA, listB;
    list.split(listA, listB);

    std::cout << listA;
    std::cout << listB;
}

void testRemoveAll()
{    
    {
        int arr[] = {
            6, 6,1,2,8,100, 0, -1
        };

        LinkedList<int> list;
        for(size_t i = 0; i < ARRAY_SIZE(arr); i++)
        {
            list.insert(arr[i]);
        }

        assert(list.removeAll(6) == 2);
        std::cout << list;
    }

    {
        int arr[] = {
            6, 6,1,2,8,100, 0, -1
        };

        LinkedList<int> list;
        for(size_t i = 0; i < ARRAY_SIZE(arr); i++)
        {
            list.insert(arr[i]);
        }

        assert(list.removeAll(-1) == 1);
        std::cout << list;
    }

      {
        int arr[] = {
            6, 6,0,2,8,100, 0, -1
        };

        LinkedList<int> list;
        for(size_t i = 0; i < ARRAY_SIZE(arr); i++)
        {
            list.insert(arr[i]);
        }

        assert(list.removeAll(0) == 2);
        std::cout << list;
    }
}
