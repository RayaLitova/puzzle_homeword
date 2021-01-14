#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//-----------------------------------------------------------------------------

char used_topics[10][11]; //already used topics for puzzles
int used_tpcs=0; //num of used topics

struct puzzle_t{ //puzzle struct
	int parts;
	char topic[10];
	char title[20];
	struct puzzle_t* next;	
};

struct list_t{ //linked list (puzzles)
	int size;
	struct puzzle_t* head;
};

//--------------------------------------------------------------------------------------

int if_in(char *str){ //checks if topic is already used
	for(int i=0;i<=used_tpcs;i++){

		if(strcmp(str,used_topics[i])==0){
			return 1;
		}
	}
	return 0;
}

//---------------------------------------------------------------------------------------

struct puzzle_t* puzzle_create(){ //creates a puzzle with only a random topic and nth else
	char topics[10][11]={"animations", "animals", "cars", "cities", "games", "history", "landscapes", "movies", "space", "sports"};
	srand(time(0));//for random number
	struct puzzle_t* puzzle=(struct puzzle_t*) malloc(sizeof(struct puzzle_t*));//frees up space for the new struct (don't ask questions here that's how they want us to do it)
	
	do{
		strcpy(puzzle->topic,topics[rand()%10]);
	}while(if_in(puzzle->topic));
	
	strcpy(used_topics[used_tpcs],puzzle->topic);//inserts the topic ot the new puzzle to already used
	used_tpcs++;//increases their num
	
	return puzzle;
}

void insert(struct list_t *list, struct puzzle_t *puzzle){//inserts a puzzle into the list

	if(list->head!=NULL){
    		puzzle->next = list->head;
    	}else{
    		puzzle->next=NULL;
    	}
    	list->head = puzzle; 
    	list->size++; 
}

void full_puzzle_params(struct puzzle_t *puzzle){//asks the user to full the parameters
	printf("Topic: %s\n", puzzle->topic);
	printf("Parts: ");
	scanf("%d",&puzzle->parts);
	getchar(); //fixing the scanf's extra new line bug :))
	printf("Title: ");
	fgets(puzzle->title,20,stdin);
	printf("-------------------------------\n");
}

void show_puzzles(struct list_t *list){//prints the whole list (here i get the segm. fault)
	int count=1;//only for displaying
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
	for(int i=0;i<4;i++){
		insert(&list,puzzle_create());
		full_puzzle_params(list.head);
	}
	show_puzzles(&list);
	
		
}

