#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <common.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost;
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

int roundOff(int x, int y, int z, int& c) {
	if (y < 5) {
		return x;
	} else if (y> 5) {
		if (x== 9) c = 1;
		return (x + 1) % 10;
	} else if (y == 5) {
		if (z >= 5) { 
			if (x== 9) c = 1;
			return (x + 1) % 10;
		} else {
			return x;
		}
	}
	return x;
}

int countPrimes(char* z1, char* z2) {
	int offset = 2;
	int cnt = 0;
	for (int i =  offset; i < 11; ++i) {
		int z1k = z1[i] - '0';
		int z2k = z2[i] - '0';
		int e = z1k*10 + z2k;
		int r = z2k*10 + z1k;
		if (isPrime(e) ) {
			++cnt;
		} 
                if (isPrime(r)) {
			++cnt;
		}
	}
	return cnt;
}

char* identifyZeros(char* num, char* nrev) {
	int l = strlen(num);
	std::string factor = "";
	for (int i = 0; i < l-1; ++i) { 
		int topl = num[i]-'0';
		int topr = num[i+1]-'0';
		int botl = nrev[i]-'0';
		int botr = nrev[i+1]-'0'; 

		int ce = topl*10 + topr;
		int be = botl*10 + botr;
		int rce = topr*10 + topl;
		int rbe = botr*10 + botl;

		if (_riemannExists(ce) && _riemannExists(be)) { //symmetry
			int p1 = _getPosRiemann(ce);
			int p2 = _getPosRiemann(be);
			const char* exp1 = riemann_exponents[p1 - 1];
			const char* exp2 = riemann_exponents[p2 - 1];
			char rexp1[14];
			char rexp2[14];
			strncpy(rexp1, exp1, 13);
			strncpy(rexp2, exp2, 13);
			rexp1[13] = '\0';
			rexp2[13] = '\0';
			cout << "Before Processing: Truncated exp1:\t"<< rexp1 << "\n";
			cout << "Before Processing: Truncated exp2:\t"<< rexp2 << "\n";
			int carry = 0;
			int corr = roundOff(rexp1[10]-'0', rexp1[11]-'0', rexp1[12]-'0', carry);
			rexp1[10] = corr + '0';
			if (carry > 0) {
				for (int i = 9; i >= 0; --i) {
					if (rexp1[i] == 9) { carry = 1; rexp1[i] = '0'; }
					else {
						carry = 0;
						rexp1[i] = carry + rexp1[i] + '0';
						break;
					} 
				}
			}
			rexp1[12] = rexp1[11] = '\0';
			carry = 0;
			corr = roundOff(rexp2[10]-'0', rexp2[11]-'0', rexp2[12]-'0', carry);
			rexp2[10] = corr + '0';
			if (carry > 0) {
				for (int i = 9; i >= 0; --i) {
					if (rexp2[i] == 9) { carry = 1; rexp2[i] = '0'; }
					else {
						carry = 0;
						rexp2[i] = carry + rexp2[i] + '0';
						break;
					} 
				}
			}
			rexp2[12] = rexp2[11] =  '\0';
			cout << "Truncated exp1:\t"<< rexp1 << "\n";
			cout << "Truncated exp2:\t"<< rexp2 << "\n";
			factor += boost::lexical_cast<std::string>(countPrimes(rexp1, rexp2));
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
			char rexp1[14];
			char rexp2[14];
			strncpy(rexp1, exp1, 13);
			strncpy(rexp2, exp2, 13);
			rexp1[13] = '\0';
			rexp2[13] = '\0';
			cout << "Before Processing: Truncated exp1:\t"<< rexp1 << "\n";
			cout << "Before Processing: Truncated exp2:\t"<< rexp2 << "\n";
			int carry = 0;
			rexp1[10] = roundOff(rexp1[10]-'0', rexp1[11]-'0', rexp1[12]-'0', carry);
			if (carry > 0) {
				for (int i = 9; i >= 0; --i) {
					if (rexp1[i] == 9) { carry = 1; rexp1[i] = 0; }
					else {
						carry = 0;
						rexp1[i] = carry + rexp1[i];
						break;
					} 
				}
			}
			rexp1[12] =  rexp1[11] = '\0';
			rexp2[10] = roundOff(rexp2[10]-'0', rexp2[11]-'0', rexp2[12]-'0', carry);
			if (carry > 0) {
				for (int i = 9; i >= 0; --i) {
					if (rexp2[i] == 9) { carry = 1; rexp2[i] = 0; }
					else {
						carry = 0;
						rexp2[i] = carry + rexp2[i];
						break;
					} 
				}
			}
			rexp2[12] =  rexp2[11] = '\0';
			cout << "Truncated exp1:\t"<< rexp1 << "\n";
			cout << "Truncated exp2:\t"<< rexp2 << "\n";
			factor += boost::lexical_cast<std::string>(countPrimes(rexp1, rexp2));
		} 
	}
	return strdup((char*) factor.c_str());
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
	return strdup((char*) factor.c_str());
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
	if (factor) {
		cout << "\nFactor:\t"<< factor<<"\n";
	}
}
