//Can search and replace [name] with the new scrambler you want
#ifndef _[name]_h
#define _[name]_h
#ifndef NULL
#define NULL 0
#endif
#include "scrambler.h"

class [name] : public scrambler {

public:
//Needs to initialize the generator used in the LK Hash
//Pass in a function pointer that returns an INT with no params

//Function for if a scramble requires an rng scourge
int init_add_gen(int64_t (*gener)());
//if the scrambler has any inputs use this
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

//stores the rng source (only used in lk_hash currently)
int64_t (*func)();

};

#endif
