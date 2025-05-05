//#include "../generators/generator.h"

#ifndef _lk_hash_h
#define _lk_hash_h
#ifndef NULL
#define NULL 0
#endif
#include "scrambler.h"

class lk_hash : public scrambler {

public:
//Needs to initialize the generator used in the LK Hash
//Pass in a function pointer that returns an INT with no params


int init_add_gen(int64_t (*gener)());
uint64_t scramble_int(uint64_t);
float scramble_flt(float);
double scramble_double(double);
//int init_scrambler(int (*func)());

//LK has uses none of these, only here for compilation reasons
int init_scrambler();
int init_scrambler(int);
int init_scrambler(int, int);
int init_scrambler(int, int, int);
int init_scrambler(int, int, int, int);

private:

int64_t (*func)();

};


//https://psychopath.io/post/2021_01_30_building_a_better_lk_hash
#endif
