#include <iostream>
using namespace std;

class ConcertedDef
{
public:
	virtual void copy_pointer_val(ConcertedDef *copy_val1)
	{
		cout<<"in ConcertedDef copy_pointer_val"<<endl;
	}
};
