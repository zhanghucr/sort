#ifndef __SORT_H__
#define __SORT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#ifdef __SORT_C__
    #define SORT_EXT
#else
    #define SORT_EXT        extern
#endif

SORT_EXT void swap(int *a, int *b);
SORT_EXT void sort_print(int a[], int n);
SORT_EXT void sort_insert(int a[], int n);
SORT_EXT void sort_select(int a[], int n);
SORT_EXT void sort_bubble(int a[], int n);
SORT_EXT int partition(int a[], int low, int high);
SORT_EXT void sort_quick(int a[], int low, int high);
SORT_EXT void heap_precolate_down(int H[], int s, int length);
SORT_EXT void heap_build(int H[], int length);
SORT_EXT void sort_heap(int H[], int length);

#ifdef __cplusplus
}
#endif

#endif
