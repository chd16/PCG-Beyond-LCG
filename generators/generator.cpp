#include "generator.h"
#include "select_gen.h"
#include <iostream>


int init_generator(generator* gen, int count, int64_t a, int b, int c, int d, int e){
if(count == 0)
{
return gen->init_rng();
}
else if(count == 1)
{
return gen->init_rng(a);
}
else if(count == 2)
{
return gen->init_rng(a,b);
}
else if(count == 3)
{
return gen->init_rng(a,b,c);
}

else if(count == 4)
{
return gen->init_rng(a,b,c,d);
}
else if(count == 5)
{
return gen->init_rng(a,b,c,d,e);
}
else
return -1;
}


generator * create_generator(int type)
{
	return select_generator(type);
}

int free_generator(generator * gen)
{
delete gen;
return 0;

}




//Use the one in SPRNG but SPRNG.org is down right now?
int64_t create_seed()
{
return make_new_seed_64();
}
