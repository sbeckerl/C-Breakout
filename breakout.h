//Sean Beckerle
//func.h 
//
//The header functin for the brick breaker program
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "gfx3.h"

typedef struct{
	int red;
	int green;
	int blue;
	bool alive;
	float x;
	float y;
} Brick;

void resetBoard(Brick [][7],int,int,int,int);
void displayBoard(Brick [][7],int,int,int,int);
void displayText(int,int,int,int,int,int,int,int);
int hitBoard(Brick [][7],int,int,int,int,float,float,int);
bool levelComplete(Brick [][7],int,int);
