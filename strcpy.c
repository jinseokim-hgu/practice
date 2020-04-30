#include <stdio.h>
#include <string.h>

int main(){
	char input[]="12345";
	char output[10];

	strcpy(output,&input[1]);

	printf("%s\n", output);

	return 0;
}
