//
// file: life.c
// description: Simulates Conway's Game of Life
//
// @author Ryan Nowak rcn8263

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20 ///< width and height of the grid

/// Prints a welcome message to the user
void header(void) {
    printf("\n\t..Welcome to the Game of life..\n");
}

/// Returns the number of neighbor asterisks around a given coordinate
///
/// @param life array containing the grid
/// @param row current row of the grid to check
/// @param col current col of the grid to check
/// @return int containing the number of neighbors around the given point
int getNumOfNeighbors(char life[][SIZE], int row, int col) {
    int neighbors = 0;
    
    if(life[(row - 1) % SIZE][(col - 1) % SIZE] == '*')
        neighbors++;
    if(life[(row - 1) % SIZE][col] == '*')
        neighbors++;
    if(life[(row - 1) % SIZE][(col + 1) % SIZE] == '*')
        neighbors++;
    if(life[row][(col - 1) % SIZE] == '*')
        neighbors++;
    if(life[row][(col + 1) % SIZE] == '*')
        neighbors++;
    if(life[(row + 1) % SIZE][(col - 1) % SIZE] == '*')
        neighbors++;
    if(life[(row + 1) % SIZE][col] == '*')
        neighbors++;
    if(life[(row + 1) % SIZE][(col + 1) % SIZE] == '*')
        neighbors++;
      
    return neighbors;
}

/// Determines if a cell should be populated by an organism or if an organism
/// already populating a cell should die. Follows all of the rules of Conway's
/// game of life.
///
/// @param life grid containing all the organisms
/// @param life_cpy copy of the life grid so that everything can be updated
///        simultaneously
/// @param x index of last column element of life array
/// @param y index of last row element of life array
void Rules(char life[][SIZE], char life_cpy[][SIZE], int x, int y) {
    int row, col;
    int neighbors;
    for(row = 0; row<=y; row++) {
        for(col = 0; col<=x; col++) {
            neighbors = getNumOfNeighbors(life_cpy, row, col);
            
            if(life_cpy[row][col]== ' ') {
                if(neighbors == 3) {
                    life[row][col] = '*';
                }
            }
            
            else if(life_cpy[row][col]== '*') {
                if(neighbors == 2 || neighbors == 3) {
                    life[row][col] = '*';
                }
                else if(neighbors < 2) {
                    life[row][col] = ' ';
                }
                else if(neighbors > 3) {
                    life[row][col] = ' ';
                }
            }
        }
    }
    return;
}

/// Asks the user for the number of organisms to populate the grid with then
/// randomly places them on the grid. Then, simulates Conway's game of life
/// while printing each generation in the output.
int main(void) {
    char life[SIZE][SIZE];
    char life_cpy[SIZE][SIZE];
    int orgs;
    int i, row, col;
    int count = 0;
    int x = SIZE-1;
    int y = SIZE-1;
    
    header();
    
    printf("\nPlease enter the initial number of organisms: ");
    scanf("%i", &orgs);
    
    srand( 31 );
    
    //Populates the grid with organisms
    for(i = 0; i<orgs; i++) {
        while ( 1 ) {
          row = rand();
          row %= SIZE;
          col = rand();
          col %= SIZE;
          if (life[row][col] != '*') {
              life[row][col] = '*';
              break;
          }
        }
    }
    
    //Fill in any spaces on the board that don't have organisms
    for(row = 0; row<SIZE; row++)
    {
        for(col = 0; col<SIZE; col++)
        {
            if(life[row][col] != '*') {
                life[row][col] = ' ';
            }
        }
    }
    
    //Iterate through the generations
    while ( count < 100 ) {
        //Print life board
        for(row = 0; row<SIZE; row++) {
            for(col = 0; col<SIZE; col++) {
                printf("%c", life[row][col]);
            }
            puts(" ");
        }
        printf("\ngeneration: %d\n", count);
        
        //Make a copy of current board
        for(row = 0; row < SIZE; row++) {
            for(col = 0; col < SIZE; col++) {
                life_cpy[row][col] = life[row][col];
            }
        }
        
        //Create the next generation based on current board
        Rules(life, life_cpy, x, y);
        
        count++;
    }
    
    return 0;
}