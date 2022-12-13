#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 6

int arr[SIZE];
sem_t mutex;
typedef struct Composicion{
    int left; //izq
    int right; //der
} cmp;


void merge(){

}
void* mergeSort(void* a){
    cmp t1;


}
void printArray(int A[], int size){
    int i;
    for(i = 0; i< size; i++)
        printf("%d ",A[i]);

    printf("\n");
}

int main(){
    int arr[SIZE] ={12,11,13,5,6,7};
    pthread_t tid;

    cmp e;
    e.left = 0;
    e.right = SIZE-1;

    printf("given array is \n");
    printArray(arr,SIZE);

    sem_init(&mutex,0,1);

    pthread_create(&tid,NULL,mergeSort,&e);
    pthread_join(tid,NULL);

    printf("\nSorted array is\n");
    printArray(arr,SIZE);



}
