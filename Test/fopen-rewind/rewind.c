#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char buf[200];
	FILE *fp = fopen("house.obj", "r");
	int N;
	sscanf(argv[1], "%d", &N);
    for (int i = 0; i < N; ++i)
    {
		while (fgets(buf, sizeof(buf), fp));
		rewind(fp);
    }
	fclose(fp);
    return 0;
}