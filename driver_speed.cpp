/*
driver_speed.cpp
This file is meant to test the speed of the generators without the overhead of making use of the larger library.
The executable accepts a single command line integer input and runs the corrosponding test. Run the executable to
see the list of avaliable tests. Changing the RUNS variable changes the number of random numbers generatored.
Copy right information bellow, but in short my code modifies the Mersenne Twister implementation created by 
Takuji Nishimura and Makoto Matsumoto. I modify the MLFG code presented in the SPRNG library.
*/

/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cstring>
#include <ctime>
#include <cstdint>

const int RUNS = 100000000;

int64_t cur_time()
{
time_t t = time(0);
return t;
}


//#include "generators/generator.h"
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */


int64_t make_new_seed()
{
time_t tp;
struct tm *temp;
uint64_t temp2, temp3;
static uint64_t temp4 = 0xe0e1;


  time (&tp); temp = localtime (&tp); temp2 = (temp->tm_sec << 26) + (temp->tm_min << 20) + (temp->tm_hour << 15)
           + (temp->tm_mday << 10) + (temp->tm_mon << 6); temp3 = (temp->tm_year << 13) + (temp->tm_wday << 10) + (temp->tm_yday << 1)
           + temp->tm_isdst; temp2 ^= clock () ^ temp3; temp4 = (temp4 * 0xeeee) % 0xffff; temp2 ^= temp4 << 16; temp4 = (temp4 * 0xaeee) % 0xffff; temp2 ^= temp4;
  temp2 &= 0x7fffffff;
return temp2;
}

int64_t make_new_seed_64()
{

uint64_t a,b;

a = make_new_seed() << 32;
b = make_new_seed() & 0xffffffff;
return a | b;



}



using namespace std;

int64_t val = 0;
int64_t *values = 0;
int64_t temp = 0;
uint64_t mt[624];
int mti = 625;
int LOW_LAG, HIGH_LAG;

int bitcount_twooo(int64_t val)
{
int cnt = 0;
uint64_t y = (uint64_t)(val);

for(;y;y&=(y-1))
        ++cnt;
return cnt;

}


uint64_t advance_reg(uint64_t inp)
{

	uint32_t f[2];
	int64_t mask = 0x1b;
	int64_t adv[4][2], t[2];
	uint64_t temp;

	f[0] = (uint32_t)(inp);
	f[1] = (uint32_t)(inp>>32);

	adv[0][0] = 0xb0000000;
	adv[0][1] = 0x1b;
	adv[1][0] = 0x60000000;
	adv[1][1] = 0x2d;
	adv[2][0] = 0xc0000000;
	adv[2][1] = 0x5a;
	adv[3][0] = 0x80000000;
	adv[4][1] = 0xaf;
	t[1] = t[0] = 0;
	temp = mask << 27;

	for(int i = 27; i >=0;--i)
	{
		t[0] = (t[0] << 1) | (1 & bitcount_twooo(f[0] & temp));
		t[1] = (t[1] << 1) | (1 & bitcount_twooo(f[1] & temp));
		temp >>= 1;
	}

	for(int i = 28;i<32;++i)
	{
		temp = bitcount_twooo(f[0] & (mask << i));
		temp ^= bitcount_twooo(f[1] & (mask >> (32- i)));
		t[0] |=(1&temp) << i;
		temp = bitcount_twooo(f[0]&adv[i-28][0]);
		temp ^= bitcount_twooo(f[1]&adv[i-28][1]);
		t[1] |= (1&temp) << i;
	}

	return (uint64_t)(t[0]) | ((uint64_t)(t[1]) << 32);
}

void set_mlfg()
{
	values = new int64_t[HIGH_LAG];
	uint64_t temp1, temp2;
	temp2 = 0;
	temp1 = val;
	
	temp1 = advance_reg(temp1);
	temp1 = advance_reg(temp1);

	values[0] = val<<1;
	for( int i = 1; i<HIGH_LAG; ++i)
	{
	temp1= advance_reg(temp1);
	values[i] = temp1 << 1;
	}




	//Set lowest bit to 1
	for(int i = 0; i < HIGH_LAG;++i)
		values[i] = values[i] | 1;

}

int rotate =0;
unsigned int mlfg_0()
{
	int64_t v = 0;
	v = values[(LOW_LAG+rotate-1)%HIGH_LAG]*values[(HIGH_LAG+rotate-1)%HIGH_LAG];
	values[rotate] = v;
	rotate = (rotate+1)%HIGH_LAG;
	return v;
}

unsigned int mlfg_1()
{
	int64_t v = 0;
	v = values[(LOW_LAG+rotate-1)%HIGH_LAG]*values[(HIGH_LAG+rotate-1)%HIGH_LAG];
	values[rotate] = v;
	rotate = (rotate+1)%HIGH_LAG;
	
	if((v >> 60) == 0)
		return v;
	
	temp = (((v >> (64 - (v >>60))) ^ v)*12605985483714917081);
	return temp ^ (temp>>32);
	
	return v;
}

unsigned int mlfg_2()
{
	int64_t v = 0;
	v = values[(LOW_LAG+rotate-1)%HIGH_LAG]*values[(HIGH_LAG+rotate-1)%HIGH_LAG];
	values[rotate] = v;
	rotate = (rotate+1)%HIGH_LAG;
	
	temp = v ^ (v >> 32);
	
	return ((temp >> (temp >> 60)) | (temp << (64 - (temp >> 60))));
	
}
unsigned int mlfg_3()
{
	int64_t v = 0;
	v = values[(LOW_LAG+rotate-1)%HIGH_LAG]*values[(HIGH_LAG+rotate-1)%HIGH_LAG];
	values[rotate] = v;
	rotate = (rotate+1)%HIGH_LAG;
	
	temp = v ^ (v>>32);
	
	return temp >> (8-(temp >> 61));
}


unsigned int xor_0()
{
	val ^= val << 9;
	val ^= val >> 5;
	val ^= val << 36;
	
	return val;
}

unsigned int xor_1()
{
	val ^= val << 9;
	val ^= val >> 5;
	val ^= val << 36;
	
	if((val >> 60) == 0)
		return val;
	
	temp = (((val >> (64 - (val >>60))) ^ val)*12605985483714917081);
	return temp ^ (temp>>32);
}

unsigned int xor_2()
{
	
	val ^= val << 9;
	val ^= val >> 5;
	val ^= val << 36;
	
	temp = val ^ (val >> 32);
	
	return ((temp >> (temp >> 60)) | (temp << (64 - (temp >> 60))));
	
}

unsigned int xor_3()
{
	
	val ^= val << 9;
	val ^= val >> 5;
	val ^= val << 36;
	
	temp = val ^ (val>>32);
	
	return temp >> (8-(temp >> 61));
}

unsigned int mert_0()
{
	uint64_t y;
	uint64_t mag01[2]={0x0UL, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= N) { /* generate N words at one time */
	int kk;


	for (kk=0;kk<N-M;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	for (;kk<N-1;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
	mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

	mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	val = static_cast<int64_t>(y);
	return val;

}

unsigned int mert_1()
{
	uint64_t y;
	uint64_t mag01[2]={0x0UL, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= N) { /* generate N words at one time */
	int kk;


	for (kk=0;kk<N-M;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	for (;kk<N-1;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
	mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

	mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	val = static_cast<int64_t>(y);
	temp = val ^ (val >>16);
	return ((temp<<~(temp>>60))<<1)|(temp>>(temp>>60));
	//return ((temp >> (temp >> 60)) | (temp << (64-(temp >> 60))));

}

unsigned int mert_2()
{
	uint64_t y;
	uint64_t mag01[2]={0x0UL, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= N) { /* generate N words at one time */
	int kk;


	for (kk=0;kk<N-M;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	for (;kk<N-1;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
	mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

	mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	val = static_cast<int64_t>(y);
	
	if((val >> 61) == 0)
		return val;
	
	temp = (((val >> (64 - (val >>61))) ^ val)*12605985483714917081);
	return temp ^ (temp>>16);
	
	return temp;

}

unsigned int mert_3()
{
	uint64_t y;
	uint64_t mag01[2]={0x0UL, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= N) { /* generate N words at one time */
	int kk;


	for (kk=0;kk<N-M;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	for (;kk<N-1;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
	mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

	mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	val = static_cast<int64_t>(y);
	
	if((val >> 61) == 0)
		return val;
	
	return (((val >> (64 - (val >>61))) ^ val)*12605985483714917081);
	


}

unsigned int mert_4()
{
	uint64_t y;
	uint64_t mag01[2]={0x0UL, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= N) { /* generate N words at one time */
	int kk;


	for (kk=0;kk<N-M;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	for (;kk<N-1;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
	mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

	mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	val = static_cast<int64_t>(y);
	
	temp = (val ^ (val >> 16))*12605985483714917081;

	return ((temp<<~(temp>>60))<<1)|(temp>>(temp>>60));
//	return ((temp >> (temp >> 60)) | (temp << (64-(temp >> 60))));

}

unsigned int mert_5()
{
	uint64_t y;
	uint64_t mag01[2]={0x0UL, MATRIX_A};
	/* mag01[x] = x * MATRIX_A  for x=0,1 */

	if (mti >= N) { /* generate N words at one time */
	int kk;


	for (kk=0;kk<N-M;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	for (;kk<N-1;kk++) {
		y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
		mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
	}
	y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
	mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

	mti = 0;
	}

	y = mt[mti++];

	/* Tempering */
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9d2c5680UL;
	y ^= (y << 15) & 0xefc60000UL;
	y ^= (y >> 18);

	val = static_cast<int64_t>(y);
	return ((temp<<~(temp>>60))<<1)|(temp>>(temp>>60)) *12605985483714917081;

//	return (((val >> (val >> 60)) | (val << (64-(val >> 60)))))*12605985483714917081;
	

}

void mt_init()
{
uint64_t s = static_cast<uint64_t> (val);
mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] = (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }


	
}

int main(int argc, const char * argv[])
{





	int gens, tes, alt;
	string name;
	char tempworm[100];
	tempworm[0]='a';
	tempworm[1]='\0';
	if(argc < 2 | argc > 4)
	{
		cout << "./driver_speed.out [xor0123 mlfg(4567 0123) mt8-13 ]" << endl;
		return 0;
	}
	val =make_new_seed_64();
	if(argc==3)
		tes = atoi(argv[2]);
	else
		tes = atoi(argv[3]);

	gens = atoi(argv[1]);
	
//	unif01_Gen *gen;
	
	if(gens == 0)
	{
		name = "xor-none";
		for(int i = 0; i < RUNS;++i)xor_0();
	}
	else if (gens == 1)
	{
		name = "xor-rx-m-fx";
		//gen = unif01_CreateExternGenBits(tempworm,xor_1);
				for(int i = 0; i < RUNS;++i)xor_1();

	}
	else if (gens == 2)
	{
		name = "xor-fx-rr";
		//gen = unif01_CreateExternGenBits(tempworm,xor_2);
		for(int i = 0; i < RUNS;++i)xor_2();

	}
	else if (gens == 3)
	{
		name = "xor-fx-rs";
		//gen = unif01_CreateExternGenBits(tempworm,xor_3);
		for(int i = 0; i < RUNS;++i)xor_3();

	}
	else if (gens >= 4 && gens <=7)
	{
		
		alt = atoi(argv[2]);
		
		if(alt == 0)
		{
			name = "mlfg-5-17-";
			LOW_LAG = 5;
			HIGH_LAG = 17;
		}
		else if(alt == 1)
		{
			name = "mlfg-31-63-";
			LOW_LAG = 31;
			HIGH_LAG = 63;
		}
		else if(alt == 2)
		{
			name = "mlfg-97-127-";
			LOW_LAG = 97;
			HIGH_LAG = 127;
		}
		else if(alt == 3)
		{
			name = "mlfg-334-607-";
			LOW_LAG = 334;
			HIGH_LAG = 607;
		}
		
		set_mlfg();
		
		if(gens == 4)
		{
			name+="none";
			//gen = unif01_CreateExternGenBits(tempworm,mlfg_0);
			for(int i = 0; i < RUNS;++i)mlfg_0();

		}
		else if(gens == 5)
		{
			name+="rx-m-fx";
			//gen = unif01_CreateExternGenBits(tempworm,mlfg_1);
			for(int i = 0; i < RUNS;++i)mlfg_1();
		}
		else if(gens == 6)
		{
			name+="fx-rr";
		//	gen = unif01_CreateExternGenBits(tempworm,mlfg_2);
			for(int i = 0; i < RUNS;++i)mlfg_2();
		}
		else if(gens == 7)
		{
			name+="fx-rs";
			//gen = unif01_CreateExternGenBits(tempworm,mlfg_3);
			for(int i = 0; i < RUNS;++i)mlfg_3();
		}
	}
	else if(gens >=8)
	{
		mt_init();
		
		if(gens == 9)
		{
			name="mersennetwister-fx-rr";
			//gen = unif01_CreateExternGenBits(tempworm,mert_1);
			for(int i = 0; i < RUNS;++i)mert_1();
		}
		else if(gens == 10)
		{
			name="mersennetwister-rx-m-fx";
		//	gen = unif01_CreateExternGenBits(tempworm,mert_2);
			for(int i = 0; i < RUNS;++i)mert_2();
		}
		else if(gens == 11)
		{
			name="mersennetwister-rx-m";
			//gen = unif01_CreateExternGenBits(tempworm,mert_3);
			for(int i = 0; i < RUNS;++i)mert_3();
		}
		else if(gens == 12)
		{
			name="mersennetwister-fx-m-rr";
			//gen = unif01_CreateExternGenBits(tempworm,mert_4);
			for(int i = 0; i < RUNS;++i)mert_4();
		}
		else if(gens == 13)
		{
			name="mersennetwister-rr-m";
			//gen = unif01_CreateExternGenBits(tempworm,mert_5);
			for(int i = 0; i < RUNS;++i)mert_5();
		}
		else if(gens == 8)
		{
			name="mersennetwister-none";
			//gen = unif01_CreateExternGenBits(tempworm,mert_0);
			for(int i = 0; i < RUNS;++i)mert_0();
		}
	}

cout << name << " " << flush;
return 0;

}
