#include "curtime.h"
#include <iostream>
using namespace std;
int64_t cur_time()
{
time_t t = time(0);
return t;
}


//New seed math based off sprng.cpp make_new_seed()
int64_t new_seed()
{
int64_t t1 = cur_time();
int64_t t2 = clock();
t1 = (t1 * 0xeeeeeeee)%0xffffffff;
t2 ^= t1 << 32;
cout << "t1 " << t1 << " t2 " << t2 << endl;
t1 = (t1*0xaeeeeeee)%0xffffffff;
t2^=t1;
cout << "t1 " << t1 << " t2 " << t2 << endl;

t2 &=0x7fffffffffffffff;
cout << "t1 " << t1 << " t2 " << t2 << endl;

return t2;
}


//Made directly from the spring.cpp make_new_seed()
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

/*
time_t tp;
struct tm *temp;
uint64_t temp2, temp3;
static uint64_t temp4 = 0xe0e1;


  time (&tp); temp = localtime (&tp); temp2 = ((int64_t)(temp->tm_sec) << 52) + ((int64_t)(temp->tm_min) << 40) + (temp->tm_hour << 30)
           + (temp->tm_mday << 20) + (temp->tm_mon << 12); temp3 = (temp->tm_year << 26) + (temp->tm_wday << 20) + (temp->tm_yday << 2)
           + temp->tm_isdst; temp2 ^= clock () ^ temp3; temp4 = (temp4 * 0xeeeeeeee) % 0xffffffff; temp2 ^= temp4 << 32; temp4 = (temp4 * 0xaeeeeeee) % 0xffffffff; temp2 ^= temp4;
  temp2 &= 0x7fffffffffffffff;
return temp2;
*/
uint64_t a,b;

a = make_new_seed() << 32;
b = make_new_seed() & 0xffffffff;
//cout << a << " " << b << " " << (a|b) << endl;
return a | b;



}



