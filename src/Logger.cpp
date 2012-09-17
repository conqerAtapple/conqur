
#include "Logger.h"
#include "sysutils.h"
#include "archtypes.h"

Logger* Logger::instance = NULL;

/*
void enable(tracepoint *point) 
{
    extern struct trace_desc trace_table_start[], trace_table_end[];
    struct trace_desc *desc;
    for (desc = trace_table_start; desc < trace_table_end; desc++) {
        if (desc->point != point)
            continue;

        unsigned long offset = (desc->jump_to - desc->jump_from) - 5;
        if ((offset > INT32_MAX) || (offset < INT32_MIN)) {
            fprintf(stderr, "offset too big: %lx\n", offset);
            abort();
        }

        int32_t offset32 = offset;
        unsigned char *dest = (unsigned char *)desc->jump_from;
        unprotect(dest, 5);
        dest[0] = 0xe9;
        memcpy(dest+1, &offset32, 4);
    }
}

*/
