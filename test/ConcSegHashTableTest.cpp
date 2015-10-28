/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to you under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "../include/ConcSegHashTable.h"

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

int testSegHashTable(int debugValue)
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

	if (debugValue > 0)
	  tab1.PrintValues();
}
