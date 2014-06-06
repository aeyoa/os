#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define max 20

int a[max][max];
int b[max][max];
int result[max][max];
int n, m;
int i, j;
sem_t mutex;

void *readFromFile(void *args)
{  
sem_wait(&mutex);
int value; 
sem_getvalue(&mutex, &value); 
printf("The value of the semaphors is %d\n", value);

printf("reading\n");
FILE *file = fopen("in.txt", "r");
fscanf(file, "%i %i\n", &n, &m);
printf("reading %d, %d\n", n, m);
for (i=0; i<n; i++)
{
  for (j=0; j<m; j++)
  {
   fscanf(file, "%d", &a[i][j]); 
  }
}
for (i=0; i<n; i++)
{
  for (j=0; j<m; j++)
  {
   fscanf(file, "%d", &b[i][j]); 
  }
}
fclose(file);
sem_post(&mutex);
return 0;
}

void *sumMatrices(void *args)
{
  sem_wait(&mutex);

int value; 
sem_getvalue(&mutex, &value); 
printf("The value of the semaphors is %d\n", value);

  for (i=0; i<n; i++)
  {
    for (j=0; j<m; j++)
    {
     result[i][j]=a[i][j]+b[i][j];
    }
 }
 sem_post(&mutex);
 return 0;
}


void *writeToConsole(void *args)
{
sem_wait(&mutex);
int value; 
sem_getvalue(&mutex, &value); 
printf("The value of the semaphors is %d\n", value);

  printf("writing %d, %d\n", n, m);
  for (i=0; i<n; i++)
  {
    for (j=0; j<m; j++)
    {
     printf("%d ",result[i][j]);
    }
    printf("\n");
 }
 sem_post(&mutex);
 return 0; 
}


int main()
{
  pthread_t threads[3];
  sem_init(&mutex, 0, 1);
  // sem_wait(&mutex);
  pthread_create(&threads[0], NULL, readFromFile, NULL);
  // pthread_join(threads[0], NULL);

int value; 
sem_getvalue(&mutex, &value); 
printf("The value of the semaphors is %d\n", value);
  // sem_wait(&mutex);
  pthread_create(&threads[1], NULL, sumMatrices, NULL);
  // pthread_join(threads[1], NULL);
  // sem_wait(&mutex);
  pthread_create(&threads[2], NULL, writeToConsole, NULL);
  // pthread_join(threads[2], NULL);
  // sem_wait(&mutex);
  sem_destroy(&mutex);
  printf("hello\n");
  return 0;
}


