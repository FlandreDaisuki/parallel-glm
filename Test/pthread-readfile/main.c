#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define THREAD_COUNT 4

/*
char *fgets(char *str, int num, FILE *stream)
	put '\n' as a valid char and put into str

size_t strlen(const char *str)
	return the number before '\0'
	view '\n' as 1 char
*/

typedef struct _arg_t
{
	char filename[50];
	int thread_id;
} arg_t;

arg_t args[THREAD_COUNT];

void *worker(void *threadarg)
{
	arg_t *arg;
	arg = (arg_t *)threadarg;

	int thread_id = arg->thread_id;
	FILE *fp = fopen(arg->filename, "r");
	char useless[200];
	char buf[200];
	for (int i = 0; i < thread_id; ++i)
	{
		fgets(useless, sizeof(useless), fp);
	}
	while (fgets(buf, sizeof(buf), fp) != NULL)
	{
		if(buf[strlen(buf)-1] == '\n') {
			buf[strlen(buf)-1] = '\0';
		}
		printf("[%d] %s\n", thread_id, buf);

		/* jump next thread_id-1 lines */
		for (int i = 0; i < THREAD_COUNT - 1; ++i)
		{
			fgets(useless, sizeof(useless), fp);
		}
	}
}

int main(int argc, char const *argv[])
{
	pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * THREAD_COUNT);

	char filename[50];
	strcpy(filename, argv[1]);
	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		strcpy(args[i].filename, filename);
		args[i].thread_id = i;
		if (pthread_create(&threads[i], NULL, worker, (void *)&(args[i])) != 0)
		{
			printf("pthread_create fail\n");
		}
	}
	for (int i = 0; i < THREAD_COUNT; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	printf("print after join\n");

	return 0;
}