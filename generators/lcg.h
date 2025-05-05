#ifndef _lcg_h
#define _lcg_h
#ifndef NULL
#define NULL
#endif
#include <cstdarg>
#include "generator.h"
#include "../scramblers/scrambler.h"

class LCG : public generator {

public:
LCG();
int64_t get_rn_int();
float get_rn_flt();
double get_rn_double();

//Accepts starting seed value and selection for multiplier and incrementer
int init_rng(int64_t seed, int mult, int incre);
//uses preset multiplier and incrementer value
int init_rng(int64_t seed);
//uses a default seed too
int init_rng();

int init_rng(int64_t a, int b);
int init_rng(int64_t a, int b, int c, int d);
int init_rng(int64_t a, int b, int c, int d, int e);


int add_scrambler(scrambler * scramb);
int64_t get_seed();
private:



int64_t multiplier;
int64_t incrementer;
int64_t seed;
int64_t val;
scrambler * scram;

int64_t default_seed;
int64_t default_mult;
int64_t default_incre;

};

#endif
