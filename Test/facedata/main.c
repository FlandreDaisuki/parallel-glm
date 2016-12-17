#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	FILE *fp = fopen("a.txt", "r");
	char buf[200];
	char tmp[4][200]={{0}};
	int v, t, n;
	char pattern[4][10] = {"%d//%d", "%d", "%d/%d", "%d/%d/%d"};
	int mode = -1;

	while (fgets(buf, sizeof(buf), fp)) {
		int voff = sscanf(buf, "%*s %s %s %s %s",
		       tmp[0], tmp[1], tmp[2], tmp[3]); // vertices of face
		
		if(sscanf(tmp[0], "%d//%d", &v, &n) == 2) {
			mode = 0;
		} else {
			mode = sscanf(tmp[0], "%d/%d/%d", &v, &t, &n);
		}
		
		for (int i = 0; i < voff; ++i)
		{
			v = t = n = 0;
			if(mode == 0) {
				sscanf(tmp[i], pattern[mode], &v, &n);
			} else {
				sscanf(tmp[i], pattern[mode], &v, &t, &n);
			}
			printf("[v %d, t %d, n %d] ", v, t, n);
		}
		puts("");
	}
	return 0;
}