#include "pcg_random_rotate.h"
#ifndef NULL
#define NULL 0
#endif

//

#include <iostream>
using namespace std;
//Unused in this scrambler
int rr::init_add_gen(int64_t (*gener)())
{
/*
if(*gener == 0){
	return -1;}
func = gener;
*/return -1;
}


//Size of generator, number of bits used to determin rotation,
//The highest order bits in the range of 'bit' will be used to determin the rotation while only the bits within the range of 'output' will be used in the rotation
//if the actual number of filled in bits is greater than 'bit' those additional bits will be discardered
int rr::init_scrambler(int bit, int rotate)
{

//Doesn't really work if any of these are <1
if(bit<= 0 || rotate <= 0)
	return -1;
//Can't rotate more than we have in bits
if(bit < (1<<rotate))
	return -1;

bits = bit;
rotates = rotate;
mask = 1;
for(int i = 0; i < bit -1; ++i)
	mask = mask | (mask << 1);

//cout << "mask: " << mask << "\tsubmask: " << submask << endl;
return 0;
}

int rr::init_scrambler(int a, int b, int c)
{
return -1;
}



uint64_t rr::scramble_int(uint64_t rn)
{
//rns >> (bits-rotates): aka x, determins how far we left shift for the rotate
//rns&submask >> x: removes unwanted upper bits
// outputs - x: aka y, how much we left shift
// rns&submask << y: shifts the lowest bits to the top of the output bits
// ((rns&submask >> x)| (rns&submask << y) )&submask : Merging of all parts

uint64_t rns = rn;
//Dropping potentially unneeded bits
rns = rns & mask;

//Test output
/*
cout << "rns: " << rns << "\trns submask: " << (rns&submask);
cout << "\trr l val: " << (rns >> (bits-rotates)) << "\trr l output: " << ((rns&submask) >> ((rns) >> (bits-rotates)));
cout  << "\trr r val: " << (outputs - ((rns) >> (bits-rotates))) << "\trr r output: " << ((rns << (bits - ((rns) >> (bits-rotates))))&submask);
cout  << "\toutput: " << (( ((rns&submask) >> ((rns) >> (bits-rotates))) |  ((rns << (bits - ((rns) >> (bits-rotates)))))  )&submask) << endl;
*/
return (int64_t) (( (rns >> ((rns) >> (bits-rotates))) |  ((rns << (bits - ((rns) >> (bits-rotates)))))  )&mask);
}
double rr::scramble_double(double)
{
return 0;
}

float rr::scramble_flt(float)
{
return 0;
}








int rr::init_scrambler()
{
return -1;
}

int rr::init_scrambler(int a)
{
return -1;
}

int rr::init_scrambler(int a, int b, int c, int d)
{
return -1;
}

