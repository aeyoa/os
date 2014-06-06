#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

#define max 10

int i, j;

int main() 
{
 int *shared_array;
 int id;
 char pathname[] = "part1.c";
 key_t key;

 key = ftok(pathname, 0);
 if ((id = shmget(key,(3*max*max+2)*sizeof(int),0666|IPC_CREAT|IPC_EXCL)) < 0) 
 {
  id = shmget(key, (3*max*max+2)*sizeof(int), 0); 
 }
 shared_array = (int*)shmat(id, NULL, 0);
 

 pid_t process;
 process = fork();

 /* Reading */
 if (process ==0)
 {
  freopen("in.txt", "r", stdin);
  scanf("%d %d\n", &shared_array[0], &shared_array[1]);
  int n = shared_array[0];
  int m = shared_array[1];
  for (i=2;i<2*n*m+2;i++)
   {
    scanf("%d", &shared_array[i]);
   }
  return 0;
 }
 waitpid(process, NULL, 0);

 /* Summing */
 process = fork(); 
 if (process == 0)
 {
  int n = shared_array[0];
  int m = shared_array[1];
  for (i=0;i<n;i++)
  {
   for (j=0;j<m;j++)
   {
    shared_array[2+2*n*m+i*m+j] = shared_array[2+m*i+j] + shared_array[2+m*n+m*i+j];
   }
  }
  return 0;
 }
 waitpid(process, NULL, 0);

 /* Printing */
 process = fork();
 if (process == 0)
   {
    int n = shared_array[0];
    int m = shared_array[1];
    for (i=0; i < n; i++)
    {
     for (j=0; j < m; j++)
     {
      printf("%d ",shared_array[2+2*n*m+i*m+j]);
     }
     printf("\n");
    }
    return 0;
 }
 waitpid(process, NULL, 0);
 return 0;
}
