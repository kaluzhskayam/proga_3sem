#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* a = fopen("one.c", "r+");
	FILE* b = fopen("two.c", "a+");
	char* str1 = (char*)calloc(10, sizeof(char));
	size_t size;
	while(fgets(str1, 100, a) != NULL)
	{
		size = fwrite(str1, sizeof(char), 20, b);
	}
	free(str1);
	fclose(a);
	fclose(b);
	return 0;
}
