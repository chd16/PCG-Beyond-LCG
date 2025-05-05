#include "[name].h"
#ifndef NULL
#define NULL 0
#endif

//used for adding rng 
int [name]::init_add_gen(int64_t (*gener)())
{
if(*gener == 0){
	return -1;}
func = gener;
return 0;
}


//Return error on the ones that aren't the correct number of inputs
int [name]::init_scrambler()
{
return -1;
}

int [name]::init_scrambler(int a)
{
return -1;
}
int [name]::init_scrambler(int a, int b)
{
return -1;
}
int [name]::init_scrambler(int a, int b, int c)
{
return -1;
}
int [name]::init_scrambler(int a, int b, int c, int d)
{
return -1;
}




uint64_t [name]::scramble_int(uint64_t rn)
{
return rn;
}

double [name]::scramble_double(double)
{
return 0;
}

float [name]::scramble_flt(float)
{
return 0;
}
