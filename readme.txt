------ C Breakout ------
--- by Sean Beckerle ---

Project Explaination:
This program is a slightly more simplistic recreation of the game breakout/brick breaker using the gfx3 library and the C language. The users goal is
to use a paddle and ball in order to break all the bricks in a grid. Breaking all the bricks causes the grid to be reset and a new level to be started.
The user launches the ball at a random velocity from the center of the paddle and doesn't control the ball once it has been fired. The user instead 
controls the paddle, moving it horizontally in order to get the ball to not hit the bottom of the screen. If the ball hits the bottom, that ball is lost
and the user has to launch a new ball to continue the process. The user starts with 3 balls and everytime a level is completed, another ball is gained.
The game is lost when the user loses all their balls. Whenever a brick is broken, the user gains 20 points (my personal best is 1380).

Controls:
- Left and Right Arrow Keys - Moving the paddle left or right
- Space Bar - Launching the ball to begin play
- 'Q' key - quitting the program

Q/A:
-Why didn't I use gfx_clear() to reset the board every iteration?
	The use of gfx_clear caused a shuttering effect to occur for the bricks because of how frequently and intensive it was to draw them. Still wanting
	 the ball to move smoothly, I opted for a strategy where I removed drawings by re-outlining them in black, the background color.
-What does the Brick struct do? 
	The struct contains 3 integers for the RGB value of the brick, two floats that represents the top left corner of the brick's x and y values, and a
	boolean that represents whether the box is broken or not, which determines if it has an active "hit-box".
-How is the velocity of the ball determined?
	The velocity of the ball once launched is determined using the rand() function and the current level of the game. The velocity is split into x and y
	components, that are floats that have a value between level and level+1. This ensures that the game becomes more difficult if the level progresses. 
	The velocity is also re-randomized everytime it hits the paddle.
-How does the bouncing if the ball work?
	As stated in the velocity question, when hitting the paddle the ball generated a random velocity upwards and then either to the left or right 
	depending on which direction the ball is already coming from.	

	Hitting a wall or side of a brick, causes the x-component or y-component of the velocity to reverse depending on how the ball hits. Hitting the
	corner of brick causes from both the x and y components to reverse, leading to some whacky combinations.
-Why breakout?
	I thought it would be fun!

