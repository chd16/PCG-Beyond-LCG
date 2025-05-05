#include "select_gen.h"
#include <iostream>
using namespace std;

generator* select_generator(int type)
{
generator * temp;

switch (type)
{
case 0:
	temp = new LCG;
	break;
case 1:
	temp = new XOR;
	break;
case 2:
	temp = new mlfg;
	break;
case 3:
	temp = new lcg_fctrl;
	break;
case 4:
	temp = new MT;
	break;
default:
	return 0;
}

if (temp==0)
{
cout << "error allocating data" << endl;
return 0;
}

return temp;

}
