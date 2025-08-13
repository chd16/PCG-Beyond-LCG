/********************************************************************/
/*               Parallel 64bit generator                           */
/*               created by christopher draper                      */
/********************************************************************/
#include "generator.h"
#include "lcg.h"
//#include <iostream>
//max 48 bit value
#define MOD_VAL 0x0FFF
/*
#define DEFAULT_SEED 2463534242
#define DEFAULT_SEED 5290399502214841937
#define DEFAULT_MULT 69069
#define DEFAULT_INCRE 1
*/

//const int[][] = {}

LCG::LCG()
{
seed = 0;
incrementer = 0;
multiplier = 0;
scram = 0;
default_seed = 5290399502214841937;
//default_mult = 69069;
//default_incre = 1;
default_mult = 2862933555777941757;
default_incre = 3037000493;
}

int64_t LCG::get_seed()
{
return seed;
}
//needs the stuff for figuring out if int is too small or too big
int64_t LCG::get_rn_int()
{
val = (multiplier*val+incrementer);

if(scram == 0)
	return val;
else
	return scram->scramble_int(val);//	return scramble(seed);

}
float LCG::get_rn_flt()
{
	return (float)(get_rn_int());
}
double LCG::get_rn_double()
{
	return (double)(get_rn_int());
}
//Accepts starting seed value and selection for multiplier and incrementer



int LCG::init_rng(int64_t sd, int mult, int incre)
{
val = seed =sd;
incrementer = incre;
multiplier = mult;
return 0;
}
//uses preset multiplier and incrementer value
int LCG::init_rng(int64_t sd)
{
return init_rng(sd, default_mult,default_incre);
}

int LCG::init_rng()
{
return init_rng(default_seed,default_mult,default_incre);
}

int LCG::add_scrambler(scrambler * scramb)
{
scram = scramb;
return 0;
}

int LCG::init_rng(int64_t a, int b)
{
return -1;
}
int LCG::init_rng(int64_t a, int b,int c,int d)
{
return -1;
}
int LCG::init_rng(int64_t a, int b, int c, int d, int e)
{
return -1;
}

