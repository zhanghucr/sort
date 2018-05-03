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

/* ʱ�临�Ӷȣ�O(n^2) */
void sort_insert(int a[], int n)
{
    int  i, j, temp;
    
    for (i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i + 1])
        {
            temp = a[i + 1];

            /* ǰ�����б�temp���ֵ����� */
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
 * ��֪H[s��m]����H[s] �������ѵĶ���
 * ����H[s],ʹ���Ϊ�󶥶�.�����Ե�s�����Ϊ��������ɸѡ,
 * 
 * @param H�Ǵ������Ķ�����
 * @param s�Ǵ�����������Ԫ�ص�λ�� 
 * @param length������ĳ��� 
 * 
 */
void heap_precolate_down(int H[], int s, int length)
{
    int  child = 2 * s + 1;  //���ӽ���λ�á�(i+1 Ϊ��ǰ���������Һ��ӽ���λ��)
    
    while (child < length)
    {
        if (child + 1 < length && H[child] < H[child + 1])  //����Һ��Ӵ�������(�ҵ��ȵ�ǰ����������ĺ��ӽ��)
        {
            ++child;
        }
        
        if (H[s] < H[child])  //����ϴ���ӽ����ڸ����
        {
            swap(&H[s], &H[child]);  //��ô�ѽϴ���ӽ�������ƶ����滻���ĸ����
            s = child;               //��������s ,������������һ������λ��
            child = 2 * s + 1;
        }
        else  //�����ǰ�������������������Һ��ӣ�����Ҫ������ֱ���˳�
        {
            break;
        }
    }
}

/**
 * ��ʼ�ѽ��е���
 * ��H[0..length-1]���ɶ�
 * ������֮���һ��Ԫ�������е���С��Ԫ��
 */
void heap_build(int H[], int length)
{
    //���һ���к��ӵĽڵ��λ�� i=  (length -1) / 2
    for (int i = (length - 1) / 2; i >= 0; --i)
    {
        heap_precolate_down(H, i, length);
    }
}

/**
 * �������㷨
 */
void sort_heap(int H[], int length)
{
    //��ʼ��
    heap_build(H, length);
    
    //�����һ��Ԫ�ؿ�ʼ�����н��е���
    for (int i = length - 1; i > 0; --i)
    {
        //�����Ѷ�Ԫ��H[0]�Ͷ������һ��Ԫ��
        swap(&H[i], &H[0]);
        
        //ÿ�ν����Ѷ�Ԫ�غͶ������һ��Ԫ��֮�󣬶�Ҫ�Զѽ��е���
        heap_precolate_down(H, 0, i);
    }
}

