#include "lk_hash.h"
#ifndef NULL
#define NULL 0
#endif
//#include <iostream>
//using namespace std;
int lk_hash::init_add_gen(int64_t (*gener)())
{
if(*gener == 0){
	return -1;}
func = gener;
return 0;
}

uint64_t lk_hash::scramble_int(uint64_t rn)
{
int64_t seed = func();
//cout << "Seed and rn: " << seed << " " << rn << endl;
rn ^= rn * 0x3d20adea;
rn += seed;
rn *= (seed >> 16) | 1;
rn ^= rn * 0x05526c56;
rn ^= rn * 0x53a22864;
//cout << "End val " << rn << endl;
return rn;
}

double lk_hash::scramble_double(double)
{
return 0;
}

float lk_hash::scramble_flt(float)
{
return 0;
}




int lk_hash::init_scrambler()
{
return -1;
}

int lk_hash::init_scrambler(int a)
{
return -1;
}
int lk_hash::init_scrambler(int a, int b)
{
return -1;
}
int lk_hash::init_scrambler(int a, int b, int c)
{
return -1;
}
int lk_hash::init_scrambler(int a, int b, int c, int d)
{
return -1;
}

