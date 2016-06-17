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
}

int countPrimes(char* z1, char* z2, char* z3, char* z4) {
}

int countPrimes(char* z1, char* z2, char* z3, char* z4, char* z5, char* z6) {
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
			cout << "Truncated exp1:\t"<< rexp1 << "\n";
			cout << "Truncated exp2:\t"<< rexp2 << "\n";
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
			int lastp1 = rexp1[10] - '0';
			int lastp2 = rexp2[10] - '0';
			int firstp1 = rexp1[0] - '0';
			int firstp2 = rexp2[0] - '0';
			int rz1 = lastp1*10 + firstp1;
			int _rz1 = reverse_number(rz1);
			int rz2 = lastp2*10 + firstp2;
			int _rz2 = reverse_number(rz2);

			char _rexp3[14];
			char _rexp4[14];
			char rexp3[14];
			char rexp4[14];
			rexp3[0] = _rexp3[0]= _rexp4[0] = rexp4[0] = '\0';
			if (ce == rbe) {
				if (_riemannExists(rz1)) {
					int p3 = _getPosRiemann(rz1);
					const char* exp3 = riemann_exponents[p3-1];
					strncpy(rexp3, exp3, 13);
					rexp3[13] = '\0';
					//cout << "Before Processing: Truncated exp1:\t"<< rexp3 << "\n";

					int carry = 0;
					int corr  = roundOff(rexp3[10]-'0', rexp3[11]-'0', rexp3[12]-'0', carry);
					rexp3[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (rexp3[i] == '9') { carry = 1; rexp3[i] = '0'; }
							else {
								carry = 0;
								rexp3[i] = carry + rexp3[i] + '0';
								break;
							} 
						}
					}
					rexp3[12] =  rexp3[11] = '\0';
				} else {
					cout << rz1 << " is not a Riemann Zero\n";
				}
				if (_riemannExists(_rz1)) {
					int p3 = _getPosRiemann(_rz1);
					const char* exp3 = riemann_exponents[p3-1];
					strncpy(_rexp3, exp3, 13);
					rexp3[13] = '\0';
					//cout << "Before Processing: Truncated exp1:\t"<< _rexp3 << "\n";

					int carry = 0;
					int corr  = roundOff(_rexp3[10]-'0', _rexp3[11]-'0', _rexp3[12]-'0', carry);
					_rexp3[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (_rexp3[i] == '9') { carry = 1; _rexp3[i] = '0'; }
							else {
								carry = 0;
								_rexp3[i] = carry + _rexp3[i] + '0';
								break;
							} 
						}
					}
					_rexp3[12] =  _rexp3[11] = '\0';
				} else {
					cout << _rz1 << " is not a Riemann Zero\n";
				}
			} else {
				if (_riemannExists(rz1)) {
					int p3 = _getPosRiemann(rz1);
					const char* exp3 = riemann_exponents[p3-1];
					strncpy(rexp3, exp3, 13);
					rexp3[13] = '\0';
					//cout << "Before Processing: Truncated exp1:\t"<< rexp3 << "\n";

					int carry = 0;
					int corr  = roundOff(rexp3[10]-'0', rexp3[11]-'0', rexp3[12]-'0', carry);
					rexp3[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (rexp3[i] == '9') { carry = 1; rexp3[i] = '0'; }
							else {
								carry = 0;
								rexp3[i] = carry + rexp3[i] + '0';
								break;
							} 
						}
					}
					rexp3[12] =  rexp3[11] = '\0';
				} else {
					cout << rz1 << " is not a Riemann Zero\n";
				}
				if (_riemannExists(_rz1)) {
					int p3 = _getPosRiemann(_rz1);
					const char* exp3 = riemann_exponents[p3-1];
					strncpy(_rexp3, exp3, 13);
					rexp3[13] = '\0';
					//cout << "Before Processing: Truncated exp1:\t"<< _rexp3 << "\n";

					int carry = 0;
					int corr  = roundOff(_rexp3[10]-'0', _rexp3[11]-'0', _rexp3[12]-'0', carry);
					_rexp3[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (_rexp3[i] == '9') { carry = 1; _rexp3[i] = '0'; }
							else {
								carry = 0;
								_rexp3[i] = carry + _rexp3[i] + '0';
								break;
							} 
						}
					}
					_rexp3[12] =  _rexp3[11] = '\0';
				} else {
					cout << _rz1 << " is not a Riemann Zero\n";
				}
				if (_riemannExists(rz2)) {
					int p4 = _getPosRiemann(rz2);
					const char* exp4 = riemann_exponents[p4-1];
					strncpy(rexp4, exp4, 13);
					rexp4[13] = '\0';
					//cout << "Before Processing: Truncated exp4:\t"<< rexp4 << "\n";

					int carry = 0;
					int corr  = roundOff(rexp4[10]-'0', rexp4[11]-'0', rexp4[12]-'0', carry);
					rexp4[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (rexp4[i] == '9') { carry = 1; rexp4[i] = '0'; }
							else {
								carry = 0;
								rexp4[i] = carry + rexp4[i] + '0';
								break;
							} 
						}
					}
					rexp4[12] =  rexp4[11] = '\0';
				} else {
					cout << rz2 << " is not a Riemann Zero\n";
				}
				if (_riemannExists(_rz2)) {
					int p4 = _getPosRiemann(_rz2);
					const char* exp4 = riemann_exponents[p4-1];
					strncpy(_rexp4, exp4, 13);
					_rexp4[13] = '\0';
					//cout << "Before Processing: Truncated exp4:\t"<< _rexp4 << "\n";

					int carry = 0;
					int corr  = roundOff(_rexp4[10]-'0', _rexp4[11]-'0', _rexp4[12]-'0', carry);
					_rexp4[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (_rexp4[i] == '9') { carry = 1; _rexp4[i] = '0'; }
							else {
								carry = 0;
								_rexp4[i] = carry + _rexp4[i] + '0';
								break;
							} 
						}
					}
					_rexp4[12] =  _rexp4[11] = '\0';
				} else {
					cout << _rz2 << " is not a Riemann Zero\n";
				}
			}
			int carry = 0;
			int corr  = roundOff(rexp1[10]-'0', rexp1[11]-'0', rexp1[12]-'0', carry);
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
				rexp2[12] =  rexp2[11] = '\0';
				cout << "Truncated exp1:\t"<< rexp1 << "\n";
				cout << "Truncated exp2:\t"<< rexp2 << "\n";
			}
			factor += boost::lexical_cast<std::string>(countPrimes(rexp1, rexp2, rexp3, _rexp3, rexp4, _rexp4));
			cout << "Truncated exp1:\t"<< rexp1 << "\n";
			cout << "Truncated exp2:\t"<< rexp2 << "\n";
			cout << "Truncated _exp3:\t"<< _rexp3 << "\n";
			cout << "Truncated _exp4:\t"<< _rexp4 << "\n";
			cout << "Truncated exp3:\t"<< rexp3 << "\n";
			cout << "Truncated exp4:\t"<< rexp4 << "\n";
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
			int lastp1 = rexp1[10] - '0';
			int lastp2 = rexp2[10] - '0';
			int firstp1 = rexp1[0] - '0';
			int firstp2 = rexp2[0] - '0';
			int rz1 = lastp1*10 + firstp1;
			int _rz1 = reverse_number(rz1);
			int rz2 = lastp2*10 + firstp2;
			int _rz2 = reverse_number(rz2);
			char _rexp3[14];
			char _rexp4[14];
			char rexp3[14];
			char rexp4[14];
			rexp3[0] = _rexp3[0]= _rexp4[0] = rexp4[0] = '\0';
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
			rexp1[12] =  rexp1[11] = '\0';
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
			rexp2[12] =  rexp2[11] = '\0';
			if (rce==be) {
				if (_riemannExists(rz1)) {
					int p3 = _getPosRiemann(rz1);
					const char* exp3 = riemann_exponents[p3-1];
					strncpy(rexp3, exp3, 13);
					rexp3[13] = '\0';
					//cout << "Before Processing: Truncated exp1:\t"<< rexp3 << "\n";

					int carry = 0;
					int corr  = roundOff(rexp3[10]-'0', rexp3[11]-'0', rexp3[12]-'0', carry);
					rexp3[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (rexp3[i] == '9') { carry = 1; rexp3[i] = '0'; }
							else {
								carry = 0;
								rexp3[i] = carry + rexp3[i] + '0';
								break;
							} 
						}
					}
					rexp3[12] =  rexp3[11] = '\0';
				} else {
					cout << rz1 << " is not a Riemann Zero\n";
				}
				if (_riemannExists(_rz1)) {
					int p3 = _getPosRiemann(_rz1);
					const char* exp3 = riemann_exponents[p3-1];
					strncpy(_rexp3, exp3, 13);
					rexp3[13] = '\0';
					//cout << "Before Processing: Truncated exp1:\t"<< _rexp3 << "\n";

					int carry = 0;
					int corr  = roundOff(_rexp3[10]-'0', _rexp3[11]-'0', _rexp3[12]-'0', carry);
					_rexp3[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (_rexp3[i] == '9') { carry = 1; _rexp3[i] = '0'; }
							else {
								carry = 0;
								_rexp3[i] = carry + _rexp3[i] + '0';
								break;
							} 
						}
					}
					_rexp3[12] =  _rexp3[11] = '\0';
				} else {
					cout << _rz1 << " is not a Riemann Zero\n";
				}
			} else {
				if (_riemannExists(rz1)) {
					int p3 = _getPosRiemann(rz1);
					const char* exp3 = riemann_exponents[p3-1];
					strncpy(rexp3, exp3, 13);
					rexp3[13] = '\0';
					//cout << "Before Processing: Truncated exp1:\t"<< rexp3 << "\n";

					int carry = 0;
					int corr  = roundOff(rexp3[10]-'0', rexp3[11]-'0', rexp3[12]-'0', carry);
					rexp3[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (rexp3[i] == '9') { carry = 1; rexp3[i] = '0'; }
							else {
								carry = 0;
								rexp3[i] = carry + rexp3[i] + '0';
								break;
							} 
						}
					}
					rexp3[12] =  rexp3[11] = '\0';
				} else {
					cout << rz1 << " is not a Riemann Zero\n";
				}
				if (_riemannExists(_rz1)) {
					int p3 = _getPosRiemann(_rz1);
					const char* exp3 = riemann_exponents[p3-1];
					strncpy(_rexp3, exp3, 13);
					rexp3[13] = '\0';
					//cout << "Before Processing: Truncated exp1:\t"<< _rexp3 << "\n";

					int carry = 0;
					int corr  = roundOff(_rexp3[10]-'0', _rexp3[11]-'0', _rexp3[12]-'0', carry);
					_rexp3[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (_rexp3[i] == '9') { carry = 1; _rexp3[i] = '0'; }
							else {
								carry = 0;
								_rexp3[i] = carry + _rexp3[i] + '0';
								break;
							} 
						}
					}
					_rexp3[12] =  _rexp3[11] = '\0';
				} else {
					cout << _rz1 << " is not a Riemann Zero\n";
				}
				if (_riemannExists(rz2)) {
					int p4 = _getPosRiemann(rz2);
					const char* exp4 = riemann_exponents[p4-1];
					strncpy(rexp4, exp4, 13);
					rexp4[13] = '\0';
					//cout << "Before Processing: Truncated exp4:\t"<< rexp4 << "\n";

					int carry = 0;
					int corr  = roundOff(rexp4[10]-'0', rexp4[11]-'0', rexp4[12]-'0', carry);
					rexp4[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (rexp4[i] == '9') { carry = 1; rexp4[i] = '0'; }
							else {
								carry = 0;
								rexp4[i] = carry + rexp4[i] + '0';
								break;
							} 
						}
					}
					rexp4[12] =  rexp4[11] = '\0';
				} else {
					cout << rz2 << " is not a Riemann Zero\n";
				}
				if (_riemannExists(_rz2)) {
					int p4 = _getPosRiemann(_rz2);
					const char* exp4 = riemann_exponents[p4-1];
					strncpy(_rexp4, exp4, 13);
					_rexp4[13] = '\0';
					//cout << "Before Processing: Truncated exp4:\t"<< _rexp4 << "\n";

					int carry = 0;
					int corr  = roundOff(_rexp4[10]-'0', _rexp4[11]-'0', _rexp4[12]-'0', carry);
					_rexp4[10] = corr + '0';
					if (carry > 0) {
						for (int i = 9; i >= 0; --i) {
							if (_rexp4[i] == '9') { carry = 1; _rexp4[i] = '0'; }
							else {
								carry = 0;
								_rexp4[i] = carry + _rexp4[i] + '0';
								break;
							} 
						}
					}
					_rexp4[12] =  _rexp4[11] = '\0';
				} else {
					cout << _rz2 << " is not a Riemann Zero\n";
				}
			}
			carry = 0;
			corr  = roundOff(rexp1[10]-'0', rexp1[11]-'0', rexp1[12]-'0', carry);
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
				rexp2[12] =  rexp2[11] = '\0';
				cout << "Truncated exp1:\t"<< rexp1 << "\n";
				cout << "Truncated exp2:\t"<< rexp2 << "\n";
			}
			factor += boost::lexical_cast<std::string>(countPrimes(rexp1, rexp2, rexp3, _rexp3, rexp4, _rexp4));
			cout << "Truncated exp1:\t"<< rexp1 << "\n";
			cout << "Truncated exp2:\t"<< rexp2 << "\n";
			cout << "Truncated _exp3:\t"<< _rexp3 << "\n";
			cout << "Truncated _exp4:\t"<< _rexp4 << "\n";
			cout << "Truncated exp3:\t"<< rexp3 << "\n";
			cout << "Truncated exp4:\t"<< rexp4 << "\n";

			rexp3[12] =  rexp3[11] = '\0';
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
