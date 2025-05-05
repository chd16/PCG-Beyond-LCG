//#include "../generators/generator.h"

#ifndef _randomrotate_h
#define _randomrotate_h
#ifndef NULL
#define NULL 0
#endif
#include "scrambler.h"

//drop bit random shift
class rr : public scrambler {

public:
//Needs to initialize the generator used in the LK Hash
//Pass in a function pointer that returns an INT with no params

//Function for if a scramble requires an rng scourge
int init_add_gen(int64_t (*gener)());
//Only the 3 input scrambler is used
int init_scrambler();
int init_scrambler(int);
int init_scrambler(int, int);
int init_scrambler(int, int, int);
int init_scrambler(int, int, int, int);





//scramble an int
uint64_t scramble_int(uint64_t);
float scramble_flt(float);
double scramble_double(double);
//int init_scrambler(int (*func)());

private:

//stores the rng scourge
int64_t (*func)();

int bits;
int rotates;
int outputs;
uint64_t mask;
uint64_t submask;
};


//https://psychopath.io/post/2021_01_30_building_a_better_lk_hash
#endif
