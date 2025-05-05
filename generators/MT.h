/* Mersen Twister code taken and modified from:
https://www.math.sci.hiroshima-u.ac.jp/m-mat/MT/MT2002/CODES/mt19937ar.c
 */
#ifndef _MT_h
#define _MT_h
#ifndef NULL
#define NULL
#endif
#include <cstdarg>
#include "generator.h"
#include "../scramblers/scrambler.h"

class MT : public generator {

public:
MT();
int64_t get_rn_int();
float get_rn_flt();
double get_rn_double();

//Accepts starting seed value and selection for multiplier and incrementer
//uses preset multiplier and incrementer value
int init_rng(int64_t seed);
//uses a default seed too
int init_rng();

int init_rng(int64_t a, int b);
int init_rng(int64_t a, int b, int c);
int init_rng(int64_t a, int b, int c, int d);
int init_rng(int64_t a, int b, int c, int d, int e);


int add_scrambler(scrambler * scramb);
int64_t get_seed();
private:

uint64_t mt[624];
int mti = 625;

int64_t seed;
int64_t val;
scrambler * scram;

int64_t default_seed;

};

#endif
