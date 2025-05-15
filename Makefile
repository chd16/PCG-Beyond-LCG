make: driver_mixed driver_speed print
	echo DONE

print:
	g++ print_options.cpp -o print.out

driver_mixed:
	cd generators && $(MAKE)
	cd scramblers && $(MAKE)
	g++ -std=c++14 -Wall -O3 -c -o driver_mixed.o driver_mixed.cpp -ITestU01/include -LTestU01/lib -Igenerator -Ilcg -ltestu01 -lprobdist -lmylib -lm
	g++ driver_mixed.o scramblers/*.o generators/*.o  -ITestU01/include -LTestU01/lib -Ilcg -ltestu01 -lprobdist -lmylib -lm -o driver_mixed.out

driver_speed:
	g++ -std=c++14 -Wall driver_speed.cpp -o driver_speed.out



clean:
	-rm *.o *.out
	-cd generators && $(MAKE) clean
	-cd scramblers && $(MAKE) clean
