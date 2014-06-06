#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <stdio.h>     /* printf, perror */
#include <stdlib.h>    /* exit */
#include <unistd.h>    /* _exit, fork */
#include <pthread.h>

#define numberOfSteps 7
#define numberOfProcesses 11

int main() {
   int isTrunk[numberOfProcesses] = {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};
   int processes[numberOfProcesses][2] = { 
      {0, 1}, // 0
      {1, 2}, // 1
      {2, 3}, // 2
      {3, 4}, // 3
      {4, 5}, // 4
      {5, 6}, // 5
      {1, 3}, // 6
      {1, 4}, // 7
      {1, 5}, // 8
      {2, 6}, // 9
      {5, 6}  // 10
   };

   pid_t pids[numberOfProcesses];
   
   /* Fork root process. */
   pids[0] = fork();

   /* Only for child of main process */
   if (pids[0] == 0) {
      pids[0] = getpid();
      
      for (int step = 1; step < numberOfSteps; ++step)
      {
         if (getpid() == pids[step - 1]) {
            printf("---- running process (step = %d)\n", step);
            for (int i = numberOfProcesses - 1; i >= 0; --i)
            {
               if (processes[i][0] == step) {
                  printf("forked process from %d to %d\n", processes[i][0], processes[i][1]);
                  sleep(1/10);
                  pids[i] = fork();
                  printf("process from %d to %d, pid = %d, ppid = %d\n", processes[i][0], processes[i][1], getpid(), getppid());
                  if (pids[i] == 0) {
                     if (processes[i][1] == (step + 1)) {
                        pids[i] = getpid();
                        for (int p = 0; p < numberOfProcesses; ++p)
                        {
                           if (processes[p][1] == step) {
                              printf("wainting for pid = %d\n", pids[p]);
                              waitpid(pids[p], NULL, 0);
                           }
                        }
                        i = -1;
                     } else {
                        sleep((processes[i][1] - processes[i][0]) / 10);
                        return 0;
                     }
                  }
               }
            }
         }
      }

   } else {
      waitpid(pids[0], NULL, 0);
      
   }
   return 0;
}
