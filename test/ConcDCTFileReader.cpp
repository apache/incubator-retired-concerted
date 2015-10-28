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
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "../include/ConcDCT.h"

using namespace std;

std::string line;
std::ifstream infile("sat.trn");

int main()
{
int count;
int arr_val[3];
dct_tree *tree_val = NULL;
TransactionManager t1;
		
tree_val = build_dcttree(3);
count = 0;
while (std::getline(infile, line))  // this does the checking!
{
  std::istringstream iss(line);
  char c;

   int value;
  while (iss >> value)
  {
	if (count == 3)
	{
		insert_val(arr_val, tree_val, t1);
		count = 0;
		cout<<"record"<<endl;
	}

	arr_val[count] = value;
	++count;
  }
}

arr_val[0] = 91;
arr_val[1] = 100;
arr_val[2] = 81;

if ((search_val(arr_val, tree_val)) != NULL)
		{
			cout<<"All values found"<<endl;
		}
		else
		{
			cout<<"All values not found"<<endl;
		}
}
