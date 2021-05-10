//Sean Beckerle
//func.c
//
//The functions from the program are written here
#include "func.h"

//Resets the board to its original state
void resetBoard(Brick brick[][7], int row, int col, int width, int height){
	int i,j;
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			brick[i][j].alive = true;
			brick[i][j].x = 20 + (width+20) * j; //Represents the top left corner x and y values
			brick[i][j].y = 20 + (height+20) * i;
				
			//Determines color of brick
			if(i == 0){
				brick[i][j].red = 255;
				brick[i][j].green = 0;
				brick[i][j].blue = 0;
			}
			else if(i == 1){
				brick[i][j].red = 255;
				brick[i][j].green = 140;
				brick[i][j].blue = 0;
			}
			else if(i == 2){
				brick[i][j].red = 255;
				brick[i][j].green = 255;
				brick[i][j].blue = 0;
			}
			else if(i == 3){
				brick[i][j].red = 0;
				brick[i][j].green = 255;
				brick[i][j].blue = 0;
			}
			else{
				brick[i][j].red = 0;
				brick[i][j].green = 0;
				brick[i][j].blue = 255;
			}
		}
	}
}

//Displays the board as it currently is
void displayBoard(Brick brick[][7], int row, int col, int width, int height){
	int i, j;
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			gfx_color(brick[i][j].red,brick[i][j].green,brick[i][j].blue);
			gfx_rectangle(brick[i][j].x,brick[i][j].y,width,height);
		}
	}
}

//Replaces the text in the bottom left corner
void displayText(int x, int y, int prevLevel, int prevBall, int prevScore, int level, int ball, int score){
	char lString[15];
	char newLString[15];
	char bString[15];
	char newBString[15];
	char sString[15];
	char newSString[15];

	//Adds level, ball, and score values to strings
	sprintf(lString, "Level: %d", prevLevel);
	sprintf(bString, "Balls: %d", prevBall);
	sprintf(sString, "Score: %d", prevScore);
	sprintf(newLString, "Level: %d", level);
	sprintf(newBString, "Balls: %d", ball);
	sprintf(newSString, "Score: %d", score);

	//Used to erase old text
	gfx_color(0,0,0);
	gfx_text(x,y,lString);
	gfx_text(x,y+20,bString);
	gfx_text(x,y+40,sString);
	
	//Used for writing new text
	gfx_color(255,255,255);
	gfx_text(x,y,newLString);
	gfx_text(x,y+20,newBString);
	gfx_text(x,y+40,newSString);
}

//Returns an int based on whether or not the ball hits a brick and how it does so
int hitBoard(Brick brick[][7], int row, int col, int width, int height, float x, float y, int rad){
	int i, j, val = 0;

	//For loop that goes through each brick
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			if(brick[i][j].alive){ //Checks if the brick is still there
				if(brick[i][j].x < x && brick[i][j].x+width > x){ //Checks the top or bottom
					if(y+rad > brick[i][j].y && y-rad < brick[i][j].y + height){
						gfx_color(0,0,0);
						gfx_rectangle(brick[i][j].x,brick[i][j].y,width,height);
						val = 1;
						brick[i][j].alive = false;
					}
				}	
				else if(brick[i][j].y < y && brick[i][j].y+height > y){ //Checks the sides
					if(x+rad > brick[i][j].x && x-rad < brick[i][j].x + width){
						gfx_color(0,0,0);
						gfx_rectangle(brick[i][j].x,brick[i][j].y,width,height);
						val = 2;
						brick[i][j].alive = false;
					}
				}
				else if(sqrt(pow(brick[i][j].x-x,2)+pow(brick[i][j].y-y,2)) <= rad || sqrt(pow(brick[i][j].x+width-x,2)+pow(brick[i][j].y-y,2)) <= rad || sqrt(pow(brick[i][j].x-x,2)+pow(brick[i][j].y+height-y,2)) <= rad || sqrt(pow(brick[i][j].x+width-x,2)+pow(brick[i][j].y+height-y,2)) <= rad){
					gfx_color(0,0,0);
					gfx_rectangle(brick[i][j].x,brick[i][j].y,width,height);
					val = 3;
					brick[i][j].alive = false;
				}
			}
		}
	}

	return val;
}

//Sees if all the bricks are "dead" and if so, returns true
bool levelComplete(Brick brick [][7], int row, int col){
	int i, j;
		
	for(i = 0; i < row; i++){
		for(j = 0; j < col; j++){
			if(brick[i][j].alive)
				return false;
		}
	}
	
	return true;
}	
