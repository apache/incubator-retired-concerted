#include "../ConcInvertedIndex.h"

int main()
	{
		inv_index<3,0> *index1;
		int att_values[3];
		int return_value;

		return_value = 0;
		index1 = new inv_index<3,0>;
		att_values[0] = 3;
		att_values[1] = 4;
		att_values[2] = 5;

		insert_val(att_values, index1);

		return_value = search_val(&(att_values[0]), index1);

		if (return_value == 1)
		{
			cout<<"values found"<<" "<<return_value<<endl;
		}
		else
		{
			cout<<"values not found"<<" "<<return_value<<endl;
		}

	}
