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
#include "../include/ConcDCT.h"
	int main()
	{
		int att_array[3];
		int i = 0;
		TransactionManager transact_val1;
		dct_tree *tree_val = NULL;
		dct_tree *tree_val2 = NULL;
		dct_tree *tree_val3 = NULL;
		dct_node *temp = NULL;
		tree_val = build_dcttree(3);
		tree_val3 = build_dcttree(3);
		att_array[0] = 1;
		att_array[1] = 2;
		att_array[2] = 3;
		try
		{
			insert_val(att_array, tree_val, transact_val1);
			insert_val(att_array, tree_val3, transact_val1);
			//throw -1;
			transact_val1.commit_transaction();
			tree_val2 = copy_val((tree_val->getdummy()), (tree_val->getnumber_of_nodes()));
		}catch (int e)
		{
			cout<<"exception caught"<<" "<<e<<endl;
			return 1;
		}

		//att_array[2] = 3;
		if (search_val(att_array, tree_val))
		{
			cout<<"All values found"<<endl;
		}
		else
		{
			cout<<"All values not found"<<endl;
		}

		temp = search_val(att_array, tree_val2);
		if (temp != NULL)
		{
			cout<<" All values found copy tree"<<endl;
		}
		else
		{
			cout<<"All values not found copy tree"<<endl;
		}

		if (search_val(att_array, tree_val3))
		{
			cout<<"All values found3"<<endl;
		}
		else
		{
			cout<<"All values not found3"<<endl;
		}

		delete tree_val;
		delete tree_val2;
		delete tree_val3;
		delete temp;
	}
