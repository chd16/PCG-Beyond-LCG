#ifndef scrambler_mixer_h
#define scrambler_mixer_h
#ifndef NULL
#define NULL 0
#endif
#include "scrambler.h"

class scrambler_mixer : public scrambler
{
public:
scrambler_mixer();
bool add_scrambler(scrambler * scr);
bool free_all();
virtual uint64_t scramble_int(uint64_t);



//Here for compilation reasons
virtual int init_add_gen(int64_t (*gener)()){return 0;}

int init_scrambler() {return 0;}
int init_scrambler(int) {return 0;}
int init_scrambler(int, int) {return 0;}
int init_scrambler(int, int, int) {return 0;}
int init_scrambler(int, int, int, int) {return 0;}

virtual float scramble_flt(float) {return 0;}
virtual double scramble_double(double){return 0;}


private:
void expand(int v = 2);
scrambler ** scrams;
int size, capacity;
};


































#endif
