#include <stdio.h>
#include <stdlib.h>
#define SIZE 6
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

    //Merge the temp arrays back
    //into arr[l..r]
    //initial index of first subarray
    i = 0;
    //initiañ index of second subarray
    j = 0;

    //initial index of merged subarray
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
    //copy the reimaining elements
    //of L[], if there any
    while(i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }
    //copy the remaining elements of
    //R[], if there any
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[],int l,int r){
    if(l < r){
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
    int arr[SIZE]={12,11,13,5,6,7};
    int arr_size = SIZE;

    printf("given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr,0,arr_size-1);

    printf("\nSorted array is\n");
    printArray(arr,arr_size);
    return 0;

}
