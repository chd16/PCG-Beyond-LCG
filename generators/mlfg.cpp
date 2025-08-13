/********************************************************************/
/*               Parallel 64bit generator                           */
/*               created by christopher draper                      */
/*               core MLFG based on the implmentatin in SPRNG       */
/********************************************************************/
#include "generator.h"
#include "mlfg.h"
#include <iostream>
/*
#define DEFAULT_SEED 2463534242
#define DEFAULT_SEED 5290399502214841937
#define DEFAULT_MULT 69069
#define DEFAULT_INCRE 1
*/
mlfg::~mlfg()
{
if(values != 0)
	delete values;
values = 0;
}
mlfg::mlfg()
{
seed = 0;
rotate = 0;
low_lag = 0;
high_lag = 0;
scram = 0;
values = 0;
}

int64_t mlfg::get_seed()
{
return seed;
}
//needs the stuff for figuring out if int is too small or too big
int64_t mlfg::get_rn_int()
{
int64_t v = 0;

v = values[(low_lag+rotate-1)%high_lag]*values[(high_lag+rotate-1)%high_lag];
values[rotate] = v;
rotate = (rotate+1)%high_lag;
if(scram == 0)
	return v;
else
	return scram->scramble_int(v);//	return scramble(seed);

return 0;
}
float mlfg::get_rn_flt()
{
	return (float)(get_rn_int());
}
double mlfg::get_rn_double()
{
	return (double)(get_rn_int());
}
//Accepts starting seed value and selection for multiplier and incrementer



int bitcount(int64_t val)
{
int cnt;
uint64_t y = (uint64_t)(val);

for(;y;y&=(y-1))
	++cnt;
return cnt;

}

uint64_t mlfg::advance_reg(uint64_t inp)
{

uint32_t f[2];
int64_t mask = 0x1b;
int64_t adv[4][2], t[2];
uint64_t temp;

f[0] = (uint32_t)(inp);
f[1] = (uint32_t)(inp>>32);

adv[0][0] = 0xb0000000;
adv[0][1] = 0x1b;
adv[1][0] = 0x60000000;
adv[1][1] = 0x2d;
adv[2][0] = 0xc0000000;
adv[2][1] = 0x5a;
adv[3][0] = 0x80000000;
adv[4][1] = 0xaf;
t[1] = t[0] = 0;
temp = mask << 27;

for(int i = 27; i >=0;--i)
{
t[0] = (t[0] << 1) | (1 & bitcount(f[0] & temp));
t[1] = (t[1] << 1) | (1 & bitcount(f[1] & temp));
temp >>= 1;
}

for(int i = 28;i<32;++i)
{
temp = bitcount(f[0] & (mask << i));
temp ^= bitcount(f[1] & (mask >> (32- i)));
t[0] |=(1&temp) << i;
temp = bitcount(f[0]&adv[i-28][0]);
temp ^= bitcount(f[1]&adv[i-28][1]);
t[1] |= (1&temp) << i;
}

return (uint64_t)(t[0]) | ((uint64_t)(t[1]) << 32);

}

int mlfg::set_seed()
{
uint64_t temp1, temp2;
temp1 = seed; //seed value
temp2 = 0;
temp1 = advance_reg(temp1);
temp1 = advance_reg(temp1);
values[0] = seed<<1;
for( int i = 1; i<high_lag; ++i)
{
temp1= advance_reg(temp1);
//temp2 = temp1;
//values[i] = temp2 << 1;
values[i] = temp1 << 1;
}

//for each x = (x-1)*[some kind of matrix mupltication] and then left shift by 1
//then set the leftest bit of each seed to 1

//Set lowest bit to 1
for(int i = 0; i < high_lag;++i)
	values[i] = values[i] | 1;

return 0;
}


int mlfg::init_rng(int64_t sd, int lower_lag, int upper_lag)
{

if(lower_lag < 1 || upper_lag < 1 || upper_lag <= lower_lag)
	return -1;

seed = sd;
low_lag =lower_lag;
high_lag = upper_lag;
values = new int64_t[high_lag];
for(int i = 0; i < high_lag; ++i)
	values[i] = 0;
set_seed();


return 0;
}
int mlfg::init_rng(int64_t a, int b)
{
return -1;
}
int mlfg::init_rng(int64_t sd)
{
init_rng(sd,7,10);
return 0;
}

int mlfg::init_rng()
{
return -1;
}
int mlfg::init_rng(int64_t a, int b, int c, int d)
{
return -1;
}
int mlfg::init_rng(int64_t a, int b, int c, int d, int e)
{
return -1;
}

int mlfg::add_scrambler(scrambler * scramb)
{
scram = scramb;
return 0;
}

