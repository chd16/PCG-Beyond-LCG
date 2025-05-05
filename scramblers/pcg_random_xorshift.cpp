#include "pcg_random_xorshift.h"
#ifndef NULL
#define NULL 0
#endif

//#include <iostream>
//using namespace std;

//used for adding rng 
int rand_xor::init_add_gen(int64_t (*gener)())
{
if(*gener == 0){
	return -1;}
func = gener;
return 0;
}


//Return error on the ones that aren't the correct number of inputs
int rand_xor::init_scrambler()
{
return -1;
}
int rand_xor::init_scrambler(int a)
{
return -1;
}

//Amount of bits in the generator, amount of bits used to determine xorshift
int rand_xor::init_scrambler(int bit, int ixor)
{
bits = bit;
xors = ixor;

//Once again does not make much sense for these values to be less than 1
if(bits <= 0 || ixor <= 0)
	return -1;
//Can't use more bits than are avaliable in the xor
if(bits < (1<<ixor))
	return -1;

return 0;
}
int rand_xor::init_scrambler(int a, int b, int c)
{
return -1;
}




uint64_t rand_xor::scramble_int(uint64_t rn)
{
uint64_t rns = rn;
/*
cout << "rns: " << rns;
cout << "\tbits-xors: " << bits-xors << "\trns>>prev: " << (rns>>(bits-xors));
cout << "\tbits-prev: " << (bits-(rns>>(bits-xors))) << "\trns>>prev: " << (rns >> (bits-(rns>>(bits-xors))));
cout << "\tFinal: " << ((int64_t)((rns >> (bits - (rns >> ( bits - xors)))) ^ rns)) << endl;
*/

//When rns>>(bits-xors) == bits system will not shift rns>>bits for result 0, but instead just returns rns which returns 0 in error
if ((rns>>(bits-xors)) == 0)
	return (int64_t)(rns);

return (int64_t)((rns >> (bits - (rns >> ( bits - xors)))) ^ rns);
}

double rand_xor::scramble_double(double)
{
return 0;
}

float rand_xor::scramble_flt(float)
{
return 0;
}
int rand_xor::init_scrambler(int a, int b, int c, int d)
{
return -1;
}

