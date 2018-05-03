#define __SORT_C__

#include "sort.h"

void swap(int *a, int *b)
{
    int  temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void sort_print(int a[], int n)
{
    int  i;

    for (i = 0; i < n - 1; i++)
    {
        printf("%d, ", a[i]);
    }

    printf("%d\n", a[i]);
}

/* 时间复杂度：O(n^2) */
void sort_insert(int a[], int n)
{
    int  i, j, temp;
    
    for (i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i + 1])
        {
            temp = a[i + 1];

            /* 前面所有比temp大的值向后移 */
            for (j = i; j >= 0 && a[j] > temp; j--)
            {
                a[j + 1] = a[j];
            }

            a[j + 1] = temp;
        }
    }
}

void sort_select(int a[], int n)
{
    int  i, j, min;

    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[min] > a[j])
            {
                min = j;
            }
        }

        if (min != i)
        {
            swap(&a[i], &a[min]);
        }
    }
}

void sort_bubble(int a[], int n)
{
    int  i, j;
    int  swap_flag;

    for (i = 0; i < n - 1; i++)
    {
        swap_flag = 0;
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap_flag = 1;
                swap(&a[j], &a[j + 1]);
            }
        }

        if (swap_flag == 0)  /* no swap happen, sort finished */
        {
            break;
        }
    }
}

int partition(int a[], int low, int high)
{
    int pivot_key = a[low];
    
    while (low < high)
    {
        /* scan from 2 sides to middle */
        while (low < high && a[high] >= pivot_key)
        {
            high--;
        }

        if (low != high)
        {
           swap(&a[low], &a[high]);
        }
        
        while (low < high && a[low] <= pivot_key)
        {
            low++;
        }

        if (low != high)
        {
            swap(&a[low], &a[high]);
        }
    }
    
    return low;
}

/* O(nlog2n) */
void sort_quick(int a[], int low, int high)
{
    int  pivot;
    
    if (low < high)
    {
        pivot = partition(a, low, high); 
        sort_quick(a, low,  pivot - 1);
        sort_quick(a, pivot + 1, high);
    }
}

/**
 * 已知H[s…m]除了H[s] 外均满足堆的定义
 * 调整H[s],使其成为大顶堆.即将对第s个结点为根的子树筛选,
 * 
 * @param H是待调整的堆数组
 * @param s是待调整的数组元素的位置 
 * @param length是数组的长度 
 * 
 */
void heap_precolate_down(int H[], int s, int length)
{
    int  child = 2 * s + 1;  //左孩子结点的位置。(i+1 为当前调整结点的右孩子结点的位置)
    
    while (child < length)
    {
        if (child + 1 < length && H[child] < H[child + 1])  //如果右孩子大于左孩子(找到比当前待调整结点大的孩子结点)
        {
            ++child;
        }
        
        if (H[s] < H[child])  //如果较大的子结点大于父结点
        {
            swap(&H[s], &H[child]);  //那么把较大的子结点往上移动，替换它的父结点
            s = child;               //重新设置s ,即待调整的下一个结点的位置
            child = 2 * s + 1;
        }
        else  //如果当前待调整结点大于它的左右孩子，则不需要调整，直接退出
        {
            break;
        }
    }
}

/**
 * 初始堆进行调整
 * 将H[0..length-1]建成堆
 * 调整完之后第一个元素是序列的最小的元素
 */
void heap_build(int H[], int length)
{
    //最后一个有孩子的节点的位置 i=  (length -1) / 2
    for (int i = (length - 1) / 2; i >= 0; --i)
    {
        heap_precolate_down(H, i, length);
    }
}

/**
 * 堆排序算法
 */
void sort_heap(int H[], int length)
{
    //初始堆
    heap_build(H, length);
    
    //从最后一个元素开始对序列进行调整
    for (int i = length - 1; i > 0; --i)
    {
        //交换堆顶元素H[0]和堆中最后一个元素
        swap(&H[i], &H[0]);
        
        //每次交换堆顶元素和堆中最后一个元素之后，都要对堆进行调整
        heap_precolate_down(H, 0, i);
    }
}

