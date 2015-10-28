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
#include "../ConcDCT.h"

	void *thread_lock_test1(void *arg1)
	{
		dct_tree *tree_val = (dct_tree*)arg1;
		int arr_val[3];

		arr_val[0] = 1;
		arr_val[1] = 2;
		arr_val[2] = 3;

		insert_val(arr_val, tree_val);
	}

	void *thread_lock_test2(void *arg1)
	{
		dct_tree *tree_val = (dct_tree*)arg1;
		int arr_val[3];

		arr_val[0] = 4;
		arr_val[1] = 5;
		arr_val[2] = 6;

		insert_val(arr_val, tree_val);
	}

	void *thread_lock_test3(void *arg1)
	{
		dct_tree *tree_val = (dct_tree*)arg1;
		int arr_val[3];

		arr_val[0] = 1;
		arr_val[1] = 2;
		arr_val[2] = 3;

		insert_val(arr_val, tree_val);
	}

	void *thread_lock_test4(void *arg1)
	{
		dct_tree *tree_val = (dct_tree*)arg1;
		int arr_val[3];

		arr_val[0] = 4;
		arr_val[1] = 5;
		arr_val[2] = 6;

		search_val(arr_val, tree_val);
	}
		
	int main()
	{
	dct_tree *tree_val = NULL;
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;
	pthread_t tid4;

	tree_val = new dct_tree(3);

	pthread_create(&tid1,NULL,thread_lock_test1,(void*)tree_val);
	pthread_create(&tid2,NULL,thread_lock_test2,(void*)tree_val);
	pthread_create(&tid3,NULL,thread_lock_test3,(void*)tree_val);
	pthread_create(&tid4,NULL,thread_lock_test4,(void*)tree_val);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid4,NULL);
	}

	
