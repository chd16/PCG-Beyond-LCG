#include "constant_multiplier.h"
#ifndef NULL
#define NULL 0
#endif

//used for adding rng 
int constant_multiplier::init_add_gen(int64_t (*gener)())
{
if(*gener == 0){
	return -1;}
func = gener;
return 0;
}


//Return error on the ones that aren't the correct number of inputs
int constant_multiplier::init_scrambler()
{
return -1;
}

int constant_multiplier::init_scrambler(int a)
{
if(a <= 0 || a >64)
	return -1;

mask = 1;
--a;
while(a!=0)
	{mask = mask<<1|mask;--a;}


return 0;
}
int constant_multiplier::init_scrambler(int a, int b)
{
return -1;
}
int constant_multiplier::init_scrambler(int a, int b, int c)
{
return -1;
}




uint64_t constant_multiplier::scramble_int(uint64_t rn)
{
return (rn*mult)&mask;
}

double constant_multiplier::scramble_double(double)
{
return 0;
}

float constant_multiplier::scramble_flt(float)
{
return 0;
}
int constant_multiplier::init_scrambler(int a, int b, int c, int d)
{
return -1;
}

