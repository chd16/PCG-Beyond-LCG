#include "pcg_fixed_xorshift.h"
#ifndef NULL
#define NULL 0
#endif

#include <iostream>
using namespace std;
//used for adding rng 
int fixed_xors::init_add_gen(int64_t (*gener)())
{
if(*gener == 0){
	return -1;}
func = gener;
return 0;
}


//Return error on the ones that aren't the correct number of inputs
int fixed_xors::init_scrambler()
{
return -1;
}

int fixed_xors::init_scrambler(int a)
{
return -1;
}
//The bit length of the generator, length of the bits to shift,
//Cannot have the shift length be equal too or greater than the total length of the generator
//Does allow there to be overlap on the bits being used for the xor and the bits
//being xor-ed upon
int fixed_xors::init_scrambler(int bit, int ixor)
{
if(ixor >= bit)
	return -1;

bits = bit;
xors = ixor;
return 0;
}

int fixed_xors::init_scrambler(int a, int b, int c)
{
return -1;
}
int fixed_xors::init_scrambler(int a, int b, int c, int d)
{
return -1;
}



//Uses the top xors bit to xor onto the bottom xor bits
//Use bits-xors to determine the total shift and
uint64_t fixed_xors::scramble_int(uint64_t rn)
{
uint64_t rns = rn;

//cout << "rns: " << rns << "\tbits-xors: " << bits-xors << "\trns>>prev: ";
//cout << (rns >> (bits-xors)) << "\tprev^rns: " << ((rns >> (bits-xors))^rns) << endl;
return (int64_t)((rns >> (bits-xors))^rns);
}

double fixed_xors::scramble_double(double)
{
return 0;
}

float fixed_xors::scramble_flt(float)
{
return 0;
}
