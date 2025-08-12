#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
int x;

void* prvaNit(void* a)
{
	pthread_mutex_lock(&mutex);

	printf("Nit 1 je otpocela\n");

	while(x<30)
	{
		pthread_cond_wait(&cond,&mutex);
	}

	printf("Nit 1 je dobila koriscenje nakon primanja signala\n");

	pthread_mutex_unlock(&mutex);

}

void* drugaNit(void* a)
{
	pthread_mutex_lock(&mutex);

	printf("Druga nit krece\n");

	while(x < 60)
	{
		x++;
		if(x == 30)
		{
			printf("Druga nit je stigla do 30\n");
			pthread_cond_signal(&cond);
		}
		printf("Druga nit : x = %d\n", x);
	}

	printf("Druga zavrsava\n");
	pthread_mutex_unlock(&mutex);
}


int main()
{
	pthread_t t1,t2;
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&cond,NULL);

	pthread_create(&t1, NULL, prvaNit, NULL);
	sleep(3);
	pthread_create(&t2, NULL, drugaNit, NULL);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
return 0;
}
