#include <stdio.h>

void swap(int* a);

void swap(int* a){
    int b = 10;
    *a = b;
}

int main(void)
{
    int aa = 5;
    int* a = &aa;
    swap(a);

    printf("%d",*a);
}
