//Sean Beckerle
//project.c
//
//This project contains the main for a program that runs a version of the game brick breaker
#include "func.h"

int main(){
	bool cont = true, reset = false, ball = false;
	int width = 720, height = 720, event = 0, level = 1, score = 0, hit = 0;
	int brickWidth = 80, brickHeight = 40, row = 5, col = 7; //Brick Variables
	int barWidth = 120, barHeight = 10, barX = width/2-barWidth/2 , barY = height-60-barHeight;//Bar Variables
	int ballX = 800, ballY = 800, ballRad = 11, balls = 3; //Ball Variables
	float vX = 0, vY = 0;
	int waitTime = 10000;
	char c = ' ';
	Brick brick[row][col]; 

	//Sets up the initial screen
	gfx_open(width,height,"Breakout");
	resetBoard(brick,row,col,brickWidth,brickHeight);	
	displayBoard(brick,row,col,brickWidth,brickHeight);
	displayText(20,height-50,level,balls,score,level,balls,score);

	//Used for randomization of ball velocity
	srand(time(0));

	//Loop that keeps the game running
	while(ball ||  balls > 0 || level > 10){
		//Called if level is beaten
		if(reset){
			reset = false;
			level++;
			balls++;
			resetBoard(brick,row,col,brickWidth,brickHeight);	
			displayBoard(brick,row,col,brickWidth,brickHeight);
			displayText(20,height-50,level-1,balls-2,score,level,balls,score);
		}
	
		//Waits for button clicks	
		event = gfx_event_waiting();
		
		//Goes if a button is pressed
		if(event != 0){
			c = gfx_wait();
			if(event == 1){
				if(c == 'Q')//Moves the bar right
					if(barX != 0){	
						gfx_color(0,0,0);
						gfx_fill_rectangle(barX,barY,barWidth,barHeight);
						barX-=20;
					}
				if(c == 'S')//Moves the bar left
					if(barX+barWidth != width){
						gfx_color(0,0,0);
						gfx_fill_rectangle(barX,barY,barWidth,barHeight);
						barX+=20;
					}
				if(c == 32)//Creates the ball if non-existent
					if(ball == false){
						ball = true;
						ballX = barX + barWidth/2;
						ballY = barY - ballRad;	
						vX = level + (float)(rand()%100)/50;
						vY = level + (float)(rand()%100)/50;
						balls--;
						displayText(20,height-50,level,balls+1,score,level,balls,score);
					}
				if(c == 'q'){//quits the program
					balls = -1;
					ball = false;
					cont = false;
				}
			}
		}
	
		//Displays the bar
		gfx_color(255,255,255);
		gfx_fill_rectangle(barX,barY,barWidth,barHeight);

		//Erases old ball and adds new ball, also sees if velocity needs to be changed.
		if(ball){	
			gfx_color(0,0,0);
			gfx_circle(ballX,ballY,ballRad);
			ballX -= vX;
			ballY -= vY;
			gfx_color(255,255,255);
			gfx_circle(ballX,ballY,ballRad);

			//Checks to see if the ball hits a wall
			if(ballX-ballRad <= 0){ //left wall
				vX = -vX;
				gfx_color(0,0,0);
				gfx_circle(ballX,ballY,ballRad);
				ballX = ballRad+1;
			}
			else if(ballX+ballRad >= width){ //right walll
				vX = -vX;
				gfx_color(0,0,0);
				gfx_circle(ballX,ballY,ballRad);
				ballX = width-ballRad-1;
			}

			//checks to see if the ball hit the top, bottom or a paddle
			if(ballY-ballRad <= 0){ //top wall
				vY = -vY;
				gfx_color(0,0,0);
				gfx_circle(ballX,ballY,ballRad);
				ballY = ballRad+1;
			}
			else if(ballY+ballRad >= barY && ballY+ballRad <= barY+barHeight && ballX >= barX && ballX <= barX+barWidth){ //bar
				vY = level + (float)(rand()%100)/50;
				if(vX > 0)
					vX = level + (float)(rand()%100)/50;
				else
					vX = -level - (float)(rand()%100)/50;	
			}
			else if(ballY+ballRad >= height){ //bottom wall
				ball = false;
				vX = 0;
				vY = 0;
				gfx_color(0,0,0);
				gfx_circle(ballX,ballY,ballRad);	
				ballX = 800; //off-screen
				ballY = 800; //off-screen
				displayText(20,height-50,level,balls+1,score,level,balls,score);		
			}

			//Checks if the ball hit any bricks
			if(ballY-ballRad <= (20+brickWidth)*row){
				hit = hitBoard(brick,row,col,brickWidth,brickHeight,ballX,ballY,ballRad);
			
				//Hit represents whether the ball hit the top, bottom, sides, or corner of the brick
				if(hit == 1){ //top and bottom
					score += 20;
					displayText(20,height-50,level,balls,score-20,level,balls,score);
					vY = -vY;
				}			
				else if(hit == 2){ //sides
					score += 20;
					displayText(20,height-50,level,balls,score-20,level,balls,score);
					vX = -vX;
				}
				else if(hit == 3){ //corener
					score += 20;
					displayText(20,height-50,level,balls,score-20,level,balls,score);
					vX = -vX;
					vY = -vY;
				}

				hit = 0;
			}
		
		}
	
		//Checks if all the bricks are broken and if so, sets the reset level boolean to true and removes the ball
		if(levelComplete(brick,row,col)){
			reset = true;
			balls++;
			ball = false;
			vX = 0;
			vY = 0;
			gfx_color(0,0,0);
			gfx_circle(ballX,ballY,ballRad);	
			ballX = 800; //off-screen
			ballY = 800; //off-screen
		}

		gfx_flush();
		usleep(waitTime);
	}

	//Displays message based on if the user beat 10 levels
	if(level == 11)
		gfx_text(width/2 - 30,height/2,"YOU WIN!!");
	else
		gfx_text(width/2 - 30,height/2,"GAME OVER");
	gfx_text(width/2 - 65,height/2 + 20,"Press 'Q' Key to Exit");

	//Waits for the user to exit the program
	while(cont){
		event = gfx_event_waiting();
		if(event != 0){
			c = gfx_wait();
			if(c == 'q')
				cont = false;
		}
	}	
	
	return 0;
}
