#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "sort.h"

char *tv_diff_string(struct timeval *tv_begin, struct timeval *tv_end)
{
    static char  diff_string[64];
    
    long   tv_diff = (tv_end->tv_sec - tv_begin->tv_sec) * 1000000 + tv_end->tv_usec - tv_begin->tv_usec;

    memset(diff_string, sizeof(diff_string), 0);
    
    if (tv_diff < 1000)
    {
        snprintf(diff_string, sizeof(diff_string), "%ld us", tv_diff);
    }
    else if (tv_diff < 1000000)
    {
        snprintf(diff_string, sizeof(diff_string), "%ld ms", tv_diff / 1000);
    }
    else
    {
        snprintf(diff_string, sizeof(diff_string), "%ld s, %ld ms", tv_diff / 1000000, (tv_diff % 1000000) / 1000);
    }
    
    return diff_string;
}

int main(int argc, char *argv[])
{
    int  i;
    int  size;
    int  print_flag;
    int  *a;
    struct timeval  tv_begin;
    struct timeval  tv_end;
    
    memset(&tv_begin, 0, sizeof(struct timeval));
    memset(&tv_end, 0, sizeof(struct timeval));

    if (argc != 4)
    {
        printf("sort <algo> <capacity> <print flag>\n");
        printf("sort algo list:\n");
        printf("0 -- bubble sort\n");
        printf("1 -- insert sort\n");
        printf("2 -- select sort\n");
        printf("3 -- quick  sort\n");
        printf("4 -- heap   sort\n");
        return -1;
    }

    size = atoi(argv[2]);
    if (size <= 0)
    {
        return -1;
    }

    print_flag = atoi(argv[3]);

    a = (int *)malloc(sizeof(int) * size);
    if (a == NULL)
    {
        return -1;
    }

    srand(time(0));

    for (i = 0; i < size; i++)
    {
        a[i] = rand() % (size * 2);
    }

    if (print_flag)
    {
        sort_print(a, size);
    }

    switch (*argv[1])
    {
        case '0':
        {
            printf("bubble sort\n");
            gettimeofday(&tv_begin, NULL);
            sort_bubble(a, size);
            gettimeofday(&tv_end, NULL);
        }
        break;

        case '1':
        {
            printf("insert sort\n");
            gettimeofday(&tv_begin, NULL);
            sort_insert(a, size);
            gettimeofday(&tv_end, NULL);
        }
        break;

        case '2':
        {
            printf("select sort\n");
            gettimeofday(&tv_begin, NULL);
            sort_select(a, size);
            gettimeofday(&tv_end, NULL);
        }
        break;

        case '3':
        {
            printf("quick sort\n");
            gettimeofday(&tv_begin, NULL);
            sort_quick(a, 0, size - 1);
            gettimeofday(&tv_end, NULL);
        }
        break;

        case '4':
        {
            printf("heap sort\n");
            gettimeofday(&tv_begin, NULL);
            sort_heap(a, size);
            gettimeofday(&tv_end, NULL);
        }
        break;

        default:
        {
            printf("unknow sort %s\n", argv[1]);
        }
        break;
    }

    if (print_flag)
    {
        sort_print(a, size);
    }
    
    printf("sort time: %s\n", tv_diff_string(&tv_begin, &tv_end));
    free(a);
    return 0;
}

/* end of sort_test.c */