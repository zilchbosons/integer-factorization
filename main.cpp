#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
using namespace std;

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
}
