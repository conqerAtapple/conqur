#ifndef SYSUTIL_LINUX_H
#define SYSUTIL_LINUX_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096
#define PAGE_OF(_addr) ( ((unsigned long) (_addr)) & ~(PAGE_SIZE-1) )

static int unprotect(unsigned char *addr, size_t len) 
{
    int rc = 0;
    unsigned long pg1 = PAGE_OF(addr), pg2 = PAGE_OF(addr + len - 1);
    if ((rc = mprotect( (void*)pg1, pg2 - pg1 + PAGE_SIZE, PROT_READ | PROT_EXEC | PROT_WRITE)))
    {
        perror("mprotect");
        return rc;
    }

    return rc;
}


#endif
