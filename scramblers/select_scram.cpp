#include "select_scram.h"

scrambler* select_scrambler(int type)
{

switch(type)
{
case 0:
	return new lk_hash;
	break;
case 1:
	return new db_rs;
	break;
case 2:
	return new rr;
	break;
case 3:
	return new rand_xor;
	break;
case 4:
	return new fixed_xors;
	break;
case 5:
	return new constant_multiplier;
	break;
case 6:
	return new fixed_dropshift;
	break;
case 7:
	return new rightshift;
	break;
default:
	return 0;

}



return 0;
}


scrambler_mixer* get_mixer()
{
return new scrambler_mixer;
}
