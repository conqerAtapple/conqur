
#include <iostream>

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
