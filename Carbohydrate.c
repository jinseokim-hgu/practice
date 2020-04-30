#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum { Integer, Element, Open } token_type ;

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int top ;
	}
	stack ;

typedef struct {
	int integer ;
	char element ;
    char open ;
	token_type type ;
} token_t ;

stack * 
create_stack (int capacity, int unit) 
{
	stack * st = malloc(sizeof(stack)) ;
	st->capacity = capacity ;
	st->unit = unit ;
	st->top = 0 ;
	st->buffer = calloc(capacity, unit) ;
	return st ;
}

void
delete_stack (stack * st) 
{
	if (st->buffer != 0x0)
		free(st->buffer) ;
	free(st) ;
}

int 
is_empty (stack * st) 
{
	return (st->top == 0) ;
}

int 
is_full (stack * st) 
{
	return (st->top == st->capacity) ;
}

int 
push (stack * st, void * elem)
{
	if (is_full(st))
		return 1 ;

	memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit) ;
	st->top += 1 ;

	return 0 ;
}

int
pop (stack * st, void * elem)
{
	if (is_empty(st)) 
		return 1 ;
	
	memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit) ;
	st->top -= 1 ;
	return 0;
}

int
get_size (stack * st) 
{
	return st->top ;
}

int
get_element (stack * st, int index, void * elem)
{
	if (st->top <= index)
		return 1 ;

	memcpy(elem, st->buffer + index * st->unit, st->unit) ;
	return 0 ;
}

void
print_stack (stack * st)
{
	int i ;
	for (i = 0 ; i < get_size(st) ; i++) {
		token_t tok ;
		get_element(st, i, &tok) ;
		if (tok.type == Element) 
			printf("[%c] ", tok.element) ;
		else if (tok.type == Integer)
			printf("[%d] ", tok.integer) ;
		else 
			printf("[(] ") ;
	}
	printf(".\n") ;
}

int main()
{
    int i=0;
    int molecule=0;
    int term=0;
    int size;

    token_t tok;
    stack * st1;
    stack * st2;
    st1=create_stack(100,sizeof(token_t));
    st2=create_stack(100,sizeof(token_t));

    tok.type = Open ;
	push(st1, &tok) ;

    int output[100];
    char input[100];
    scanf("%s", input);

    do{
        if(input[i]=='('){
            token_t tok ;
            tok.type = Open ;
            push(st1, &tok) ;
        }
        else if(isalpha(input[i])){
            token_t tok ;
            tok.type = Element ;
            tok.element = input[i];
            push(st1, &tok) ;
        }
        else if(input[i]==')' || input[i]=='\0'){
            token_t temp,temp2,top;
            do{
                while(temp.type!=Open){
                    pop(st1, &temp);
                    push(st2, &temp);
                }
                pop(st2, &temp);
                if(temp.type==Element){
                    pop(st2, &temp2);
                    if(temp2.type==Element){
                        push(st2, &temp2);
                        push(st1, &temp);
                    }
                    else{
                        push(st1, &temp);
                        temp2.integer*=atoi(&input[i+1]);
                        push(st1, &temp2);
                    }
                }
            }while(top.type!=Open);
        }
        else if(isdigit(input[i]) && isalpha(input[i-1])){
            token_t tok;
            tok.type = Integer;
            tok.integer = atoi(&input[i]);
            push(st1, &tok);
        }
        i++;
    }while(input[i-1] != '\0');

    for(int i=get_size(st1)-1;i>=0;i--){
        size=get_size(st1);
        token_t temp;
        pop(st1, &temp);
        if(temp.type==Element){
            if(temp.element=='C'){
                output[i]=12;
            }
            else if(temp.element=='O'){
                output[i]=16;
            }
            else{
                output[i]=1;
            }
        }
        else if(temp.type==Integer){
            output[i]=temp.integer;
        }
    }

    for(int i=1;i<size;i++){
        if(output[i]>1 && output[i]<10){
            molecule+=output[i-1]*output[i];
        }
        else{
            molecule+=output[i-1];
        }
    }
    printf("%d\n", molecule);
    delete_stack(st1);
    delete_stack(st2);
    return 0;
}
