#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
			void * element ;
				struct node * left ; 
					struct node * right ;
} ;

typedef struct node node_t ;
typedef struct node linkedlist_t ;

linkedlist_t * 
linkedlist_alloc (int unit) 
{
			linkedlist_t * l = (linkedlist_t *) malloc(sizeof(linkedlist_t)) ;
				l->left = l  ;	
					l->right = l ;
						l->element = malloc(sizeof(int)) ;
							int * u = (int *) l->element ;
								*u = unit ;

									return l ;
}

void
linkedlist_free (linkedlist_t * l)
{
			node_t * curr ;
				node_t * next ;

					curr = l->right ;
						while (curr != l) {
										next = curr->right ;
												free(curr->element) ;
														free(curr) ;
																curr = next ;
																	}
																		free(l->element) ;
																			free(l) ;
}

int 
linkedlist_length (linkedlist_t * l)
{
			int len = 0 ;

				node_t * curr = l->right ;
					while (curr != l) {
									len += 1 ;
											curr = curr->right ; 
												}
													return len ; 
}

void 
linkedlist_insert (node_t * left, void * e, int unit)
{
			node_t * _new = (node_t *) malloc(sizeof(node_t)) ;
				_new->element = malloc(unit) ;
					memcpy(_new->element, e, unit) ;

						node_t * right = left->right ;

							_new->left = left ;
								_new->right = right ;

									left->right = _new ;
										right->left = _new ;
}

void
linkedlist_insert_first (linkedlist_t * l, void * e)
{
			linkedlist_insert(l, e, *((int *)(l->element))) ;
}

void
linkedlist_insert_last (linkedlist_t * l, void * e)
{
			linkedlist_insert(l->left, e, *((int *)(l->element))) ;
}

int
linkedlist_remove (linkedlist_t * l, node_t * n)
{
			if (l->left == l)
							return 1 ;

								n->left->right = n->right ;
									n->right->left = n->left ;

										free(n->element) ;
											free(n) ;
												return 0 ;
}

int 
linkedlist_remove_first (linkedlist_t * l, void * e)
{
			if (l->right == l)
							return 1 ;

								memcpy(e, l->right->element, *((int *)(l->element))) ;
									linkedlist_remove(l, l->right) ;
										return 0 ;
}

int
linkedlist_remove_last (linkedlist_t * l, void * e)
{
			if (l->left == l)
							return 1 ;

								memcpy(e, l->left->element, *((int *)(l->element))) ;
									linkedlist_remove(l, l->left) ;
										return 0 ;
}

int 
linkedlist_get (linkedlist_t * l, int pos, void * e)
{
			if (pos < 0)
							return 1 ;

								int unit = *((int *) l->element) ;
									int i = 0 ;
										node_t * curr = l->right ;
											while (i < pos && curr != l) {
															curr = curr->right ;
																	i += 1 ;
																		}
																			if (i != pos)
																							return 1 ;

																								memcpy(e, curr->element, unit) ;
																									return 0 ;
}

int main()
{
		    char RE[128];
			    char input[5][128];
				    char output[128];
					    char empty[]="\0";
						    int size=0;

							    scanf("%s", RE);

								    for(int i=0;i<5;i++){
											        scanf("%s", input[i]);
													    }

														    linkedlist_t * l ;
															    linkedlist_t * bracket ; 
																	l = linkedlist_alloc(128*sizeof(char)) ;

																	    for(int i=0; i<5; i++){
																				        linkedlist_insert_last(l, input[i]);

																						        for(int j=0; j<strlen(RE); j++){
																										            int flag=0;

																													            if(RE[j]=='*'){
																																		                size=linkedlist_length(l);
																																						                for(int k=0; k<size; k++){
																																												                    char temp1[128];
																																																	                    linkedlist_remove_first(l,temp1);

																																																						                    for(int a=0; a<strlen(temp1); a++){
																																																													                        char temp2[128];
																																																																			                        strcpy(temp2,&temp1[a]);
																																																																									                        linkedlist_insert_last(l,temp2);
																																																																															                    }
																																																																																				                }
																																																																																								                linkedlist_insert_last(l,empty);
																																																																																												            }
																																																																																															            else if(islower(RE[j])!=0 && flag==0){
																																																																																																				                size=linkedlist_length(l);
																																																																																																								                for(int k=0; k<size; k++){
																																																																																																														                    char temp1[128];
																																																																																																																			                    linkedlist_remove_first(l,temp1);

																																																																																																																								                    if(temp1[0]==RE[j] && strlen(temp1)==1){
																																																																																																																															                        linkedlist_insert_last(l,empty);
																																																																																																																																					                    }
																																																																																																																																										                    else if(temp1[0]==RE[j] && 1<strlen(temp1)){
																																																																																																																																																	                        char temp2[128];
																																																																																																																																																							                        strcpy(temp2,&temp1[1]);
																																																																																																																																																													                        linkedlist_insert_last(l,temp2);
																																																																																																																																																																			                    }
																																																																																																																																																																								                }
																																																																																																																																																																												            }
																																																																																																																																																																															            else if(RE[j]=='?'){
																																																																																																																																																																																				                size=linkedlist_length(l);
																																																																																																																																																																																								                for(int k=0; k<size; k++){
																																																																																																																																																																																														                    char temp1[128];
																																																																																																																																																																																																			                    linkedlist_remove_first(l,temp1);
																																																																																																																																																																																																								                    
																																																																																																																																																																																																													                    if(temp1[0]==RE[j] && strlen(temp1)==1){
																																																																																																																																																																																																																				                        linkedlist_insert_last(l,empty);
																																																																																																																																																																																																																										                    }
																																																																																																																																																																																																																															                    else if(islower(temp1[0]) && 1<strlen(temp1)){
																																																																																																																																																																																																																																						                        char temp2[128];
																																																																																																																																																																																																																																												                        strcpy(temp2,&temp1[1]);
																																																																																																																																																																																																																																																		                        linkedlist_insert_last(l,temp2);
																																																																																																																																																																																																																																																								                    }
																																																																																																																																																																																																																																																													                }
																																																																																																																																																																																																																																																																	            }
																																																																																																																																																																																																																																																																				            else if(RE[j]=='!'){
																																																																																																																																																																																																																																																																									                size=linkedlist_length(l);
																																																																																																																																																																																																																																																																													                for(int k=0; k<size; k++){
																																																																																																																																																																																																																																																																																			                    char temp1[128];
																																																																																																																																																																																																																																																																																								                    linkedlist_remove_first(l,temp1);

																																																																																																																																																																																																																																																																																													                    char temp2[128];
																																																																																																																																																																																																																																																																																																		                    if(temp1[0]==RE[j] && strlen(temp1)==1){
																																																																																																																																																																																																																																																																																																									                        linkedlist_insert_last(l,empty);
																																																																																																																																																																																																																																																																																																															                    }
																																																																																																																																																																																																																																																																																																																				                    else if(temp1[0]==RE[j] && 1<strlen(temp1)){
																																																																																																																																																																																																																																																																																																																											                        strcpy(temp2,&temp1[1]);
																																																																																																																																																																																																																																																																																																																																	                        linkedlist_insert_last(l,temp2);
																																																																																																																																																																																																																																																																																																																																							                    }
																																																																																																																																																																																																																																																																																																																																												                    linkedlist_insert_last(l,temp1);
																																																																																																																																																																																																																																																																																																																																																	                }
																																																																																																																																																																																																																																																																																																																																																					            }
																																																																																																																																																																																																																																																																																																																																																								            else if(RE[j]=='['){
																																																																																																																																																																																																																																																																																																																																																													                flag=1;
																																																																																																																																																																																																																																																																																																																																																																		            bracket = linkedlist_alloc(128*sizeof(char)) ;
																																																																																																																																																																																																																																																																																																																																																																					                size=linkedlist_length(l);
																																																																																																																																																																																																																																																																																																																																																																									                for(int k=0; k<size; k++){
																																																																																																																																																																																																																																																																																																																																																																															                    char temp1[128];
																																																																																																																																																																																																																																																																																																																																																																																				                    linkedlist_remove_first(l,temp1);
																																																																																																																																																																																																																																																																																																																																																																																									                    linkedlist_insert_last(bracket,temp1);
																																																																																																																																																																																																																																																																																																																																																																																														                }
																																																																																																																																																																																																																																																																																																																																																																																																		            }
																																																																																																																																																																																																																																																																																																																																																																																																					            else if(RE[j]==']'){
																																																																																																																																																																																																																																																																																																																																																																																																										                flag=0;
																																																																																																																																																																																																																																																																																																																																																																																																														                linkedlist_free(bracket);
																																																																																																																																																																																																																																																																																																																																																																																																																		            }
																																																																																																																																																																																																																																																																																																																																																																																																																					            else if(islower(RE[j])!=0 && flag==1){
																																																																																																																																																																																																																																																																																																																																																																																																																										                size=linkedlist_length(bracket);
																																																																																																																																																																																																																																																																																																																																																																																																																														                for(int k=0; k<size; k++){
																																																																																																																																																																																																																																																																																																																																																																																																																																				                    char temp1[128];
																																																																																																																																																																																																																																																																																																																																																																																																																																									                    linkedlist_get(bracket,k,temp1);

																																																																																																																																																																																																																																																																																																																																																																																																																																														                    if(temp1[0]==RE[j] && strlen(temp1)==1){
																																																																																																																																																																																																																																																																																																																																																																																																																																																					                        linkedlist_insert_last(l,empty);
																																																																																																																																																																																																																																																																																																																																																																																																																																																											                    }
																																																																																																																																																																																																																																																																																																																																																																																																																																																																                    else if(temp1[0]==RE[j] && 1<strlen(temp1)){
																																																																																																																																																																																																																																																																																																																																																																																																																																																																							                        char temp2[128];
																																																																																																																																																																																																																																																																																																																																																																																																																																																																													                        strcpy(temp2,&temp1[1]);
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																			                        linkedlist_insert_last(l,temp2);
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									                    }
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																														                }
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																		            }
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																					        }
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																							        linkedlist_remove_first(l,output);
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									        if(strcmp(output,empty)==0){
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																													            printf("true\n");
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																        }
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																		        else{
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																						            printf("false\n");
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																									        }
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																											    }
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																												    linkedlist_free(l);
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																													    return 0;
}
