/*
 * Console "Snake" Ver0.4 Windows version
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

#include <stdio.h>
#include <unistd.h> /*getch, sleep and usleep*/
#include <stdlib.h> /*rand*/
#include <time.h>   /*srand*/
#include <windows.h> /*gotoxy*/

#define SNAKE_HEAD	'@'
#define SNAKE_BODY 	'0'
#define FOOD '*'
#define SNAKE_START_POSITION_X	10
#define SNAKE_START_POSITION_Y	5
#define SLEEP_TIME 500000

/*gotoxy function for linux*/
void gotoxy(int x,int y);
int moveSnakeRight();
int moveSnakeDown();
int moveSnakeUp();
int moveSnakeLeft();
int generateFood();
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

	/*********Start Here*******/


	while(1) {
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
	/*Tweak the values after '+' to get FOOD within the terminal visible area*/
	foodPositionX = rand() % 10 + 40;
	foodPositionY = rand() % 10 + 15;
	gotoxy(foodPositionX, foodPositionY);
	putchar(FOOD);
	return 0;
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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

	if(direction == 'd')
		moveSnakeRight();
	else if(direction == 'a')
		moveSnakeLeft();
	else if(direction == 's')
		moveSnakeDown();
	else if(direction == 'w')
		moveSnakeUp();

	/*Suicide case*/
	for(i=0; i<=bodyLength; i++) {
			if(headPositionX==bodyPositionX[i] && headPositionY==bodyPositionY[i]) {
				/*code to end the game*/
				printf("\t\t\tGame Over\n\n\n\n\n\n");
				exit(1);
			}
		}


	/*Speed of snake ie. sleepe time in ms time unit.*/
	usleep(SLEEP_TIME);
	fflush(stdout);

	return 0;
}
