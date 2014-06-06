#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define numberOfSteps 7
#define numberOfThreads 11

int threads[numberOfThreads][2] = { 
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

pthread_t tids[numberOfThreads];

struct thread_params
{
	int sleepTime;
};

void* thread_function(void* params)
{	
	struct thread_params* p = (struct thread_params*) params;
	sleep(p->sleepTime);
	return NULL;
}

int main ()
{
	for (int s = 0; s < numberOfSteps; ++s)
	{
		for (int t = 0; t < numberOfThreads; ++t)
		{
			if (threads[t][1] == s) {
				printf("Waiting for thread %d\n", t);
				pthread_join(tids[0], NULL);			
			}

			if (threads[t][0] == s) {
				pthread_t thread1_id;
				struct thread_params params;
				params.sleepTime = threads[t][1] - threads[t][0];
				pthread_create (&thread1_id, NULL, &thread_function, &params);
				printf("Created thread %d\n", t);
				tids[t] = thread1_id;
			}
		}
	}
	return 0;
}




