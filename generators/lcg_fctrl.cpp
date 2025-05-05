/********************************************************************/
/*               Parallel 32bit generator                           */
/*               created by christopher draper                      */
/********************************************************************/
#include "generator.h"
#include "lcg_fctrl.h"
#include <iostream>
using namespace std;
//max 48 bit value
#define MOD_VAL 0x0FFF
/*
#define DEFAULT_SEED 2463534242
#define DEFAULT_SEED 5290399502214841937
#define DEFAULT_MULT 69069
#define DEFAULT_INCRE 1
*/
#include <iostream>
using namespace std;

lcg_fctrl::lcg_fctrl()
{
seed = 0;
val = 0;
mult = con = mod = 0;
scram = 0;
}

int64_t lcg_fctrl::get_seed()
{
return seed;
}
//needs the stuff for figuring out if int is too small or too big
int64_t lcg_fctrl::get_rn_int()
{

val = (mult*val+con)%mod;

if(scram == 0)
	return val;
else
	return scram->scramble_int(val);//	return scramble(seed);

}
float lcg_fctrl::get_rn_flt()
{
	return (float)(get_rn_int());
}
double lcg_fctrl::get_rn_double()
{
	return (double)(get_rn_int());
}
//Accepts starting seed value and selection for multiplier and incrementer



int lcg_fctrl::init_rng(int64_t a, int b, int c)
{
return -1;
}

int lcg_fctrl::init_rng(int64_t a)
{
return -1;
}

int lcg_fctrl::init_rng()
{
return -1;
}

int lcg_fctrl::add_scrambler(scrambler * scramb)
{
scram = scramb;
return 0;
}

int lcg_fctrl::init_rng(int64_t sd, int sel)
{
if (sel < 0 || sel > 37)
return -1;
mult = lcg_values[sel][0];
con = lcg_values[sel][1];
mod = lcg_values[sel][2];
seed = val = sd;
return 0;
}
int lcg_fctrl::init_rng(int64_t a, int m, int c, int d)
{
return -1;
}
int lcg_fctrl::init_rng(int64_t a, int m, int c, int d, int e)
{
return -1;
}

