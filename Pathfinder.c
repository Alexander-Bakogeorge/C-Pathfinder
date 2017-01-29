#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QueueImplementation.c"

//***************************************************************************//
//	PROGRAMMER: Alexander Bakogeorge				     //
//	COURSE: CPS305-012						     //
//	STUDENT NUMBER: 500689218					     //
//	FILES INCLUDED: Pathfinder.c, UserTypes.h, member.txt, cert.txt      //
//	DATE: Nov 21, 2016						     //
//									     //
//	This program take in an input matrix, and finds a path               //
//	from a start point to an end point.				     //
//									     //
//***************************************************************************//


//*****************************FUNCTION PROTOTYPES***************************//
int validmove(int x, int y, char moves[][21], char source[][21]);
void newnodes(Queue *Que, ItemType *temp, char moves[][21], int leftright, int updown, int xy);
void priority(int *leftright, int *updown, int *xy, int startx, int endx, int starty, int endy);
void found(ItemType *temp, char source[21][21], int yaxis, int xaxis, char moves[21][21]);
ItemType startingmove(int startx, int starty);

int main(int argc, char *argv[]){
	
	//*********************VARIABLE DECLARATION**************************//
	char source[21][21]; //input map
	char moves[21][21]; //list of moves made
	int startx, starty; //start point
	int endx, endy; //end point
	int xaxis,yaxis; //x and y size
	int updown, leftright, xy; //move priorities, explained more in function
	int foundbool = 0; //variable for do while loop, checks if end has been found
	
	//pointers for the priority function	
	int *xypoint = &xy;
	int *lrpoint = &leftright;
	int *udpoint = &updown;

	//start and end flag for checking if s and e are in the matrix
	int startflag = 0;
	int endflag = 0;
	
	//Queue
	Queue *Que =  malloc(sizeof(Queue));
	InitializeQueue(Que);
	
	//loop variables
	int i = 0;
	int j = 0;

	//*********************FILE INPUT************************************//
	
	//scans in the x and y axis
	scanf("%d", &xaxis);
	scanf("%d", &yaxis);

	//scans in the matrix
	for(i=1; i < yaxis+1; i++){
		scanf("%s", source[i-1]);
		strcpy(moves[i-1], source[i-1]);
	}

	//searches for the start and end position
	for(i=0; i < yaxis; i++){
		for(j=0; j < xaxis; j++){
			if(source[i][j] == 's'){
				startx = j;
				starty = i;
				startflag = 1;
			}
			if(source[i][j] == 'e'){
				endx = j;
				endy = i;
				endflag = 1;
			}
		}
}

	//if there is no start or end point, exit the program
	if(startflag == 0 || endflag == 0){
		printf("NO PATHS\n");
		return 0;
	}

	//************************MAIN FUNCTION******************************//

	//checks priority of the moves in order decide how to push moves onto the que
	priority(lrpoint, udpoint, xypoint, startx, endx, starty, endy);
	
	//creates the first node and adds it to the queue
	ItemType startmove = startingmove(startx, starty);
	Insert(startmove, Que);

	do{
		//makes an ItemType pointer to hold the item off the top of the Queue		
		ItemType *temp = malloc(sizeof(ItemType));

		//Removes an item from the Queue, if there are none left, there are no paths: exit the do while loop
		if(!Remove(Que, temp)){
			printf("NO PATHS\n");
			foundbool = 1;
		}

		//If its the end point, call the found function and exit the do while loop
		else if(source[temp->y][temp->x] == 'e'){
			found(temp, source, yaxis, xaxis, moves);
			foundbool = 1;
		}
		
		//Else, check if the item is a valid move, if so, add its children to the Queue		
		else if(validmove(temp->x, temp->y, moves, source)){
			newnodes(Que, temp, moves, leftright, updown, xy);
		}
	
	//loops untill the endpoint is found, or no paths are found
	}while(foundbool == 0);
	
	//ends the program
	return 0;
}

//********************************FUNCTIONS**********************************//

//Makes the starting point, with the x and y of the 's' character, and a pointer to null
ItemType startingmove(int startx, int starty){
	ItemType temp;

	temp.x = startx;
	temp.y = starty;
	temp.ptr = NULL;

	return temp;
}

//If the item is found, preform output
void found(ItemType *temp, char source[21][21], int yaxis, int xaxis, char moves[21][21]){
	int outx[400];//array of all the output x's
	int outy[400];//array of all the output y's

	//loop variables	
	int i; 
	int j = 0;

	printf("A Path:\n");

	//loop through and get all the x and y's for the output path	
	do{
		outx[j] = temp->x;
		outy[j] = temp->y;
		source[temp->y][temp->x] = '*';
		j++;
		temp = temp->ptr;
	}while(temp != NULL);

	//print out the x and y in reverse order, so that it prints from start to end
	for(j; j > 0; j--){
		printf("[%d,%d]", outy[j-1], outx[j-1]);
	}
	
	//print the matrix with the edited path
	printf("\n");
	for(i=1; i < yaxis+1; i++){
		printf("%s\n", source[i-1]);
	}	
}

//Sets the priority of moves, for example, if the endpoint is down and to the left of the start point, the brute force method
//would be to go down and left, before checking up and down. Therefore, push down and left onto queue first, as they are most 
//likely to be the correct endpoint. So, in this function it determines the order in which to push up down left and right moves
//onto the queue. This is used in the newnodes function, and is not needed for a correct run, just a optimization
//Added with the concent of Dr. Woit
void priority(int *leftright, int *updown, int *xy, int startx, int endx, int starty, int endy){

	//checks if the end point is to the left or right of the start
	if(startx > endx)
		*leftright = 1;
	else if(startx < endx)
		*leftright = -1;
	else 
		*leftright = 0;

	//checks if the end point is bellow or above the start
	if(starty > endy)
		*updown = 1;
	else if(starty < endy)
		*updown = -1;
	else 
		*updown = 0;

	//checks whether the end point is farther from the start point horizontally or vertically
	if(startx-endx > starty-endy)
		*xy = 1;
	else if(startx-endx < starty-endy)
		*xy = -1;
	else
		*xy = 0;	
}

//checks if a move is valid or not
int validmove(int x, int y, char moves[][21], char sources[][21]){
	int i;

	//checks if the position is a valid move on the source
	if(sources[y][x] != '.' && sources[y][x] != 's' && sources[y][x] != 'e')
		return 0;

	//checks if the move has been done or not
	if(moves[y][x] == '*')
		return 0;

	//else, valid move, send true
	return 1;
}

//this code formerly in main after valid move check
void newnodes(Queue *Que, ItemType *temp, char moves[][21], int leftright, int updown, int xy){

	//records the move
	moves[temp->y][temp->x] = '*';
	
	//creates an up, down, right and left node, would be shorter to make an array of nodes, but this is a bit easier 
	//to follow, so its staying a bit longer.
	ItemType *newnodeu = malloc(sizeof(ItemType));
	ItemType *newnoded = malloc(sizeof(ItemType));
	ItemType *newnoder = malloc(sizeof(ItemType));
	ItemType *newnodel = malloc(sizeof(ItemType));

	//points the new node to its parent
	newnodeu->ptr = temp;
	newnoded->ptr = temp;
	newnoder->ptr = temp;
	newnodel->ptr = temp;
	
	//nodes for left right up down
	newnoder->x = temp->x + 1;
	newnoder->y = temp->y;

	newnodel->x = temp->x - 1;
	newnodel->y = temp->y;

	newnodeu->x = temp->x;
	newnodeu->y = temp->y - 1;

	newnoded->x = temp->x;
	newnoded->y = temp->y + 1;

	//This part uses the priority to push onto the queue, not needed for the program to run, but does speed it up slightly in some cases
	//based on priority, chooses the best brute force way to add items to queue
	if(xy >= 0){
		if(updown >= 0){
			if(leftright >= 0){
				Insert(*newnodel, Que);
				Insert(*newnodeu, Que);
				Insert(*newnoded, Que);
				Insert(*newnoder, Que);
			}
			if(leftright < 0){
				Insert(*newnoder, Que);
				Insert(*newnodeu, Que);
				Insert(*newnoded, Que);
				Insert(*newnodel, Que);
			}
		}
		if(updown < 0){
			if(leftright >= 0){
				Insert(*newnodel, Que);
				Insert(*newnoded, Que);
				Insert(*newnodeu, Que);
				Insert(*newnoder, Que);
			}
			if(leftright < 0){
				Insert(*newnoder, Que);
				Insert(*newnoded, Que);
				Insert(*newnodeu, Que);
				Insert(*newnodel, Que);
			}
		}
	}
	if(xy < 0){
		if(updown >= 0){
			if(leftright >= 0){
				Insert(*newnodeu, Que);
				Insert(*newnodel, Que);
				Insert(*newnoder, Que);
				Insert(*newnoded, Que);
			}
			if(leftright < 0){
				Insert(*newnodeu, Que);
				Insert(*newnoder, Que);
				Insert(*newnodel, Que);
				Insert(*newnoded, Que);
			}
		}
		if(updown < 0){
			if(leftright >= 0){
				Insert(*newnoded, Que);
				Insert(*newnodel, Que);
				Insert(*newnoder, Que);
				Insert(*newnodeu, Que);
			}
			if(leftright < 0){
				Insert(*newnoded, Que);
				Insert(*newnoder, Que);
				Insert(*newnodel, Que);
				Insert(*newnodeu, Que);
			}
		}
	}
}	
