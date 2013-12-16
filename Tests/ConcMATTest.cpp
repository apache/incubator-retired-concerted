#include "../ConcMAT.h"	

	int main()
	{
		int att_array[3];
		int i = 0;
		mat_tree *tree_val = NULL;
		tree_val = build_mattree(3);
		att_array[0] = 1;
		att_array[1] = 2;
		att_array[2] = 3;
		insert_val(att_array, tree_val);
		if (search_val(att_array, tree_val))
		{
			cout<<"All values found"<<endl;
		}
		else
		{
			cout<<"All values not found"<<endl;
		}

		delete tree_val;
	}

