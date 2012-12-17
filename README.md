#Start the game (on Linux)
   Right click on the file "start.sh" --> Properties --> Permissions --> click on "Allow executing file as program" --> close

   Now, double click on "start.sh" --> "Run in terminal".


   On Windows, double click on snake.exe to play.

#COMPILATION
  Run the following command for compilation -- 
		
		gcc -o snake snake\ 0.6.c

#KNOWN ISSUES
   
   As the main functionality has been added already (which was the intent),
   I didn't care to develop it further.
   1. Game crashes when snake reaches the edge, no boundary limit has been defined for the snake to crawl.
   2. No score/level system.
   3. Food generates around a specific region only.
