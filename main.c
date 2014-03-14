/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <stdlib.h> //System calls
#include <windows.h>    //Sleep and Beep
#include <time.h>   //For time
#include <string.h>
#include "textutil.h"   //Thanks to Cristian Francu ^_^
#include "extraKeys.h"  //For detecting letters from the keyboard with getKey()

#define EFFECTS_SPEED 125
#define DELAY 80
#define INC 0x01
#define OUTC 0x02

void initializeGame();  //Drwaing the square
void startGame();   //The game
void putFood(); //Put some snails (YUM!)
void spawnMoney();
void clearConsole(int part);
void commandParse(char *command);
int getCollide(int x, int y);   //If we ate a snail...
int random();   //Get a random number from 1 to 19

void die();

char game[20][20];  //The matrix with the things from the screen
unsigned char power[2];
int points;
int money;
int multiplyer = 1;
int speed;

int main()
{
    hideCursor();
    clearScreen();
    putChar(9, 9, '*');
    startGame();
    return 0;
}

void initializeGame(){
    system("color 07");

    //Drawing the square
    for(int i = 0; i < 20; i++){
        putChar(i, 0, '#');
        putChar(i, 19, '#');
        putChar(0, i, '#');
        putChar(19, i, '#');

        game[i][0] = '#';
        game[i][19] = '#';
        game[0][i] = '#';
        game[19][i] = '#';
    }

    GotoXY(0, 20);
}

void startGame(){
    int direction;  //1 for up, 2 for down, 3 for left, 4 for right
    int xA, yA; //Coordinates of the Avatar (a star???)
    int collision;  //If we ate a snail...

    putStr(30, 5, "The Omnomnomer");
    putStr(30, 7, "Use the arrows to move the star (or WASD)");
    putStr(30, 8, "You need to eat the snails(@).");

    initializeGame();

    speed = DELAY;
    collision = 1;
    direction = 0;  //We are not moving
    xA = 9;
    yA = 9;
    for(int i = 1;;){
        initializeGame();   //Re-draw the square

        //If the food was eat
        if(collision == 1){
            putFood();  //Get some food
            collision = 0;  //We need to eat that food!
        }

        Sleep(speed);  //Calm down, computer

        //Setting the direction
        if(getKey(VK_UP) || getKey(VK_W)){
            direction = 1;
            i++;
        }
        else if(getKey(VK_DOWN) || getKey(VK_S)){
            direction = 2;
            i++;
        }
        else if(getKey(VK_LEFT) || getKey(VK_A)){
            direction = 3;
            i++;
        }
        else if(getKey(VK_RIGHT) || getKey(VK_D)){
            direction = 4;
            i++;
        }
        else if(getKey(VK_ESCAPE)){
            direction = 0;
        }
        else if(getKey(VK_C)){
            showCursor();
            clearConsole(OUTC);
            direction = 0;
            printf("\b\b\b\b\b\b\b\b\b\b\b\b");

            char str[81];
            gets(str);
            commandParse(str);
        }

        game[xA][yA] = ' ';

        //We are moving!!!
        if(!(xA == 0 || xA == 19 || yA == 0 || yA == 19)){
            switch(direction){
                case 1: putChar(xA, yA, ' '); yA--; putChar(xA, yA, '*'); break;
                case 2: putChar(xA, yA, ' '); yA++; putChar(xA, yA, '*'); break;
                case 3: putChar(xA, yA, ' '); xA--; putChar(xA, yA, '*'); break;
                case 4: putChar(xA, yA, ' '); xA++; putChar(xA, yA, '*'); break;
            }
        }
        else{   //If we hit the border, GAME OVER
            die();
        }
        //If the powers are off
        if(i % 5 == 0)
            spawnMoney();
        if(i % 50 == 0){
            speed = DELAY;
            multiplyer = 1;
        }
        //Where are we?
        collision = getCollide(xA, yA);
        game[xA][yA] = '*';
        clearConsole(INC);
    }
}

void putFood(){
    int xF, yF; //Coordinates of the food

    xF = random();  //Get random coordinates
    yF = random();
    game[xF][yF] = '@'; //Put a snail

    putChar(xF, yF, '@');   //Put a snail ON THE SCREEEN
}

//Put some money...
void spawnMoney(){
    int x, y;

    srand(time(NULL));
    //Only in the corner
    x = rand() % 4 + 1;
    y = rand() % 4 + 2;
    putChar(x, y, '$');
    game[x][y] = '$';
}

int random(){
    srand((int)time(0));

    return (rand() % 16) + 2;
}

int getCollide(int x, int y){
    int ret;

    //Show the stats
    char mn[10], pt[10];
    sprintf(pt, "%d Points", points);
    putStr(30, 10, pt);

    sprintf(mn, "%d Money", money);
    putStr(70, 10, mn);

    //If we ate a snail
    ret = 0;
    if(game[x][y] == '@'){
        points += 10 * multiplyer;
        ret = 1;
    }
    //If we got money
    else if(game[x][y] == '$'){
        money++;
        game[x][y] = ' ';
    }

    return ret;
}

void die(){
    //Special effects
    clearScreen();
    printf("You died!\nMADE IN ROMANIA\nYou scored %d POINTS and %d MONEY!", points, money);
    //Produce the Romanian Flag on the screen
    int j = 1;
    for(;;){
        switch(j){
            case 1: system("color 17"); j++; break;
            case 2: system("color E0"); j++; break;
            case 3: system("color C7"); j = 1; break;
        }
        Sleep(EFFECTS_SPEED);
    }
}

void commandParse(char str[81]){
            char msg[81];
            if(strncmp(str, "/say", 4) == 0){
                printf(strcat(msg, "                                "));
            }
            else if(strcmp(str, "/buy") == 0){
                printf("Type \"/buy <power>\". Power can be slow or dblpoint.                    ");
            }
            else if(strncmp(str, "/buy", 4) == 0){
                sscanf(str, "/buy %s", &msg);

                if((strncmp(msg, "slow", 4) == 0) && money >= 1){
                    power[0]++;
                    money -= 1;

                    printf("You have %d slowness powers!                     ", power[0]);
                }
                else if((strncmp(msg, "dblpoint", 8) == 0) && money >= 5){
                    power[1]++;
                    money -= 5;
                    multiplyer = 2;
                    printf("You have %d double points powers!                ", power[1]);
                }
                getCollide(1, 1);
            }
            else if(strcmp(str, "/use") == 0){
                printf("Usage: /use <power>");
            }
            else if(strncmp(str, "/use", 4) == 0){
                sscanf(str, "/use %s", &msg);
                if(strcmp(msg, "slow") == 0 && power[0] > 0){
                    speed = 120;
                    power[0]--;
                }
                else if(strcmp(msg, "dblpoint") == 0 && power[1] > 0){
                    multiplyer = 2;
                    power[1]--;
                }
            }
            else if(strcmp(str, "/spawnSnail") == 0){
                putFood();
            }
            else if(strncmp(str, "/die", 4) == 0){
                die();
            }
            hideCursor();
}

void clearConsole(int part){
    if(part == INC){
        GotoXY(0, 20);
        printf("                                                            ");
    }
    else if(part == OUTC){
        GotoXY(0, 21);
        printf("                                                            ");
    }
    GotoXY(0, 20);
}
