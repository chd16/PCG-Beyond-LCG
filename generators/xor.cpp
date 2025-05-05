/********************************************************************/
/*               	  xor 64bit generator                       */
/*               created by christopher draper                      */
/********************************************************************/

/*
static unsigned int y = 2463534242U;

unsigned int xorshift (void)
{
y ^= (y << 13);
y ^=(y >> 17);
return y ^=(y <<5);

}

//Xorshift 32
static unsigned int x = 2463534242U;

unsigned int xorshifts (void)
{
x ^= (x << 13);
x ^=(x >> 17);
return ui_scrambler( x ^=(x <<5) );

}

*/


#include "xor.h"

//#include <iostream>
//using namespace std;

//max 64 bit value
#define MOD_VAL 0xFFFF
//#define DEFAULT_SEED 2463534242
#define DEFAULT_SEED 246353424212421
#define DEFAULT_SHIFT_1 13
#define DEFAULT_SHIFT_2 17
#define DEFAULT_SHIFT_3 5

XOR::XOR()
{
seed = 0;
shift1 = 0;
shift2 = 0;
shift3 = 0;
val = 0;
scram = 0;
}

int64_t XOR::get_seed()
{
return seed;
}

//needs the stuff for figuring out if int is too small or too big
int64_t XOR::get_rn_int()
{
val ^= (val << shift1);
val ^=(val >> shift2);
val ^=(val << shift3);


//cout << "XOR " << val << endl;
if(scram == 0)
	return val;
else
	return scram->scramble_int(val);
//	return scramb(val);

}

float XOR::get_rn_flt()
{
	return (float)(get_rn_int());
}

double XOR::get_rn_double()
{
	return (double)(get_rn_int());
}




int XOR::init_rng(int64_t sd, int s1, int s2, int s3)
{
seed =sd;
shift1=s1;
shift2=s2;
shift3=s3;
val = seed;
return 0;
}
int XOR::init_rng(int64_t sd)
{
return init_rng(sd, DEFAULT_SHIFT_1,DEFAULT_SHIFT_2,DEFAULT_SHIFT_3);
}

int XOR::init_rng()
{
return init_rng(DEFAULT_SEED, DEFAULT_SHIFT_1,DEFAULT_SHIFT_2,DEFAULT_SHIFT_3);
}

int XOR::init_rng(int64_t sd, int sel)
{
if(sel < 0 || sel > MAX_SEL_XOR)
	return -1;

return init_rng(sd,xor_values[sel][0],xor_values[sel][1],xor_values[sel][2]);

}
int XOR::init_rng(int64_t a, int b, int c)
{
return -1;
}
int XOR::init_rng(int64_t a, int b, int c, int d, int e)
{
return -1;
}

int XOR::add_scrambler(scrambler * scrambs)
{
scram = scrambs;
return 0;
}

