#include "generator.h"
#include "[name].h"


[name]::[name]()
{
 seed =0;
 val =0;
 scram =0;

int64_t default_seed =0;
}

int64_t [name]::get_seed()
{
return seed;
}
int64_t [name]::get_rn_int()
{

if(scram == 0)
	return val;
else
	return scram->scramble_int(val);

}
float [name]::get_rn_flt()
{
	return (float)(get_rn_int());
}
double [name]::get_rn_double()
{
	return (double)(get_rn_int());
}


int [name]::init_rng()
{
return -1;
}

int [name]::add_scrambler(scrambler * scramb)
{
scram = scramb;
return 0;
}

int [name]::init_rng(int64_t a)
{
return -1;
}
int [name]::init_rng(int64_t a, int b)
{
return -1;
}
int [name]::init_rng(int64_t a, int b, int c)
{
return -1;
}
int [name]::init_rng(int64_t a, int b,int c,int d)
{
return -1;
}
int [name]::init_rng(int64_t a, int b, int c, int d, int e)
{
return -1;
}

