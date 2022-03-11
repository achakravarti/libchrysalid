#include "../include/heap.h"
#include <stdio.h>


int main(void)
{
        int *i = c_heap_std_new(sizeof *i, 1);
        *i = 45;
        
        printf("i = %d\n", *i);
        printf("sz = %lu\n", c_heap_sz(i));
        printf("refc = %lu\n", c_heap_refc(i));

        int *j = c_heap_copy(i);
        printf("j = %d\n", *j);
        printf("sz = %lu\n", c_heap_sz(j));
        printf("refc = %lu\n", c_heap_refc(j));
        printf("refc = %lu\n", c_heap_refc(i));

        return 0;
}

