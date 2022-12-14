#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100
void merge(int arr[], int l, int m, int r){
    int i,j,k;

    int n1 = m-l+1;
    int n2 = r-m;

    //Create temp arrays

    int L[n1], R[n2];

    //copy data to temp arrays
    for (i=0;i<n1;i++)
        L[i] = arr[l+i];
    for(j=0;j< n2;j++)
        R[j] = arr[m+1+j];

    i = 0;
    j = 0;

    k = l;
    while(i < n1 && j < n2){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    //L[] if there any
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    //R[], if there any
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[],int l,int r){
    if(l < r){
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l +(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr,l,m,r);
    }
}

void printArray(int A[], int size){
    int i;
    for(i = 0; i< size; i++)
        printf("%d ",A[i]);

    printf("\n");
}

int main(){
    double time_spent = 0.0;
    clock_t begin = clock();

    srand(time(NULL));
    int arr[SIZE];
    for (int i=0;i<SIZE;i++){
        arr[i] = rand()%9;
    }

    int arr_size = SIZE;

    printf("Lista inicial is \n");
    printArray(arr, SIZE);

    mergeSort(arr,0,SIZE-1);

    printf("\nLista Ordenada \n");
    printArray(arr,arr_size);
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecucion %f segundos\n", time_spent);


}
