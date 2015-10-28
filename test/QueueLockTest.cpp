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
#include<unistd.h>
#include "../include/QueueLock.h"

QueueLock GlobalQueueLock;
void *thread_getlock_start(void *arg1)
{
	GlobalQueueLock.GetLock((char*)arg1);
	cout<<"Lock acquired by"<<" "<<(char*)arg1<<endl;
	usleep(1);
	GlobalQueueLock.ReleaseLock((char*)arg1);
}

void testQueueLock()
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

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);
	pthread_join(tid5,NULL);
}

