#ifndef _mlfg_h
#define _mlfg_h
#ifndef NULL
#define NULL
#endif
#include <cstdarg>
#include "generator.h"
#include "../scramblers/scrambler.h"

class mlfg : public generator {

public:
mlfg();
~mlfg();
int64_t get_rn_int();
float get_rn_flt();
double get_rn_double();

int add_scrambler(scrambler * scramb);
int64_t get_seed();

int init_rng(int64_t, int, int, int, int);
int init_rng(int64_t, int, int, int);
int init_rng(int64_t, int, int);
int init_rng(int64_t, int);
int init_rng(int64_t);
int init_rng();


private:
//Does some matrix math, used in setting intial seed
uint64_t advance_reg(uint64_t);
//Sets values
int set_seed();


int low_lag, high_lag, rotate;
scrambler * scram;
int64_t seed;
int64_t *values;

};

#endif
