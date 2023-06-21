#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <conio.h>

typedef struct CORD{
    int y;
    int x;
}CORD;

void displayDataGrid(char dataGrid[10][10], CORD userInput){

    int y, x;

    dataGrid[userInput.y][userInput.x] = 'H';

    //If we want to get value at the userInput, just do (value = dataGrid[y][x])
    //Will later use to compare and do inventory/data collection

    printf("\n-----------------------------------------\n");
    for(y = 0; y < 10; y++)
    {
        for(x = 0; x < 10; x++)
        {
            printf("| %c ",dataGrid[y][x]);
        }
        printf("|");
        printf("\n-----------------------------------------\n");
    }
}

void getUserInput(CORD *userInput){

    char letterValue, numberValue, response[3];     //Variables needed only in this function. Gets organized into CORD STRUCT
    int xValue, yValue;

while(1) //Turns entire function into infinite loop. Only breaks out if all values are good/valid
{
    printf("\nEnter position on board: \n");        //Makes char array response and stores response
    scanf(" %s", &response);

    if (response[0] == 'Q')     //Ends program if user submits "QQ", will have save data function later
    {                           //Whole function will need to pass dataArray and displayArray eventually to save
        if (response[1] == 'Q')
        {
            printf("Saving data, ending program");
            exit(1);
        }
    }
    
    letterValue = response[0];  //puts array response[0] into char variable "letterValue"
    numberValue = response[1] + response[2];   //puts array response[1+2} into char variable "numberValue"

    xValue = numberValue - '0'; //puts/transforms char variable numberValue to integer variable "xValue"

    //CHECKS SIZE OF xValue, if it doesn't pass it loops function over again until good value
    if (0 > xValue )
    {
        printf("\nNumber value out of range, please try again\n", xValue);
        continue;
    }
    else if (xValue > 9)
    {
        printf("\nNumber value out of range, please try again\n", xValue);
        continue;
    }

    //CHAR VARIABLE "letterValue" WHICH IS STILL A LETTER DECIDES WHAT "yValue" SHOULD BE 
    //(if A, make value 0, if C make value 2 etc) ALSO CHECKS TO MAKE SURE USER SUBMITTED A VALID LETTER

    if (letterValue == 'A')
    {
        yValue = 0;
        break;
    } 
    else if (letterValue == 'B')
    {
        yValue = 1;
        break;
    } 
    else if (letterValue == 'C')
    {
        yValue = 2;
        break;
    } 
    else if (letterValue == 'D')
    {
        yValue = 3;
        break;
    } 
    else if (letterValue == 'E')
    {
        yValue = 4;
        break;
    } 
    else if (letterValue == 'F')
    {
        yValue = 5;
        break;
    } 
    else if (letterValue == 'G')
    {
        yValue = 6;
        break;
    } 
    else if (letterValue == 'H')
    {
        yValue = 7;
        break;
    } 
    else if (letterValue == 'I')
    {
        yValue = 8;
        break;
    } 
    else if (letterValue == 'J')
    {
        yValue = 9;
        break;
    }
    else {
        printf("\nLetter value out of range, please try again (CAPS SENSITIVE)\n");
    }
}
    (*userInput).y = yValue;
    (*userInput).x = xValue;
}

int printRandoms(int lower, int upper, int count) //Used in generateDataGrid to get random numbers not only for direction but cordinate values
{
	int i;
	for (i = 0; i < count; i++) {
		int num = (rand() % (upper - lower + 1)) + lower;
        return(num);
	}
}

void placeShips(int shipSize, CORD shipName[], char dataGrid[10][10], char shipLetter)
{
    while(1)
    {   
    // Gets 2 unique random numbers, logic for 1 random number is much easier.
    // This code is needed cause without it the random numbers generated would always be the same for X & Y
    // All it does is get 2 random ints between 0-9 and puts them into CORD randomCord.y/x
    int i, rnum, xyArray[2];
    srand(time(0));
    for(i=0; i<2; i++)
    {
        rnum = rand()%(9+1-0)+0;
        xyArray[i] = rnum;
    }

    CORD randomCord;
    randomCord.y = xyArray[0];
    randomCord.x = xyArray[1];

    printf("Random numberY is %d\n", randomCord.y);
    printf("Random numberX is %d\n", randomCord.x);
    // dataGrid[randomCord.y][randomCord.x] = 'Z'; //<-- Example code to "place" ship at randomCord spot

    // Gets random number for direction ship will be built in:
    // 1 = up(yValue - 1)
    // 2 = right(xValue + 1)
    // 3 = down(yValue + 1)
    // 4 = left(xValue -1)
	srand(time(0)); 
	int randomNumberDirection  = printRandoms(1, 4, 1);  // First 2 values are limit (1-4) 3rd value is what % (in this case every "1's" number)
    printf("Random number is %d\n", randomNumberDirection);

    if (dataGrid[randomCord.y][randomCord.x] != 'M')
    {
        printf("\nThat cord is not M \n");
        continue;
    }
    
    if (randomNumberDirection == 1)
    {
        printf("\n going up\n");
        for(i=0; i<shipSize; i++)
        {
            if ((randomCord.y - i) == -1)
            {
                printf("\nThat new spot is out of bounds\n");
                break;
            }

            else if ( (dataGrid[randomCord.y - i][randomCord.x]) == 'M')
            {
                (dataGrid[randomCord.y - i][randomCord.x]) = 'S';
                shipName[i].y = randomCord.y - i;
                shipName[i].x = randomCord.x;
            }

            else if ( (dataGrid[randomCord.y - i][randomCord.x]) != 'M')
            {
                printf("That new spot is not M");
                break;
            }
        }
        break;
    }
    if (randomNumberDirection == 2)
    {
        printf("\n going right\n");
        for(i=0; i<shipSize; i++)
        {
            if ((randomCord.x + i) == 10)
            {
                printf("\nThat new spot is out of bounds\n");
                break;
            }

            else if ( (dataGrid[randomCord.y][randomCord.x + i]) == 'M')
            {
                (dataGrid[randomCord.y][randomCord.x + i]) = 'S';
                shipName[i].y = randomCord.y;
                shipName[i].x = randomCord.x + i;
            }

            else if ( (dataGrid[randomCord.y][randomCord.x + i]) != 'M')
            {
                printf("\nThat new spot is not M\n");
                break;
            }
        }
        break;
    }
    if (randomNumberDirection == 3)
    {
        printf("\n going down\n");
        for(i=0; i<shipSize; i++)
        {
            if ((randomCord.y + i) == 10)
            {
                printf("\nThat new spot is out of bounds\n");
                break;
            }

            else if ( (dataGrid[randomCord.y + i][randomCord.x]) == 'M')
            {
                (dataGrid[randomCord.y + i][randomCord.x]) = 'S';
                shipName[i].y = randomCord.y + i;
                shipName[i].x = randomCord.x;
            }

            else if ( (dataGrid[randomCord.y + i][randomCord.x]) != 'M')
            {
                printf("That new spot is not M");
                break;
            }
        }
        break;        
    }
    if (randomNumberDirection == 4)
    {
        printf("\n going left\n");
        for(i=0; i<shipSize; i++)
        {
            if ((randomCord.x - i) == -1)
            {
                printf("\nThat new spot is out of bounds\n");
                break;
            }

            else if ( (dataGrid[randomCord.y][randomCord.x - i]) == 'M')
            {
                (dataGrid[randomCord.y][randomCord.x - i]) = 'S';
                shipName[i].y = randomCord.y;
                shipName[i].x = randomCord.x - i;
            }

            else if ( (dataGrid[randomCord.y][randomCord.x - i]) != 'M')
            {
                printf("That new spot is not M");
                break;
            }
        }
        break;        
    }
    }
}


void generateDataGrid(char dataGrid[10][10], CORD shipZCords[2],  CORD shipYCords[3],  CORD shipXCords[3],  CORD shipWCords[4],  CORD shipVCords[5])
{
    placeShips(2, shipZCords, dataGrid, 'Z');

}

int main(){
    
    //Makes 2D array base with all "M's" 
    char dataGrid[10][10];
    memset(dataGrid, 'M', sizeof(dataGrid));

    CORD shipZCords[2], shipYCords[3], shipXCords[3], shipWCords[4], shipVCords[5]; // cords for ship placements, decided when generating board
    int shipZSize = 2, shipYSize = 3, shipXSize = 3, shipWSize = 4, shipVSize = 5; // sizes of ship, used to know how big to make ship when generating board and when ship has been sunk (When shipSize == shipHits)
    int shipZHits = 0, shipYHits = 0, shipXHits = 0, shipWHits = 0, shipVHits = 0; // keeps track of how many times ship has been hit
    char shipZSunk = 'N', shipYSunk = 'N', shipXSunk = 'N', shipWSunk = 'N', shipVSunk = 'N'; // keeps track if ship is sunk or not "N" for no, "Y" for yes

    // Uses dataGrid[] and generates randomly located ships
    // Also gets values of all ship cordinates, to be- 
    // -used later when displaying "H/Hit" to the letter of the ship "Z/ZShip"

    while(1){
        CORD userInput;
        getUserInput(&userInput);
        printf("\nuserInput.y is %d, userInput.x is %d\n", userInput.y, userInput.x);
        generateDataGrid(dataGrid, shipZCords, shipYCords, shipXCords, shipWCords, shipVCords); 
        displayDataGrid(dataGrid, userInput);
        //GETS Y X VALUES FROM USER, CHECKS TO MAKE SURE IN RANGE, AND CONVERTS ALL TO INT
    
    }

    return 0;
}

