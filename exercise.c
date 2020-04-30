#include <stdio.h>
#define N 10
int main(void) {
	char s_gets[N], s_fgets[N];
	
	printf("Read by gets()>");
	gets(s_gets);

	printf("Read by fgets()>");
	fgets(s_fgets,N-1,stdin);

	printf("\nInput: s_gets and s_fgets\n");
	printf("s_gets: %s\n",s_gets);
	printf("s_fgets: %s\n",s_fgets);

	printf("-----------------\n");

	printf("\nInput: s_fgets and s_gets\n");
	printf("s_fgets: %s\n",s_fgets);
	printf("s_gets: %s\n",s_gets);

	printf("-----------------\n");

	return 0;
}
