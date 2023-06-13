#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// Defines the amount of rows and columns in the game field
#define ROW 20
#define COL 40  

// Create necessary global variables
int i, j, area[ROW][COL], x, y, gy, head, tail, game, apple, a, b, var, dir;

void snakeStart(){
    // Clear the game area by setting all the elements of the area to 0
    for (i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            area[i][j] = 0;
        }
    }

    // Set the initial position of the snake to be in the center of the game area
    x = ROW / 2;
    y = COL / 2;

    // Set the position of the snake's head and tail
    head = 5;
    tail = 1;

    // Set the initial position of the snake's body
    gy = y;

    // Set the game status, 0 represents that the game is not over
    game = 0;

    apple = 0;

    dir = 'd';

    // Create the snake's body segments inside the game area
    for (i = 0; i < head; i++){
        gy++;
        area[x][gy - head] = i + 1;
    }
}

// Function that creates the game area to play in
void printGame(){
    
    // Creates the top border of the game area
    for (i = 0; i <= COL + 1; i++){
        // Prints the left corner piece
        if (i == 0){
            printf("%c", 201);
        }
        // Prints the right corner piece
        else if (i == COL + 1){
            printf("%c", 187);
        }
        // Prints the middle pieces
        else{
            printf("%c", 196);
        }
    }
    printf("\n");

    // Creates the left border and the game area
    for (i = 0; i < ROW; i++){
        printf("%c", 179);

        for (j = 0; j < COL; j++){
            // Print a space if the element in the game area is 0 (Empty Space)
            if (area[i][j] == 0){
                printf(" ");
            }
            // Print a segment of the snake's body if the element is greater than 0 and not the head
            else if (area[i][j] > 0 && area[i][j] != head){
                printf("%c", 176);
            }
            // Print the head of the snake if the position is at the head
            else if (area[i][j] == head){
                printf("%c", 178);
            }
            else if (area[i][j] == -1){
                printf("%c", 2);
            }
            else {
                printf(" ");
            }

            // Creates the right border of the game area
            if (j == COL - 1) {
                printf("%c\n", 179);
            }
        }
    }

    // Creates bottom border for the game area
    for (i = 0; i <= COL + 1; i++){
        // Prints the left corner piece
        if (i == 0){
            printf("%c", 200);
        }
        // Prints the right corner piece
        else if (i == COL + 1){
            printf("%c", 188);
        }
        // Prints the pieces in the middle
        else{
            printf("%c", 196);
        }
    }
    printf("\n");
}

void resetScreen(){
    // Handle to the console output
    HANDLE hOut;

    // Structure to store the position of the cursor
    COORD position;

    // Get the handle to the standard output
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the X-coordinate of the cursor position to 0 (Leftmost Position)
    position.X = 0;

    // Set the Y-coordinate of the cursor position to 0 (Topmost Position)
    position.Y = 0;

    // Set the cursor position to the specified coordinates (0,0)
    SetConsoleCursorPosition(hOut, position); 
}

void randomPosition(){
    srand(time(0));
    a = 1 + rand() % 18;
    b = 1 + rand() % 38;

    if (apple == 0 && area[a][b] == 0){
        area[a][b] = -1;
        apple = 1;
    }
}

int getch_noblock(){

    if(_kbhit()){
        return _getch();
    }
    else{
        return -1;
    }
}

void snakeMovement(){

    var = getch_noblock();
    var = tolower(var);

    if (((var == 'd' || var == 'a') || (var == 's' || var == 'w')) && (abs(dir - var) > 5)){
        dir = var;
    }

    if (dir == 'd'){
        y++;
        if (y == COL - 1){
            y = 0;
        }
        head++;
        area[x][y] = head;
    }

    else if (dir == 'a'){
        y--;
        if (y == 0){
            y = COL -1;
        }
        head++;
        area[x][y] = head;
    }

    else if (dir == 'w'){
        x--;
        if (x == -1){
            x = ROW - 1;
        }
        head++;
        area[x][y] = head;
    }

    else if (dir == 's'){
        x++;
        if (x == ROW - 1){
            x = 0;
        }
        head++;
        area[x][y] = head;
    }

}

void Tail(){
    for(i = 0; i < ROW; i++){
        for(j = 0; j < COL; j++){
            if(area[i][j] == tail){
                area[i][j] = 0;
            }
        }
    }

    tail++;
    
}

int main(){
    // Initialize the game
    snakeStart();

    // Loop until the game is over (game != 0)
    // This loop creates a fluid system in which each frame can be seen 
    while (game == 0){
        // Print the game area
        printGame(); 

        // Reset the screen 
        resetScreen();

        randomPosition();

        snakeMovement();

        Tail();

        Sleep(99);
    }
    
    return 0;    
}