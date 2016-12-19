#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char buf[200];
	int N;
	sscanf(argv[1], "%d", &N);
	for (int i = 0; i < N; ++i)
    {
		FILE *fp = fopen("house.obj", "r");

		while (fgets(buf, sizeof(buf), fp));
		fclose(fp);
    }
    return 0;
}