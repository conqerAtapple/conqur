#ifndef X86_LOGGER_H
#define X86_LOGGER_H

#include <stdio.h>

#define NOP5 ".byte 0x0f, 0x1f, 0x44, 0x00, 0x00;"

/*
#define TRACE(_point, _args...)          \
    do {                                   \
        asm goto (                           \
                "0: " NOP5                         \
                ".pushsection trace_table, \"a\";" \
                ".quad " #_point ", 0b, %l0;"      \
                ".popsection"                      \
                : : : : __lbl_##_point);           \
        if (0) {                             \
            __lbl_##_point: printf(_args);     \
        }                                    \
    } while (0);
*/

/*
#define TRACE(_point, _args...)  \
do                                              \
{                                               \   
    if (0) {                                      \
        __lbl_##_point:printf(_args) ; \
    }                                          \
    asm (                          \
        "0: " NOP5                                  \
        ".pushsection trace_table, \"a\" \n\t"  \
        " .long  0b  \n\t"     \
        ".popsection \n\t"  \
        );                                              \                                                         
}while(0);\
*/

/*
#define TRACE(_point, _args...)  \
do                                              \
{                                                   \       
    asm volatile (                          \
        "0: " NOP5                                  \     
        " jmp 1f"        \
        );                              \
      __lbl_##_point:printf(_args) ; \
     asm volatile ( " 1:" \
            " .section trace_table, \"a\" \n\t"  \
            " .align 4 \n\t"    \
            " .long  0b \n\t"     \            
         ); \
}while(0);\
*/

/*
#define TRACE(_point, _args...)  \
do                                              \
{                                                   \ 
     asm volatile ( "1: " \
            " .pushsection ._trace, \"aw\", @progbits \n\t"  \
            " .align 4 \n\t"    \
            " .long  1b\n\t"     \
            " .popsection \n\t"   \
         ); \
         printf("hello\n"); \
}while(0);\
*/

#define TRACE(_point, _args...)  \                 
    int i=10, j;                            \ 
     asm (                         \
          "mov %1, %0 \n"            \
          :  "=r"(j)   \
          : "r"(i)  \
         ); \
         printf("hello %d, %d\n", i, j); 


#endif
