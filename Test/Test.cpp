#include "stdafx.h"

#include <iostream>
using namespace std;

#include <time.h>
int main()
{
	float test[12*3*3];
	srand((unsigned)time(NULL));
	for (int v = 0; v < 12*3 ; v++)
	{
		test[3*v+0] =(float) rand()/RAND_MAX;
		test[3*v+1] =(float) rand()/RAND_MAX;
		test[3*v+2] =(float) rand()/RAND_MAX;
		cout<<test[3*v]<<" "<<test[3*v+1]<<" "<<test[3*v+2]<<endl;
	}

	return 0;
}