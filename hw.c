#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//-----------------------------------------------------------------------------

char used_topics[10][11];
int used_tpcs=0;

struct puzzle_t{
	int parts;
	char topic[10];
	char title[20];
	struct puzzle_t* next;	
};

struct list_t{
	int size;
	struct puzzle_t* head;
};

//--------------------------------------------------------------------------------------

int if_in(char *str){
	for(int i=0;i<=used_tpcs;i++){

		if(strcmp(str,used_topics[i])==0){
			return 1;
		}
	}
	return 0;
}

//---------------------------------------------------------------------------------------

struct puzzle_t* puzzle_create(){
	char topics[10][11]={"animations", "animals", "cars", "cities", "games", "history", "landscapes", "movies", "space", "sports"};
	srand(time(0));
	struct puzzle_t* puzzle=(struct puzzle_t*) malloc(sizeof(struct puzzle_t*));
	
	do{
		strcpy(puzzle->topic,topics[rand()%10]);
	}while(if_in(puzzle->topic));
	
	strcpy(used_topics[used_tpcs],puzzle->topic);
	used_tpcs++;
	
	return puzzle;
}

void insert(struct list_t *list, struct puzzle_t *puzzle){

	if(list->head!=NULL){
    		puzzle->next = list->head;
    	}else{
    		puzzle->next=NULL;
    	}
    	list->head = puzzle; 
    	list->size++; 
}

void full_puzzle_params(struct puzzle_t *puzzle){
	printf("Topic: %s\n", puzzle->topic);
	printf("Parts: ");
	scanf("%d",&puzzle->parts);
	getchar(); //fixing the scanf's extra new line bug :))
	printf("Title: ");
	fgets(puzzle->title,20,stdin);
	printf("-------------------------------\n");
}

void show_puzzles(struct list_t *list){
	int count=1;
	struct puzzle_t* puzzle=list->head;
	for(int i=0;i<list->size;i++){
		printf("Puzzle %d:\n", count);
		printf("	Topic: %s\n",puzzle->topic);
		printf("	Parts: %d\n",puzzle->parts);
		printf("	Title: %s\n",puzzle->title);
		count++;
		puzzle=puzzle->next;
	}
}

//-------------------------------------------------------------------------------------

int main(){
	struct list_t list={0,NULL};
	struct puzzle_t t={14,"a","a",NULL};
	struct puzzle_t *temp=&t;	
	for(int i=0;i<4;i++){
		//temp=puzzle_create();
		
		full_puzzle_params(temp);
		insert(&list,temp);


	}
	show_puzzles(&list);
	
		
}

