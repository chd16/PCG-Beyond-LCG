#include "scrambler.h"
#include "select_scram.h"

scrambler* create_scrambler(int type)
{
	return select_scrambler(type);
}

int free_scrambler(scrambler* scram)
{
	delete scram;
	return 0;
}
