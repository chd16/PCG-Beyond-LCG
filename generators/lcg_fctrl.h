#ifndef _lcg_fctrl_h
#define _lcg_fctrl_h
#ifndef NULL
#define NULL
#endif
#include <cstdarg>
#include "generator.h"
#include "../scramblers/scrambler.h"
#include "lcg_values.h"
class lcg_fctrl : public generator {

public:
lcg_fctrl();
int64_t get_rn_int();
float get_rn_flt();
double get_rn_double();

//Accepts starting seed value and selection for multiplier and incrementer
//uses preset multiplier and incrementer value
int init_rng(int64_t sd, int sel);

//uses a default seed too
int init_rng();
int init_rng(int64_t a);
int init_rng(int64_t a, int b, int c);
int init_rng(int64_t a, int b, int c, int d, int e);
int init_rng(int64_t a, int b, int c, int d);


int add_scrambler(scrambler * scramb);
int64_t get_seed();
private:



int64_t seed;
int64_t val;
int64_t mult;
int64_t con;
int64_t mod;

scrambler * scram;


};

#endif
