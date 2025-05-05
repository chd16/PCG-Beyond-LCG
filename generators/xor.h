#ifndef _xor_h
#define _xor_h
#ifndef NULL
#define NULL
#endif
#include <cstdarg>
#include <cstdint>
#include "generator.h"
#include "../scramblers/scrambler.h"
#include "xor_values.h"

class XOR : public generator{

public:
XOR();
int64_t get_rn_int();
float get_rn_flt();
double get_rn_double();

//accepts starting seed and shift values 1,2,3
//int init_rng(int count...);

int init_rng(int64_t sd, int s1, int s2, int s3);
int init_rng(int64_t sd, int sel); //accept seed and use xor_values.h for selection
//uses presest shift values
int init_rng(int64_t sd);
//uses a default seed too
int init_rng();

//invalid call
int init_rng(int64_t a, int b, int c);
int init_rng(int64_t a, int b, int c, int d, int e);

int add_scrambler(scrambler*);
int64_t get_seed();
private:


int shift1;
int shift2;
int shift3;
int64_t seed;
int64_t val;
scrambler * scram;
};

#endif

