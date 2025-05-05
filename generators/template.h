//You can search replace [name] with the name of your generator
#ifndef _[name]_h
#define _[name]_h
#ifndef NULL
#define NULL
#endif
#include <cstdarg>
#include "generator.h"
#include "../scramblers/scrambler.h"

class [name] : public generator {

public:
[name]();
int64_t get_rn_int();
float get_rn_flt();
double get_rn_double();


//Modify which ever init_rng() function matches the number of
//Parameters that you need for your generator
int init_rng();
int init_rng(int64_t a);
int init_rng(int64_t a, int b);
int init_rng(int64_t a, int b, int c);
int init_rng(int64_t a, int b, int c, int d);
int init_rng(int64_t a, int b, int c, int d, int e);


int add_scrambler(scrambler * scramb);
int64_t get_seed();
private:



int64_t seed; //Stores the starting Seed so it can be retrieved later 
int64_t val; //stores the current state for more generators with single states
scrambler * scram; //stores the pointer to the scrambler 

int64_t default_seed;

};

#endif
