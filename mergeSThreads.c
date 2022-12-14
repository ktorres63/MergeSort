#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#define SIZE 100

int arr[SIZE];
pthread_mutex_t lock;

typedef struct Composicion{
    int id;
    int left; //izq
    int right; //der
} cmp;

void merge(int l, int m, int r){
    int i,j,k;

    int n1 = m-l+1; // tam izq
    int n2 = r-m;   // tam der


    int L[n1], R[n2];

    for (i=0;i<n1;i++)
        L[i] = arr[l+i];
    for(j=0;j< n2;j++)
        R[j] = arr[m+1+j];

    i = 0;
    j = 0;
    k = l;
    pthread_mutex_lock(&lock);

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
    pthread_mutex_unlock(&lock);
}


void* mergeSort(void* a){
    cmp *g = a;
    cmp pi,pd;
    int l = g->left;
    int r = g->right;
    pthread_t tle, tri;

    if(l < r){
        int m = l+(r-l)/2;

        //parte izq
        pi.left = l;
        pi.right = m;
        //parte derecha
        pd.left = m+1;
        pd.right = r;

        pthread_create(&tle,NULL,mergeSort,&pi);
        pthread_create(&tri,NULL,mergeSort,&pd);

        pthread_join(tle,NULL);
        pthread_join(tri,NULL);

        merge(l,m,r);

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
    for(int i=0;i<SIZE;i++){
        arr[i] = rand()%9;
    }
    pthread_mutex_init(&lock,NULL);
    //sem_init(&mutex,0,1);

    pthread_t tid;

    printf("Lista inicial\n");
    printArray(arr,SIZE);

    cmp e;
    e.left = 0;
    e.right = SIZE-1;

    pthread_create(&tid,NULL,mergeSort,&e);
    pthread_join(tid,NULL);

    printf("\nLista Ordenada\n");
    printArray(arr,SIZE);
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecucion %f segundos\n", time_spent);
}
