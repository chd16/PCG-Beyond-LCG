/*
driver_mixed.cpp
This code was created to test the quality of the generators with
any combination of PCG scramblers attached to them using TestU01's
crush tests. Input is provided via the command line. Provide
no command line input to see the format of the wanted input.
*/

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <bitset>
#include "generators/generator.h"
#include "scramblers/scrambler.h"
#include "generators/lcg_values.h"
#include "generators/xor_values.h"
#include "generators/mlfg_values.h"
#include "scramblers/scrambler_mixer.h"
#include "scramblers/select_scram.h"
#include <cstring>

extern "C"
{
#include "unif01.h"
#include "bbattery.h"
}

using namespace std;

generator *test;
unsigned int hold = 0;
unsigned int build = 0;
unsigned int ret = 0;
int length = 48;
int err_cnt = 1;
unsigned int wrapper()
{
return test->get_rn_int();
}

void print_err()
{
 cout << "./driver_mixed.out [0. lcg 1. xor 2. mlfg 3. MT] [0-("<< MAX_SEL<<", " <<MAX_SEL_XOR << ", " << MAX_SEL_MLFG << ", " << 0 << ")] [0.small 1.big 2.print 3.crush] [number of scramblers] [0.dbrs [bit,drop,shift,target] 1.rr[bit,rotate] 2.rxs[bit,ixor] 3.fxs[bit, ixor] 4.CM[bit] 5.DBFX[bit,target] 6.FRS[shift]]" << endl;
}

int main(int argc, const char * argv[])
{
/* Setting up the generator */
int sel, tes, gens; /*value selection, tests, scrambler*/
//cout << "command line args" << endl;

if(argc <= 4)
{
print_err();
 return 0;
}

gens = atoi(argv[1]); //select generator
sel = atoi(argv[2]); //select generator values 
tes = atoi(argv[3]); //select test



scrambler_mixer * mix = 0; //hold the mix scrambler while constructing
scrambler * hash = 0; //hold the individual generated scramblers
char name[1000]; name[0] = '\0';

int scram_cnt = atoi(argv[4]); //total number of scramblers
int scram_pross = 0; //number of scramblers processed
if(scram_cnt <0)
{
 print_err();
 return 0;
}



if(gens < 0 || gens > 3)
{
print_err();
return 0;
}

//cout << "Error location: " << err_cnt++ << endl;

if(gens == 0)
{
 if(sel < 0 || sel > MAX_SEL)
 {
  print_err();
  return 0;
 }
}
else if (gens == 1)
{
 if(sel < 0 || sel > MAX_SEL_XOR)
 {
   print_err();
   return 0;
 }
}
else if (gens == 2)
{
 if(sel < 0|| sel > MAX_SEL_MLFG)
 {
  print_err();
  return 0;
 }
}

//cout << "Error location: " << err_cnt++ << endl;

uint64_t a,c,m; //multiplier, constant, modulus
if(gens == 0)
{
 a = lcg_values[sel][0];
 c = lcg_values[sel][1];
 m = lcg_values[sel][2];

 if(m != 0)
  strcat(name, ("x_n = " + to_string(a)+" * x_(n-1) + " + to_string(c) + " % " + to_string(m) + " w/ ").c_str());
 else
  strcat(name, ("x_n = " + to_string(a)+" * x_(n-1) + " + to_string(c) + " % " + to_string(64) + " w/ ").c_str());

}
else if (gens == 1)
{
 a = xor_values[sel][0];
 c = xor_values[sel][1];
 m = xor_values[sel][2];

 strcat(name, ("x_n ^= x << " + to_string(a) + "; x_n ^= >> " + to_string(c) + "; x_n ^= << " + to_string(m) + " w/ ").c_str()); 

}
else if (gens == 2)
{
 a = mlfg_values[sel][0];
 c = mlfg_values[sel][1];
 m = 0;
 strcat(name, ("x_n = x_(n-" + to_string(a) + ") * x_(n-" + to_string(c)+") w/ ").c_str());
}
else if (gens == 3)
{
 strcat(name,("Mersen Twister w/ "));
}


if(scram_cnt ==0)
{ //For give me for this sin I'm about to do
strcat(name, "Nothing");
goto Test_Time;
}


//cout << "Error location: " << err_cnt++ << endl;

uint64_t bits,determ,targ, shift, scrmblr; //total bits, determining number of bits, target bits, scrambler
mix = get_mixer();
int i; //current position in argv
i = 5;

while(scram_pross != scram_cnt)
{
 scram_pross++;
 //cout << "Error location~: " << err_cnt++ << endl;
 scrmblr = atoi(argv[i]);
 if(scrmblr < 0 || scrmblr > 6)
 {
  cout << "Incorrect scrambler selection at " << i << " with value " << scrmblr << endl;
  mix->free_all();
  return 0;
 }

 ++i; //increase pass scrambler selection
 bits = atoi(argv[i]);
 ++i; //increase pass bit selection
 if(scrmblr != 4 && scrmblr != 6) //For all the scramblers that only accept 1 input
 {
  determ = atoi(argv[i]);
  ++i; //increase pass determining determing number of bits selection
 }
 if(scrmblr == 0) //for all the scramblers that accept 4 input
 {
  shift = atoi(argv[i]);
  ++i; //increase pass determing target selection
  targ = atoi(argv[i]);
  ++i;
 }

 hash = create_scrambler(scrmblr+1); //creates the individual scrambler

 if(scrmblr == 0)
 {
  if(hash->init_scrambler(bits,determ,shift, targ) == -1) //set up scrambler and error check
  {
   cout << "1. Error initializing scrambler " << scrmblr << " " << bits << " " << determ << " " << shift << " " << targ << endl;
   mix->free_all();
   return 0;
  }
 strcat(name,("DBRS_" + to_string(bits) + "_" + to_string(determ)+"_"+ to_string(shift) + "_" + to_string(targ) + " ").c_str());
 }
 else if (scrmblr == 1)
 {
  if(hash->init_scrambler(bits,determ) == -1) //set up scrambler and error check
  {
   cout << "2. Error initializing scrambler " << scrmblr << " " << bits << " " << determ << endl;
   mix->free_all();
   return 0;
  }
  strcat(name,("RR_"+to_string(bits)+"_"+to_string(determ)+" ").c_str());
 }
 else if (scrmblr == 2)
 {
  if(hash->init_scrambler(bits,determ) == -1) //set up scrambler and error check
  {
   cout << "3. Error initializing scrambler " << scrmblr << " " << bits << " " << determ << endl;
   mix->free_all();
   return 0;
  }
  strcat(name,("RXS_"+to_string(bits)+"_"+to_string(determ)+" ").c_str());
 }
 else if (scrmblr == 3)
 {
  if(hash->init_scrambler(bits,determ) == -1) //set up scrambler and error check
  {
   cout << "4. Error initializing scrambler " << scrmblr << " " << bits << " " << determ << endl;
   mix->free_all();
   return 0;
  }
  strcat(name,("FXS_"+to_string(bits)+"_"+to_string(determ)+" ").c_str());
 }
 else if (scrmblr == 4)
 {
  if(hash->init_scrambler(bits) == -1) //set up scrambler and error check
  {
   cout << "5. Error initializing scrambler " << scrmblr << " " << bits << endl;
   mix->free_all();
   return 0;
  }
  strcat(name,("CM_"+to_string(bits)+" ").c_str());
 }
 else if (scrmblr == 5)
 {
  if(hash->init_scrambler(bits,determ) == -1) //set up scrambler and error check
  {
   cout << "6. Error initializing scrambler " << scrmblr << " " << bits << " " << determ << endl;
   mix->free_all();
   return 0;
  }
  strcat(name,("DBFS_"+to_string(bits)+"_"+to_string(determ)+" ").c_str());
 }
 else if (scrmblr == 6)
 {
  if(hash->init_scrambler(bits) == -1) //set up scrambler and error check
  {
   cout << "7. Error initializing scrambler " << scrmblr << " " << bits << endl;
   mix->free_all();
   return 0;
  }
 strcat(name,("FRS_"+to_string(bits)+" ").c_str());
 }

mix->add_scrambler(hash);
hash = 0;
}

//cout << "Error location: " << err_cnt++ << endl;
cout << name << endl;
//cout << "Error location: " << err_cnt++ << endl;

hash = mix;
//cout << "Error location: " << err_cnt++ << endl;

Test_Time:
if(gens == 0)
{
 if(m == 0)
 {
  test = create_generator(0);
  init_generator(test,3,create_seed(),a,c);
 }
 else
 {
  test = create_generator(3);
  init_generator(test,2,create_seed(),sel);
 }
}
else if(gens == 1)
{
 test = create_generator(1);
 init_generator(test,2,create_seed(),sel);
}
else if(gens == 2)
{
 test = create_generator(2);
 init_generator(test,3,create_seed(),a,c);

}
else if(gens == 3)
{
 test = create_generator(4);
 init_generator(test,1,create_seed());
}
//cout << "Error location: " << err_cnt++ << endl;
if(scram_cnt !=0)
 test->add_scrambler(hash);

unif01_Gen *gen;

gen = unif01_CreateExternGenBits(name, wrapper);


//cout << "Error location: " << err_cnt++ << endl;
if(tes == 0) 
 bbattery_SmallCrush(gen);
else if (tes == 1)
 bbattery_BigCrush(gen);
else if (tes == 2)
 for(int i = 0; i < 25; ++i)
 {
  for(int j = 0; j < 4; ++j)
   cout << left<<setw(25) << (test->get_rn_int());
 cout << endl;
 }
else if (tes == 3)
 bbattery_Crush(gen);
unif01_DeleteExternGenBits(gen);

free_generator(test);
if(scram_cnt != 0)
 mix->free_all();

return 0;
}
