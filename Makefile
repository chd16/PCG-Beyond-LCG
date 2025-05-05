make: driver3 driver4 print
	echo DONE

print:
	g++ print_options.cpp -o print.out

driver3:
	cd generators && $(MAKE)
	cd scramblers && $(MAKE)
	g++ -std=c++14 -Wall -O3 -c -o driver_mixed.o driver_mixed.cpp -ITestU01/include -LTestU01/lib -Igenerator -Ilcg -ltestu01 -lprobdist -lmylib -lm
	g++ driver_mixed.o scramblers/*.o generators/*.o  -ITestU01/include -LTestU01/lib -Ilcg -ltestu01 -lprobdist -lmylib -lm -o driver3.out

driver4:
	cd generators && $(MAKE)
	cd scramblers && $(MAKE)
	g++ -std=c++14 -Wall -O3 -c -o driver_speed.o driver_speed.cpp -ITestU01/include -LTestU01/lib -Igenerator -Ilcg -ltestu01 -lprobdist -lmylib -lm
	g++ driver_speed.o scramblers/*.o generators/*.o  -ITestU01/include -LTestU01/lib -Ilcg -ltestu01 -lprobdist -lmylib -lm -o driver4.out



clean:
	-rm *.o *.out
	-cd generators && $(MAKE) clean
	-cd scramblers && $(MAKE) clean
