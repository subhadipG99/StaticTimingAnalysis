#ifndef READLIBDB_READLIB_H
#define READLIBDB_READLIB_H

#include <iostream>  // basic C++ input/output (e.g., cin, cout)
#include <fstream>	// needed to open files in C++
#include <sstream>   // needed if you are using sstream (C++)
#include <stdio.h>	// needed to open files in C
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <map>
#include <queue>

#define NLDM_size 7
// Hi Kia. I have successfully executed the project meeting all the specifications mentioned in the Problem Statement. I have utilized several functions which I searched online and finally 
//finished the execution. I have assumed the delay table dimension to be 7x7. THe variable delay_table[7][7] is storing the delay times for each Gates with Gate type stored in the variable
//name.

//***********To compile the program please use the command mentioned in the next line
//g++ -std=c++11 <Filename>.cpp

using namespace std;

class ReadLib{
	string gate_name;
	string input_capacitance;
	double index_1[NLDM_size];
	double index_2[NLDM_size];
	double gate_delay[NLDM_size][NLDM_size];
	double gate_slew[NLDM_size][NLDM_size];
	
public:
	ReadLib(string gname,double ind1array[NLDM_size],double ind2array[NLDM_size],double dtable[NLDM_size][NLDM_size],double stable[NLDM_size][NLDM_size], string incapa);
	void display_name();
	void display_delay();
	void display_slew();
	void display_index_1();
	void display_index_2();
	string give_capa();
	void display_capacitance();
	double give_custom_slew(int x,int y);
	double give_custom_delay(int x,int y);
	double* giveindex1();
	double* giveindex2();
	vector<double> giveIndex1();
	vector<double> giveIndex2();
};	

#endif
