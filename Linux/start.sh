#!/bin/bash

#Startup script, so that user doesn't have to start the game from terminal.

#First, check if the compiled binary is available
if [ -e "CSnake" ] 
then
#Run the game
	./CSnake
else
	#Compile and then run the game
	gcc CSnake.c -o CSnake
	./CSnake
fi
