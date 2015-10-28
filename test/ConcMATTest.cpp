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
#include "../include/ConcMAT.h"

	int testMAT(int debugValue)
	{
		int att_array[3];
		int i = 0;
		int numberOfTestsPassed;
		int numberOfTestsFailed;
		mat_tree *tree_val = NULL;

		numberOfTestsPassed = 0;
		numberOfTestsFailed = 0;
		tree_val = build_mattree(3);
		att_array[0] = 1;
		att_array[1] = 2;
		att_array[2] = 3;
		insert_val(att_array, tree_val);
		if (search_val(att_array, tree_val))
		{
		  if (debugValue > 0)
		    cout<<"All values found"<<endl;

		  ++numberOfTestsPassed;
		}
		else
		{
		  if (debugValue > 0)
		    cout<<"All values not found"<<endl;

		  ++numberOfTestsFailed;
		}

		delete tree_val;

		return numberOfTestsFailed;
	}

