#include <pthread.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "LFQueue.h"
#include "TestIntervalTree.h"
#include "SkipList.h"

#define PRODS 10
#define CONS 10

LFQueue<int> lfq;

void* run_enq(void*)
{
     int arr[] = {
        1
        ,2,3,4,5,6,7,8,9,10
    };

    for(int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
    {
        lfq.enq(arr[i]);
    }
}


void* run_deq(void*)
{
    for(int i = 0; i <100; i++)
    {
        int o;
        if(lfq.deq(o))
        {
            debug("dequed: ") << o ;//<< eol;
        }
        else
        {
            debug("dequed none") ;//<< eol;
        }
    }
}

void testLfQueue()
{   
    debug("\n");
   // pthread_once(&once_control, cb_init);
    pthread_t pr_threads[PRODS];
    pthread_t cr_threads[CONS];

    for(int i=0; i < PRODS; i++)
    {
       // debug("creating producer thread %d", i);
        pthread_create(&pr_threads[i], NULL, &run_enq, &i);
    }


     for(int i=0; i < CONS; i++)
    {
       //  debug("creating cons thread %d", i);
        pthread_create(&cr_threads[i], NULL, &run_deq, &i);
    }


     for(int i=0; i < PRODS; i++)
    {
        pthread_join(pr_threads[i], NULL);
    }


     for(int i=0; i < CONS; i++)
    {
        pthread_join(cr_threads[i], NULL);
    }
}

void testIntervalTree()
{
  testIntervalQuery();  
  testRemoveInterval(); 
  testLocks();
  testRemoveFromMiddle();
  testBoundaries();
  testStringIntervals();
  testNames();
}

void testSkipList()
{
    SkipList<int> sList(5);
    sList.add(3);
    sList.add(4);
    sList.add(5);
    sList.add(2);
    sList.add(3);
}

int main()
{   
    //TRACE(main_entry, "main");
    //debug("main");
    //printf("main\n");    
    testLfQueue();
    testSkipList();
    return 0;
}
