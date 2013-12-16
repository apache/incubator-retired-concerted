#include "../ConcSegHashTable.h"

ConcSegHashTable<int> tab1(10,2);
void *thread_lock_test(void *arg1)
{
	//tab1.GetWriteLock(0,2,(char*)arg1);
	//tab1.InsertElement(5, false, (char*)arg1);
	if((tab1.InsertElement(5, false,(char*)arg1)) == 0)
	{
		cout<<"Value not inserted"<<" "<<(char*)arg1<<" "<<5<<endl;
		sleep(1);
	}

	tab1.InsertElement(6, false,(char*)arg1);
	//tab1.InsertElement(5, false,(char*)arg1);
	//tab1.InsertElement(5, false,(char*)arg1);
	//cout<<"read lock with"<<" "<<(char*)arg1<<endl;
	//sleep(1);
	//tab1.ReleaseWriteLock(0,2,(char*)arg1);
	//cout<<"read lock released by"<<" "<<(char*)arg1<<endl;
}

void *thread_lock_test2(void *arg1)
{
	//tab1.GetWriteLock(0,2, (char*)arg1);
	//cout<<"write lock with"<<" "<<(char*)arg1<<endl;
	//tab1.ReleaseWriteLock(0,2, (char*)arg1);
	//cout<<"write lock released by"<<" "<<(char*)arg1<<endl;
	if((tab1.InsertElement(5, false, (char*)arg1)) == 0)
	{
		cout<<"Value not inserted"<<" "<<(char*)arg1<<" "<<5<<endl;
		sleep(1);
	}

	if((tab1.InsertElement(6, false, (char*)arg1)) == 0)
	{
		cout<<"Value not inserted"<<" "<<(char*)arg1<<" "<<6<<endl;
		sleep(1);
	}
}

void *thread_lock_test3(void *arg1)
{
	/*tab1.GetReadLock(0,2, (char*)arg1);
	cout<<"read lock with"<<" "<<(char*)arg1<<endl;
	tab1.ReleaseReadLock(0,2, (char*)arg1);
	cout<<"read lock released by"<<" "<<(char*)arg1<<endl;*/
	if((tab1.InsertElement(6, false, (char*)arg1)) == 0)
	{
		cout<<"Value not inserted"<<" "<<(char*)arg1<<" "<<6<<endl;
	}

	//tab1.InsertElement(6, false, (char*)arg1);
}

void *thread_lock_test4(void *arg1)
{
	tab1.InsertElement(6,false,(char*)arg1);
	tab1.InsertElement(9,false,(char*)arg1);
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_t tid4;
	char name1[] = "thread1";
	char name2[] = "thread2";
	char name3[] = "thread3";
	char name4[] = "thread4";

	pthread_create(&tid1,NULL,thread_lock_test,(void*)name1);
	pthread_create(&tid2,NULL,thread_lock_test2,(void*)name2);
	pthread_create(&tid3,NULL,thread_lock_test3,(void*)name3);
	pthread_create(&tid4,NULL,thread_lock_test4,(void*)name4);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);

	tab1.PrintValues();

	//tab1.GetWriteLock(2,3);
	//tab1.ReleaseWriteLock(2,3);
}
