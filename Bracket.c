#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int top ;
	} 
	stack ;

stack * 
create_stack (int capacity, int unit) 
{
	stack * stack = malloc(sizeof(stack)) ;
	stack->capacity = capacity ;
	stack->unit = unit ;
	stack->top = 0 ;
	stack->buffer = (char *) calloc(capacity, unit) ;
	return stack ;
}

void
delete_stack (stack * stack) 
{
	if (stack->buffer != 0x0)
		free(stack->buffer) ;
	free(stack) ;
}

int 
is_empty (stack * stack) 
{
	return (stack->top == 0) ;
}

int 
is_full (stack * stack) 
{
	return (stack->top == stack->capacity) ;
}

int 
push (stack * stack, void * elem)
{
	if (is_full(stack))
		return 1 ;
	
	memcpy(stack->buffer + stack->top * stack->unit, elem, stack->unit) ;
	stack->top += 1 ;
	return 0 ;
}

int
pop (stack * stack, void * elem)
{
	if (is_empty(stack)) 
		return 1 ;
	
	memcpy(elem, stack->buffer + (stack->top - 1) * stack->unit, stack->unit) ;
	stack->top -= 1 ;
	return 0;
}

int
get_size (stack * stack) 
{
	return stack->top ;
}

int
get_element (stack * stack, int index, void * elem)
{
	if (stack->top <= index)
		return 1 ;

	memcpy(elem, stack->buffer + index * stack->unit, stack->unit) ;
	return 0 ;
}

int main()
{
    char bracket[100];
    int depth=0;
    char element[2];
    stack * st;

    scanf("%s", bracket);

    st=create_stack(strlen(bracket),sizeof(char));

    for(int i=0;i<strlen(bracket);i++){
        if(bracket[i]=='(' || bracket[i]=='{' || bracket[i]=='<' || bracket[i]=='['){
            push(st,&bracket[i]);
			if(depth<st->top){
				depth=st->top;
			}
        }
        else if(bracket[i]==')'){
            get_element(st,st->top-1,&element[0]);
            if(element[0]=='('){
                pop(st,&element[0]);
            }
            else{
                break;
            }
        }
        else if(bracket[i]=='}'){
            get_element(st,st->top-1,&element[0]);
            if(element[0]=='{'){
                pop(st,&element[0]);
            }
            else{
                break;
            }
        }
        else if(bracket[i]=='>'){
            get_element(st,st->top-1,&element[0]);
            if(element[0]=='<'){
                pop(st,&element[0]);
            }
            else{
                break;
            }
        }
        else if(bracket[i]==']'){
            get_element(st,st->top-1,&element[0]);
            if(element[0]=='['){
                pop(st,&element[0]);
            }
            else{
                break;
            }
        }
    }
    if(st->top!=0){
        printf("invalid\n");
    }
    else{
        printf("%d\n", depth);
    }
}
