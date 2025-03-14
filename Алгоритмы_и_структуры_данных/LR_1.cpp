#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

int main()
{
    long long int* mass;
    long long int n,l,i,j,min,number;
    size_t t;
    struct timeval t1,t2;
    n = 10000;
    l = 10000;

    //Инициализация массивов
    mass = (long long int*)malloc(l * sizeof(mass));
    if (mass == NULL)
    {
        printf("Error!\n");
        return 1;
    }

    t = time(NULL);
    if (t == -1)
    {
        printf("Error!\n");
        return 1;
    }
    srand(t);
    for (i = 0; i < l; i ++) mass[i] = rand()%n;

    //Вывод первоначального массива
    printf("Unsorted array\n");
    for (i = 0; i < 10; i ++) printf("%d\ ", mass[i]);
    printf("...");
    for (i = l - 10; i < l; i ++) printf("%d\ ", mass[i]);
    printf("\n");

    //Сортировка подсчетом

    if (gettimeofday(&t1,NULL)==-1)
    {
        printf("Error t1");
        return 1;
    }

    for (i = 0; i < l - 1; i ++)
    {
        min = mass[i];
        for (j = i + 1; j < l; j ++)
        {
            if (mass[j] <= min)
            {
                min = mass[j];
                number = j;
            }
        }
        mass[number] = mass[i];
        mass[i] = min;
    }
    if (gettimeofday(&t2,NULL)==-1)
    {
        printf("Error t2");
        return 1;
    }

    // Вывод отсортированного массива
    printf("Sorted array\n");
    for (i = 0; i < 10; i ++) printf("%d\ ", mass[i]);
    printf("...");
    for (i = l - 10; i < l; i ++) printf("%d\ ", mass[i]);
    printf("\n");
    printf("\nmilli second algorithm: %lld ",((t2.tv_sec *1000000 + t2.tv_usec) - (t1.tv_sec * 1000000 + t1.tv_usec))/1000);
    return 0;
}


//Сортировка подсчетом

for (j = 0; j < n + 1; j ++)
    {
        for (i = 0; i < l; i ++)
        {
            if (mass[i] == j) mass2[j] ++;
        }
    }
    for (i = 0; i < l; i ++)
    {
        for (j = 0; j < n + 1; j ++)
        {
            if (mass2[j] > 0)
            {
                k = mass2[j];
                while (k > 0)
                {
                    mass[i] = j;
                    k --;
                    i ++;
                }
            }
        }
    }



