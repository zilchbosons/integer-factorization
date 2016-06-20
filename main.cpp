#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <common.hpp>
#include <vector>
#include <algorithm>
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

struct A {
	bool operator()(char* a, char* b)
	{   
		return strcmp(a, b) < 0;
	}   
} customLess;

int countPrimes(char* z1, char* z2) {
	int l = strlen(z1);
	int cnt = 0;
	for (int i = 0; i < l ; ++i ) {
		int z1k = ((strlen(z1)==0)? -1:(z1[i] - '0'));
		int z2k = ((strlen(z2)==0)? -1:(z2[i] - '0'));

		int ce = 0, rce = 0;
		if (z1k == -1) {
			ce = z2k;
			rce = z2k;
		} else if (z2k == -1) {
			ce = z1k;
			rce = z1k;
		} else {
			ce = z1k*10 + z2k;
			rce = z2k*10 + z1k;
		}
		if (isPrime(ce) || isPrime(rce) ) {
			++cnt;
		} 
	}
	cout << "\n 2-way Primes: \t"<<cnt<<"\n";
	return 0;
}

int countPrimes(char* z1, char* z2, char* z3, char* z4, char* z5, char* z6) {
	vector<char*> test;
	int l = 0;
	if (strlen(z1)>0) {
		l = strlen(z1);
		test.push_back(z1);
	}
	if (strlen(z2) > 0) {
		l = strlen(z2);
		test.push_back(z2);
	}
	if (strlen(z3) > 0) {
		l = strlen(z3);
		test.push_back(z3);
	}
	if (strlen(z4) > 0) {
		l = strlen(z4);
		test.push_back(z4);
	}
	if (strlen(z5) > 0) {
		l = strlen(z5);
		test.push_back(z5);
	}
	if (strlen(z6) > 0) {
		l = strlen(z6);
		test.push_back(z6);
	}
	test.erase(
			std::unique(test.begin(), test.end()),
			test.end());
	std::sort(test.begin(), test.end(), customLess);
	int cnt = 0;
	int zk[6];
	for (int j = 0; j < test.size() ; ++j) {
		cnt = 0;
		for (int i = 0; i < l; ++i ) {
			zk[0] = zk[1] = zk[2] = zk[3] = zk[4] = zk[5] = -1;
			if (test.size() > 0) {
				zk[0] = test[0][i] - '0';
			}
			if (test.size() > 1) {
				zk[1] = test[1][i] - '0';
			}
			if (test.size() > 2) {
				zk[2] = test[2][i] - '0';
			}
			if (test.size() > 3) {
				zk[3] = test[3][i] - '0';
			}
			if (test.size() > 4) {
				zk[4] = test[4][i] - '0';
			}
			if (test.size() > 5) {
				zk[5] = test[5][i] - '0';
			}
			int ce = 0, rce = 0;
			ce = zk[0]*10 + zk[1];
			rce = zk[1]*10 + zk[0];
			if (isPrime(ce) || isPrime(rce)) {
				if (zk[2] > -1) {
					ce = zk[1]*10 + zk[2];
					rce = zk[2]*10 + zk[1];
					if (isPrime(ce) || isPrime(rce)) {
						if (zk[3] > -1) {
							ce = zk[2]*10 + zk[3];
							rce = zk[3]*10 + zk[2];
							if (isPrime(ce) || isPrime(rce)) {
								if (zk[4] > -1) {
									ce = zk[3] *10 + zk[4];
									rce = zk[4]*10 + zk[3];
									if (isPrime(ce) || isPrime(rce)) {
										if (zk[5] > -1) {
											ce = zk[4]*10 + zk[5];
											rce = zk[5]*10 + zk[4];
											if (isPrime(ce) || isPrime(rce)) {
												++cnt;
											}
										} else {
											if (test.size()==5) {
												++cnt;
											}
										}
									}
								} else {
									if (test.size()==4) {
										++cnt;
									}
								}
							}
						} else {
							if (test.size()==3) {
								++cnt;
							}
						}
					}
				} else {
					if (test.size()==2) {
						++cnt;
					}
				}
			}
		} 
		cout << "\n @Rotation: \t"<<j<<"\t6-way Primes:\t"<<cnt<<"\n";
		std::rotate(test.begin(), test.begin()+1, test.end());
	}
	return 0;
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
			cout << "\nSymmetry #1\n";
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
			//cout << "Before Processing: Truncated exp1:\t"<< rexp1 << "\n";
			//cout << "Before Processing: Truncated exp2:\t"<< rexp2 << "\n";
			int carry = 0;
			int corr = roundOff(rexp1[10]-'0', rexp1[11]-'0', rexp1[12]-'0', carry);
			rexp1[10] = corr + '0';
			if (carry > 0) {
				for (int i = 9; i >= 0; --i) {
					if (rexp1[i] == '9') { carry = 1; rexp1[i] = '0'; }
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
					if (rexp2[i] == '9') { carry = 1; rexp2[i] = '0'; }
					else {
						carry = 0;
						rexp2[i] = carry + rexp2[i] + '0';
						break;
					} 
				}
			}
			rexp2[12] = rexp2[11] =  '\0';
//			cout << "Truncated exp1:\t"<< rexp1 << "\n";
//			cout << "Truncated exp2:\t"<< rexp2 << "\n";
			factor += boost::lexical_cast<std::string>(countPrimes(rexp1, rexp2));
		} 
		if (_riemannExists(ce) && _riemannExists(rbe)) { //cross - symmetry
			cout << "\nCross Symmetry #1\n";
			int p1 = _getPosRiemann(ce);
			int p2 = _getPosRiemann(rbe);
			const char* exp1 = riemann_exponents[p1 - 1];
			const char* exp2 = riemann_exponents[p2 - 1];
			char rexp1[14];
			char rexp2[14];
			strncpy(rexp1, exp1, 13);
			strncpy(rexp2, exp2, 13);
			rexp1[13] = '\0';
			rexp2[13] = '\0';
			//cout << "Before Processing: Truncated exp1:\t"<< rexp1 << "\n";
			//cout << "Before Processing: Truncated exp2:\t"<< rexp2 << "\n";
			int carry = 0;
			int corr = roundOff(rexp1[10]-'0', rexp1[11]-'0', rexp1[12]-'0', carry);
			rexp1[10] = corr + '0';
			if (carry > 0) {
				for (int i = 9; i >= 0; --i) {
					if (rexp1[i] == '9') { carry = 1; rexp1[i] = '0'; }
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
					if (rexp2[i] == '9') { carry = 1; rexp2[i] = '0'; }
					else {
						carry = 0;
						rexp2[i] = carry + rexp2[i] + '0';
						break;
					} 
				}
			}
			rexp2[12] = rexp2[11] =  '\0';
//			cout << "Truncated exp1:\t"<< rexp1 << "\n";
//			cout << "Truncated exp2:\t"<< rexp2 << "\n";
			factor += boost::lexical_cast<std::string>(countPrimes(rexp1, rexp2));
		} 
		if (_riemannExists(rce) && _riemannExists(be)) { //cross - symmetry
			cout << "\nCross Symmetry #2\n";
			int p1 = _getPosRiemann(rce);
			int p2 = _getPosRiemann(be);
			const char* exp1 = riemann_exponents[p1 - 1];
			const char* exp2 = riemann_exponents[p2 - 1];
			char rexp1[14];
			char rexp2[14];
			strncpy(rexp1, exp1, 13);
			strncpy(rexp2, exp2, 13);
			rexp1[13] = '\0';
			rexp2[13] = '\0';
			//cout << "Before Processing: Truncated exp1:\t"<< rexp1 << "\n";
			//cout << "Before Processing: Truncated exp2:\t"<< rexp2 << "\n";
			int carry = 0;
			int corr = roundOff(rexp1[10]-'0', rexp1[11]-'0', rexp1[12]-'0', carry);
			rexp1[10] = corr + '0';
			if (carry > 0) {
				for (int i = 9; i >= 0; --i) {
					if (rexp1[i] == '9') { carry = 1; rexp1[i] = '0'; }
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
					if (rexp2[i] == '9') { carry = 1; rexp2[i] = '0'; }
					else {
						carry = 0;
						rexp2[i] = carry + rexp2[i] + '0';
						break;
					} 
				}
			}
			rexp2[12] = rexp2[11] =  '\0';
//			cout << "Truncated exp1:\t"<< rexp1 << "\n";
//			cout << "Truncated exp2:\t"<< rexp2 << "\n";
			factor += boost::lexical_cast<std::string>(countPrimes(rexp1, rexp2));
		} 
		if (_riemannExists(rce) & _riemannExists(rbe)) { //symmetry
			cout << "\nSymmetry #2\n";
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
			//cout << "Before Processing: Truncated exp1:\t"<< rexp1 << "\n";
			//cout << "Before Processing: Truncated exp2:\t"<< rexp2 << "\n";
			int carry = 0;
			int corr =  roundOff(rexp1[10]-'0', rexp1[11]-'0', rexp1[12]-'0', carry);
			rexp1[10] = corr + '0';
			if (carry > 0) {
				for (int i = 9; i >= 0; --i) {
					if (rexp1[i] == '9') { carry = 1; rexp1[i] = '0'; }
					else {
						carry = 0;
						rexp1[i] = carry + rexp1[i] + '0';
						break;
					} 
				}
			}
			rexp1[12] =  rexp1[11] = '\0';
			corr  = roundOff(rexp2[10]-'0', rexp2[11]-'0', rexp2[12]-'0', carry);
			rexp2[10] = corr + '0';
			if (carry > 0) {
				for (int i = 9; i >= 0; --i) {
					if (rexp2[i] == '9') { carry = 1; rexp2[i] = '0'; }
					else {
						carry = 0;
						rexp2[i] = carry + rexp2[i] + '0';
						break;
					} 
				}
			}
			rexp2[12] =  rexp2[11] = '\0';
//			cout << "Truncated exp1:\t"<< rexp1 << "\n";
//			cout << "Truncated exp2:\t"<< rexp2 << "\n";
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
		cout <<"\nIteration #\t"<< i + 1 <<"\n";
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
