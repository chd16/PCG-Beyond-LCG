Readme.txt
This library contains the source code used to test the PCG scrambling techniques as 
outlined in the paper "Moving the PCG beyond LCGs" by Christopher Draper and Michael Mascagni.

It contains the generators used in that paper, the generalized PCG scrambling techniques, 
and a number of driver files used in testnig. It currently contains the following generators:
the linear congruental generator, the xorshift generator, the multiplicative lagged fibonachi 
generator, and the Mersen Twister. It also currently contains the following scramblers: the 
improved lk hash, random shift, random rotation, random xorshift, fixed xorshift, const multiplier,
and fixed drop shift.

To compile the code you will need the TestU01 library installed. Currently the driver file 
driver_mixed.cpp makes use of TestU01 in order to test the quality of the code. Currently 
driver_mixed.cpp assumes the TestU01 library will be compiled into a folder called TestU01/ 
in the same directory. If you don't wish to make use of TestU01 you simply need to remove the
driver_mixed.cpp file and modify the Makefile in the main directory. If you have the TestU01 
library installed in the correct location you can simply run Make to compile the correct code.
