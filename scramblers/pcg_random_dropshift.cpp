#include "pcg_random_dropshift.h"
#ifndef NULL
#define NULL 0
#endif

#include <iostream>
//used for adding rng 
int db_rs::init_add_gen(int64_t (*gener)())
{
if(*gener == 0){
	return -1;}
func = gener;
return 0;
}


//Size of generator, number of bits to select drop, target length of output
int db_rs::init_scrambler(int bit, int drop, int shift, int target)
{
//std::cout << bit << " " << drop << " " << shift << " " << target << std::endl;
//Cannot reac target bit length greater than current bit length
if ((bit-drop) < target)
	return -1;
//Does not really work if any of these values are 0
if(bit <= 0 || target <= 0 || drop <= 0 || shift < 0)
	return -1;

//If bit-target-drop < 2^drop then there is a chance to shift more than 'bit' bits
//Which throws errors and is a bad scrambler
//std::cout << bit-target-drop << "<" << (1<<drop) << std::endl;
if( (bit - target - drop - shift) < (1<<drop))
	return -1;


bits = bit;
drops = drop;
targets = target;
shifts = shift;
mask = 1;
masku = 1;
//Mask for the target output
for(int i = 0; i < targets-1; ++i)
{
mask = mask | (mask << 1);
}
//Mask to remove the bits used in the drop
for(int i = 0; i < (bit-drop-1); ++i)
	masku=masku | (masku<<1);
//std::cout << "past init" << std::endl;
//std::cout << targets - drops << " " << bits-drops << " " << mask << std::endl;
return 0;
}

uint64_t db_rs::scramble_int(uint64_t rn)
{
//rns&masku: removes the bits that determine the drop
//targets-drops: removes the bits used in determining the drop from the output and sets the max drop
//bits-drops: selects the bits used in the drops
uint64_t rns = rn;

//Testing output
/*
std::cout << "scrambling" << std::endl;
std::cout << "rn: "<< rns <<" bits to drop: ";
std::cout << (rns >> (bits-drops)) << " total dropped: ";
std::cout << (bits- targets - drops) - (rns >> (bits-drops)) << " output: ";
std::cout << (rns >> ((bits- targets - drops) - (rns >> (bits-drops)))) << " masked output: ";
std::cout << ((rns >> ((bits-targets - drops) - (rns >> (bits-drops)))) & mask) <<std::endl;
*/
return (((rns&masku) >> ((bits - targets - drops-shifts) - (rns >> (bits-drops)))) & mask);
}

double db_rs::scramble_double(double)
{
return 0;
}

float db_rs::scramble_flt(float)
{
return 0;
}








int db_rs::init_scrambler()
{
return -1;
}

int db_rs::init_scrambler(int a)
{
return -1;
}
int db_rs::init_scrambler(int bit, int drop, int shift)
{
//std::cout << bit << " " << drop  << " " <<shift << " " << (bit-drop-(1<<drop)) <<std::endl;


return init_scrambler(bit,drop,shift,bit-drop-(1<<drop));
}

int db_rs::init_scrambler(int a, int b)
{
return -1;
}
