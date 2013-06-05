#include "testresults.hpp"
#include <stdio.h>

void TestResults::add(unsigned _v1) {
	
	FILE *f;
	f = fopen("testresults.rtr","a");
	char line[100];
	sprintf(line,"%u\n",_v1);
	fputs (line, f);
	fclose(f);
}


void TestResults::add(unsigned _v1, double _v2) {
	
	FILE *f;
	f = fopen("testresults.rtr","a");
	char line[100];
	sprintf(line,"%u %f\n",_v1, _v2);
	fputs (line, f);
	fclose(f);
}

void TestResults::add(unsigned _v1, unsigned _v2, unsigned _v3) {
	
	FILE *f;
	f = fopen("testresults.rtr","a");
	char line[100];
	sprintf(line,"%u %u %u\n",_v1, _v2, _v3);
	fputs (line, f);
	fclose(f);
}

