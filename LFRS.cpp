// LFRS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <time.h>
#include <string>
using namespace std;
unsigned  long LFSR();


void clear_array(int p[], int size) {


	for (int i = 0; i <size; i++)
		p[i] = 0;

}
void bin(unsigned n, int number_ofbits)
{
	unsigned  i;
	for (i = 1 << number_ofbits-1; i > 0; i = i / 2)
		(n & i) ? printf("1") : printf("0");


	printf("\n");
}

FILE *lsfr_out;

int math[0x7ffffff];
int found = 0;
uint32_t seed;
int LFSR2() {
	 


	static unsigned long ShiftRegister = time(NULL) - 762834772;
	static int period_count = 0;
	/* Anything but 0. */
	//fprintf(lsfr_out, "%d \n", ShiftRegister);








	ShiftRegister = (((((ShiftRegister >> 11)
		^ (ShiftRegister >> 6)
		^ (ShiftRegister >> 4)
		^ (ShiftRegister >> 2)
		^ (ShiftRegister >> 1)
		^ ShiftRegister))
		& 0x00000001)
		<< 11)
		| (ShiftRegister >> 1);
	period_count++;
	return ShiftRegister;
}



int  threbit() {


	static unsigned long ShiftRegister = 4;

	ShiftRegister = (((((ShiftRegister >> 2)

		^ ShiftRegister))
		& 0x00000001)
		<< 2)
		| (ShiftRegister >> 1);

	return ShiftRegister;

}
// tap polynomial (64, 4, 3, 1, 0) --> x^64 + x^4 + x^3 + x + 1
int LFSR_64bit(uint64_t init){

	



	static	uint64_t  ShiftRegister = init;//we use 64 bit integer so that it can be shiffted nataveliy
	/* Anything but 0. */
	ShiftRegister = (((((ShiftRegister >> 63)
		^ (ShiftRegister >> 3)
		^ (ShiftRegister >> 2)
	
		^ ShiftRegister))
		& 0x00000001)
		<< 63)
		| (ShiftRegister >> 1);
	return ShiftRegister;        // &0x00000001; 




}

int main()
{
	time_t second;
	second = time(NULL);

	
	uint32_t  st = (second <<27) ^second ;

	//st = (st << 27) + 1;
	string
fname = "xr18.txt";
	cout << fname << endl;
	
	uint32_t ramdom_addrs = (int)&second;
	seed = st ^ ramdom_addrs;
	cout << second << endl;
	cout  <<st<<endl;
	cout << seed << endl;
	bin(second, 32); 
	bin(st,32);

	bin(ramdom_addrs^st,32);
	ofstream myfile;

	
	uint64_t  xored = seed | (xored <<31);
	xored = ((xored >> 31) | LFSR()) | xored;
	
	bin(xored,32);
	xored = xored >> 31;
	bin(xored, 32);
	myfile.open(fname);
	

	
	int a;
	


	uint32_t start_state = seed;/* Any nonzero start state will work. */
	uint32_t lfsr = start_state;
	uint64_t lfsr2= start_state;
	uint32_t bit;                    /* Must be 32bit to allow bit<<32 later in the code */
	unsigned period = 0;
	int otbit;
	do
	{
		/*  polynomial: x^32 + x^7 + x^6 + x^2 + x+1  */
		
		bit = ((lfsr >> 1) ^ (lfsr >> 5)  ^ (lfsr >> 6) ^ (lfsr >> 31)) & 1;
		lfsr = (lfsr >> 1) | (bit << 31);
		
		
		int xorbit = threbit();
		//Take The output from 2 32bit LFSRS and or them together to generate a 64 bit number
		uint64_t  xored = (lfsr | (xored << 31));     
		xored = ((xored >> 31) | LFSR()) | xored;


		
//lfsr = (LFSR() ^ lfsr) & xorbit;
//lfsr = LFSR();
		lfsr2= LFSR_64bit(xored);   //take the 64 bit number and input it to the LFSR
		
		otbit = (lfsr ^ lfsr2 ^xored ^seed) & 0x00000001;  //xor everything including the seed and take the first bit

		myfile << otbit;
		++period;
	} while (lfsr != start_state);

	cout<< "period " << period << " last val " << lfsr;



	myfile.close();

		//bin(LFSR() & 0x00000001, 32);
	cin >> a;
    return 0;
}

unsigned long LFSR() {
	static unsigned long ShiftRegister = seed;
	/* Anything but 0. */
	ShiftRegister =(((((ShiftRegister >> 31)
		^ (ShiftRegister >> 6)
		^ (ShiftRegister >> 4)
		^ (ShiftRegister >> 2)
		^ (ShiftRegister >> 1)
		^ ShiftRegister))
		& 0x00000001)
		<< 31)
		| (ShiftRegister >> 1);
	return ShiftRegister & 0x00000001;
}