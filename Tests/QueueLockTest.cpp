#include<unistd.h>
#include "QueueLock.h"

QueueLock GlobalQueueLock;
void *thread_getlock_start(void *arg1)
{
	GlobalQueueLock.GetLock();
	cout<<"Lock acquired by"<<" "<<(char*)arg1<<endl;
	usleep(1);
	GlobalQueueLock.ReleaseLock();
}

int main()
{
	int data_value = 5;
	QueueLock lock1;
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_t tid4;
	pthread_t tid5;
	pthread_t tid6;
	pthread_t tid7;
	char name1[] = "thread1";
	char name2[] = "thread2";
	char name3[] = "thread3";
	char name4[] = "thread4";
	char name5[] = "thread5";

	pthread_create(&tid1,NULL,thread_getlock_start,(void*)(name1));
	pthread_create(&tid2,NULL,thread_getlock_start,(void*)(name2));
	pthread_create(&tid3,NULL,thread_getlock_start,(void*)(name3));
	pthread_create(&tid4,NULL,thread_getlock_start,(void*)(name4));
	pthread_create(&tid5,NULL,thread_getlock_start,(void*)(name5));
	

	//cout<<"pid of thread1 is"<<" "<<tid1<<endl;
	//cout<<"pid of thread2 is"<<" "<<tid2<<endl;
	//cout<<"pid of thread3 is"<<" "<<tid3<<endl;

	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);
	pthread_join(tid5,NULL);
}
	

