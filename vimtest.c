#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mk_randint(int n[], int first, int last, int size);

int main(void){
  int numarray[100], i;
  int f,l,s;
  srand(time(0));
  printf("Enter first, last, size > ");
  scanf("%d %d %d", &f, &l, &s);
  mk_randint(numarray,f,l,s);
  for(int i=0; i<s; i++){
    printf("%d ", numarray[i]);
  }
  printf("\n");
  return 0;
}

void mk_randint(int n[], int first, int last, int size){
  for(int i=0; i<size; i++){
    n[i]=rand()%(last-first+1)+first;
  }
}
