#include <stdio.h>

int main() {
	FILE* fp = fopen("./input.txt", "r");
	char nn[100];
	while (fscanf(fp, "%s", nn) != EOF) {
		printf("%s", nn);
	}
	fclose(fp);
}
