/*
 * Console "Snake" Ver0.4
 * 
 * Copyright 2011 Gaurav Butola <GauravButola@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
 /*					KNOWN ISSUES
  * 
  * As the main functionality has been added already (which was the intent),
  * I didn't care to develop it further.
  * (1) Game crashes when snake reaches the edge, no boundary limit has been defined for the snake to crawl.
  * (2) No score/level system.
  * (3) Food generates around a specific region only.
  */

#include <stdio.h>
#include <unistd.h> /*getch, sleep and usleep*/
#include <stdlib.h> /*rand*/
#include <time.h>   /*srand*/
#include <termios.h> /*getch*/
#include "kbhit.h" /*From http://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html#post449307*/

#define SNAKE_HEAD	'@'
#define SNAKE_BODY 	'0'
#define SNAKE_START_POSITION_X	10
#define SNAKE_START_POSITION_Y	5
#define FOOD '*'
#define SLEEP_TIME 200000

/*gotoxy function for linux*/
void gotoxy(int x,int y);
int moveSnakeRight();
int moveSnakeDown();
int moveSnakeUp();
int moveSnakeLeft();
int generateFood();
int getch();
int moveSnake();

/*Global varialbles*/
char snakeBody = SNAKE_BODY;
char snakeHead = SNAKE_HEAD;
int bodyLength = 3;
int headPositionX = SNAKE_START_POSITION_X;
int headPositionY = SNAKE_START_POSITION_Y;
char bodyPositionX[100];
char bodyPositionY[100]; 
int foodPositionX;
int foodPositionY;
int direction = 'd';
int foodEaten = 0;

int main()
{
	printf("\t\t\t\t****Controls****\n\n");
	printf("\tW = Up | A = Left | S = Down | D = Right\n\n");
	printf("\t\t\t\t****KNOWN ISSUES****\n\n");
	printf("\t As the main functionality has been added already (which was the intent)\n");
	printf("\t I didn\'t care to develop it further.\n\n");
	printf("\t (1) Game crashes when snake reaches the edge, no boundary \n\t limit has been defined for the snake to crawl.\n");
	printf("\n\t (2) No score/level system.\n");
	printf("\n\t (3) Food generates around a specific region only, Tweak the\n \t rand() values to get more random locations.\n");
	printf("\n\t\t\t\t\t\tGaurav Butola");
	printf("\n\t\t\t\t\t\tGauravButola@gmail.com");
	printf("\n\n\t\t\t\tPress any key to play");

	
	getch();
	printf("%c[2J",0x1B); /*Erase the screen*/
	
	/*Show the snake when game starts*/
	gotoxy(headPositionX, headPositionY);
	putchar(snakeHead);
	
	int i;
	for(i=1; i<=bodyLength; i++) {
		bodyPositionX[i] =  headPositionX-i;
		bodyPositionY[i] = headPositionY; /*Not moving in Y axis*/
		gotoxy(bodyPositionX[i], bodyPositionY[i]);
		putchar(snakeBody);
	}	
	
	/*********Start game loop here*******/
	
	while(1) {
		changemode(1);
	    if(!foodEaten) {
            generateFood();
            foodEaten = 1;
	    }
		if(kbhit()) {
			direction = getch();
			moveSnake();
		}
		else
			moveSnake();
	}
	return 0;
}



int moveSnakeRight() {
	++headPositionX;
	gotoxy(headPositionX,headPositionY);
	putchar(snakeHead);
	return 0;
}

int moveSnakeDown() {
	++headPositionY;
	gotoxy(headPositionX,headPositionY);
	putchar(snakeHead);
	return 0;
}

int moveSnakeUp() {
	--headPositionY;
	gotoxy(headPositionX,headPositionY);
	putchar(snakeHead);
	return 0;
}

int moveSnakeLeft() {
	--headPositionX;
	gotoxy(headPositionX,headPositionY);
	putchar(snakeHead);
	return 0;
}

int generateFood() {
	srand(time(NULL));
	foodPositionX = rand() % 10 + 50;
	foodPositionY = rand() % 10 + 15;
	gotoxy(foodPositionX, foodPositionY);
	putchar(FOOD);
	return 0;
}

void gotoxy(int x,int y)
{
	printf("%c[%d;%df",0x1B,y,x);
}


int getch( ) {
	
	struct termios oldt,
				 newt;
	int            ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

int moveSnake() {
	
	if(headPositionX==foodPositionX && headPositionY==foodPositionY)
	{
		bodyLength++;
		foodEaten = 0;
	}
	else {
		/*Removing the tail ie. the last block*/
		gotoxy(bodyPositionX[bodyLength], bodyPositionY[bodyLength]); 
		putchar(' ');
	}	
	
	/*Moving the head forward and then other blocks follow*/	
	int i;
	for(i=bodyLength;i>0;i--) {
		if(i == 1) {
			bodyPositionX[i] = headPositionX;
			bodyPositionY[i] = headPositionY;
			gotoxy(bodyPositionX[i], bodyPositionY[i]);
			putchar(snakeBody);					
		}
		else {
			bodyPositionX[i] = bodyPositionX[i-1];
			bodyPositionY[i] = bodyPositionY[i-1];
			gotoxy(bodyPositionX[i], bodyPositionY[i]);
			putchar(snakeBody);
		}
	}
	
	
	if(direction == 'd' || direction == 'D') 
		moveSnakeRight();
	else if(direction == 'a' || direction == 'A') 
		moveSnakeLeft();
	else if(direction == 's' || direction == 'S') 
		moveSnakeDown();
	else if(direction == 'w' || direction == 'W') 
		moveSnakeUp();
		
	
	/*Suicide case*/
	for(i=0; i<=bodyLength; i++) {
			if(headPositionX==bodyPositionX[i] && headPositionY==bodyPositionY[i]) {
				/*code to end the game*/
				printf("\t\t\tGame Over\n\n\n\n\n\n");
				getch();
				exit(1);
			}
		}

		
	/*Speed of snake ie. sleepe time in ms time unit.*/
	usleep(SLEEP_TIME);
	fflush(stdout);	
	return 0;
}
