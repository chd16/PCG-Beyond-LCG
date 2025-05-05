/*
This file prints out a selection of the avaliable parameter values
used in the driver_mixed.cpp file. These values can be added to by modifying the 
correct *_values.h files by adding the values to the list of options
and updating the total number of values variable.
*/

#include "generators/lcg_values.h"
#include "generators/xor_values.h"
#include "generators/mlfg_values.h"
#include <iomanip>
#include <iostream>
#include <cstdlib>
using namespace std;

void print_err()
{
 cout << "./print.out [0.lcg 1.xor 2.lfg]" << endl;
}

int main(int argc, const char * argv[])
{
if(argc == 1)
{
 print_err();
 return 0;
}

int sel = atoi(argv[1]);

if(sel < 0 | sel > 2)
{
 print_err();
 return 0;
}

if(sel == 0)
{
 for(int i = 0; i < MAX_SEL;++i)
 {
  cout  << right<< setw(3) << i <<": " <<left << setw(20) << lcg_values[i][0] << setw(20) << lcg_values[i][1] << setw(20) << lcg_values[i][2] << endl;
 }
}
else if(sel == 1)
{
 for(int i = 0; i < MAX_SEL_XOR;++i)
 {
  cout  << right<< setw(3) << i <<": " <<left << setw(5) << xor_values[i][0] << setw(5) << xor_values[i][1] << setw(5) << xor_values[i][2] << endl;
 }
}
else if(sel == 2)
 for(int i = 0; i < MAX_SEL_MLFG;++i)
 {
  cout  << right<< setw(3) << i <<": " <<left << setw(5) << mlfg_values[i][0] << setw(5) << mlfg_values[i][1] << endl;
 }

}
