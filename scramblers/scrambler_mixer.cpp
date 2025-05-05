#include "scrambler_mixer.h"

void scrambler_mixer::expand(int v)
{
scrambler ** temp;
if(capacity == 0) //on empty create array
{
 capacity = v;
 scrams = new scrambler*[v];
 return;
}

temp = new scrambler*[capacity+v];
for(int i = 0; i < (capacity+v); ++i)
	temp[i] = 0;

for(int i = 0; i < size; ++i)
	temp[i] = scrams[i];

delete [] scrams;
scrams = temp;
capacity+= v;
return;
}

scrambler_mixer::scrambler_mixer()
{
size = capacity = 0;
scrams = 0;
}


bool scrambler_mixer::add_scrambler(scrambler * scr)
{
expand(1);
scrams[size] = scr;
size++;
return true;
}

bool scrambler_mixer::free_all()
{
for(int i = 0; i < size;++i)
	delete scrams[i];
if(scrams!=0)
	delete [] scrams;
size = 0;
capacity = 0;
scrams = 0;
return true;
}

uint64_t scrambler_mixer::scramble_int(uint64_t x)
{
for(int i = 0; i < size;++i)
	x = scrams[i]->scramble_int(x);
return x;
}
