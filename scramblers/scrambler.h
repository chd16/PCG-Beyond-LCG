#ifndef _scrambler_h_
#define _scrambler_h_
#include <cstdint>
class scrambler
{

public:

//The function that scrambles
//virtual unsigned int scramble(unsigned int);
//Initialization for func variable bellow
//All functions will have an init_add_gen var they might just accept different function types
//virtual int init_add_gen();
virtual int init_add_gen(int64_t (*gener)()) = 0;

virtual int init_scrambler() = 0;
virtual int init_scrambler(int) = 0;
virtual int init_scrambler(int, int) = 0;
virtual int init_scrambler(int, int, int) = 0;
virtual int init_scrambler(int, int, int, int) = 0;

//Not all of these are necisarily defined for each function
virtual uint64_t scramble_int(uint64_t) = 0;
virtual float scramble_flt(float) = 0;
virtual double scramble_double(double) = 0;

//private:
	//used in cases where the scrambler references another function
	//Paramaters for that function will vary for each scrambler
	//so a generic void function pointer is used and will be handled
	//within each scrambler by hand
	//virtual void *func(void);

};

//Give it the type number of a scrambler and it'll return one to you
scrambler* create_scrambler(int);
//will clean up a scrambler
int free_scrambler(scrambler*);














#endif
