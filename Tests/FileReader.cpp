#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "../ConcMAT.h"

using namespace std;

std::string line;
std::ifstream infile("sat.trn");

int main()
{
int count;
int arr_val[3];
mat_tree *tree_val = NULL;

tree_val = build_mattree(3);
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
		insert_val(arr_val, tree_val);
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
