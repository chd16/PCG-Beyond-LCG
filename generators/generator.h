#ifndef _gen_h_
#define _gen_h_
#include "../scramblers/scrambler.h"
#include <cstdint>
#include "curtime.h"
class generator
{
public:
	//These are used by the subclasses to initialize various things
//	virtual int init_rng(int,int,int,int) = 0;
//	virtual int init_rng(int) = 0;
//	virtual int init_rng() = 0;

	virtual int init_rng() = 0;
	virtual int init_rng(int64_t) = 0;
	virtual int init_rng(int64_t,int) = 0;
	virtual int init_rng(int64_t,int,int) = 0;
	virtual int init_rng(int64_t,int,int,int) = 0;
	virtual int init_rng(int64_t,int,int,int,int) = 0;

	virtual int64_t get_rn_int() = 0;
	virtual float get_rn_flt() = 0;
	virtual double get_rn_double() = 0;
	virtual int add_scrambler(scrambler*) = 0;
	virtual int64_t get_seed() = 0;
//generator *gen;
	///virtual int clean();

};
//Give it the type of generator you want to create
generator* create_generator(int);
//Give it a generator pointer and the params of the generator you selected, First value is the number of params
int init_generator(generator*,int count, int64_t a = 0, int b = 0, int c = 0, int d = 0, int e = 0);
//Give it a generator to clean up
int free_generator(generator*);
//Creates a seed using the current system time
int64_t create_seed();


#endif
