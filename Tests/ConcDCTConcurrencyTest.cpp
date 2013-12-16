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

	
