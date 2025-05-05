#include "fixed_dropshift.h"
#ifndef NULL
#define NULL 0
#endif
#include <iostream>
using namespace std;
//used for adding rng 
int fixed_dropshift::init_add_gen(int64_t (*gener)())
{
if(*gener == 0){
	return -1;}
func = gener;
return 0;
}


//Return error on the ones that aren't the correct number of inputs
int fixed_dropshift::init_scrambler()
{
return -1;
}

int fixed_dropshift::init_scrambler(int a)
{
return -1;
}
int fixed_dropshift::init_scrambler(int bits, int targets)
{
if(bits < 0 || targets < 0 || bits <= targets)
	return -1;
bit = bits;
target = targets;
shift = bit - target;

return 0;
}
int fixed_dropshift::init_scrambler(int a, int b, int c)
{
return -1;
}




uint64_t fixed_dropshift::scramble_int(uint64_t rn)
{
return rn >> shift;
}

double fixed_dropshift::scramble_double(double)
{
return 0;
}

float fixed_dropshift::scramble_flt(float)
{
return 0;
}
int fixed_dropshift::init_scrambler(int a, int b, int c, int d)
{
return -1;
}

