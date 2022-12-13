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

void merge(int l, int m, int r){
    int i,j,k;

    int n1 = m-l+1; // tam izq
    int n2 = r-m;   // tam der

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
//    sem_wait(&mutex);
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
  //  sem_post(&mutex);
}


void* mergeSort(void* a){
    cmp *g = a;
    int l = g->left;
    int r = g->right;
    pthread_t tle, tri;


    if(l < r){
        int m = l+(r-l)/2;
        cmp pi,pd;

        //parte izq
        pi.left = l;
        pi.right = m;
        //parte derecha
        pd.left = m+1;
        pd.right = r;

        pthread_create(&tle,NULL,mergeSort,&pi);
        pthread_create(&tri,NULL,mergeSort,&pd);

        merge(l,m,r);

        pthread_join(tle,NULL);
        pthread_join(tri,NULL);


    }

}
void printArray(int A[], int size){
    int i;
    for(i = 0; i< size; i++)
        printf("%d ",A[i]);

    printf("\n");
}

int main(){
   arr[0] =12;
   arr[1] =11;
   arr[2] =13;
   arr[3] =5;
   arr[4] =6;
   arr[5] =7;

       //,11,13,5,6,7};
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
