#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <common.hpp>

using namespace std;



char* rotateLeft(char* n) {
	int l = strlen(n) ;
	int t = n[l - 1];
	n[l-1] = n[0];
	for (int i = 0; i < l - 2; ++i) {
		n[i] = n[i + 1];
	}
	n[l-2] = t;
	return n;
}

char* identifyZeros(char* num, char* nrev) {
     int l = strlen(num);
     for (int i = 0; i < l-1; ++i) { 
       int topl = num[i];
       int topr = num[i+1];
       int botl = nrev[i];
       int botr = nrev[i+1]; 

       int ce = topl*10 + topr;
       int be = botl*10 + botr;
       int rce = topr*10 + topl;
       int rbe = botr*10 + botl;

       if (_riemannExists(ce) && _riemannExists(be)) { //symmetry
	       int p1 = _getPosRiemann(ce);
	       int p2 = _getPosRiemann(be);
	       const char* exp1 = riemann_exponents[p1 - 1];
	       const char* exp2 = riemann_exponents[p2 - 1];
       } else if (_riemannExists(ce) && _riemannExists(rbe)) { //cross - symmetry
	       int p1 = _getPosRiemann(ce);
	       int p2 = _getPosRiemann(rbe);
       } else if (_riemannExists(rce) && _riemannExists(be)) { //cross - symmetry
	       int p1 = _getPosRiemann(rce);
	       int p2 = _getPosRiemann(be);
       } else if (_riemannExists(rce) & _riemannExists(rbe)) { //symmetry
	       int p1 = _getPosRiemann(rce);
	       int p2 = _getPosRiemann(rbe);
	       const char* exp1 = riemann_exponents[p1 - 1];
	       const char* exp2 = riemann_exponents[p2 - 1];
       } 
     }
}

char* factorize(char* num) {
	char* nrev = reverse_string(num);
	int l = strlen(num);
	std::string factor = "";
	for (int i = 0; i < ceil(l / 2.0); ++i) {
		factor += identifyZeros(num, nrev); 
		cout << "Number stack is :\n";
		cout << num <<"\n";
		cout << nrev <<"\n";
		rotateLeft(nrev);
	}
	return 0;
}

int main() {
	FILE* fp = fopen("./input.txt", "r");
	std::string numStr = "";
	char nn[100];
	while (fscanf(fp, "%s", nn) != EOF) {
		numStr += nn;
	}
	fclose(fp);
	char* num = strdup((char*) numStr.c_str());
	cout <<"Number Read was: \t"<<num<<"\n";
	char* factor = factorize(num);
}
