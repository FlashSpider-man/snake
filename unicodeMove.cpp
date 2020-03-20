#include <iostream>
#include <ncurses.h>
#include <stdlib.h>
#define y 40
#define x 125
#define z 8000
int score;
int realScore;
enum direction{Up, Right, Left, Down}direct;
int chart[y][x];
int amount;
int recordTime;
void deathBorder()
{
    move(1,0);
    for(int i = 0; i < x; i++){
        printw("_");
    }
    for(int j = 2; j < y; j++){
        move(j,0);
        printw("|");
        move(j,x);
        printw("|");
    }
    move(y,0);
    for(int k = 0; k < x; k++){
        printw("-");
    }
}
void clearArray()
{
    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++){
            chart[i][j] = 0;
        }
    }
}
void checkArrays()
{
    for(int i = 0; i < y; i++)
    {
        for(int j = 0; j < x; j++){
            if (chart[i][j] != 0)
            {
                move(i,j);
                printw("o");
            }
        }
    }
}
void arrayAmount()
{
    amount = 0;
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            if(chart[i][j] != 0){
                amount++;
            }
        }
    }
}
void correctArrays()
{
    while(amount > score){
        int numStoreY = 0;
        int numStoreX = 0;
        int store = recordTime;
        for(int i = 0; i < y; i++){
            for(int j = 0; j < x; j++){
                if(chart[i][j] != 0 && chart[i][j] < store){
                    store = chart[i][j];
                    numStoreY = i;
                    numStoreX = j;
                }
            }
        }
        chart[numStoreY][numStoreX] = 0;
        arrayAmount();
    }
}
void updateArrays(int lines, int spaces)
{
    chart[lines][spaces] = recordTime;
}
void putTarget(int xPos, int yPos)
{
    move(xPos, yPos);
    printw("x");
}
void spot(int &xPos, int &yPos)
{
    xPos = rand() % 25 + 1;
    yPos = rand() % 50 + 1;
}
void dir(int &lines, int &spaces, bool &controls, int &xPos, int &yPos)
{   
    while(controls == true)
    {
        if(lines == xPos && spaces == yPos){
            ++score;
            spot(xPos, yPos);
            putTarget(xPos, yPos);
        }
        move(0,0);
        realScore = score - 2;
        printw("%d\n", realScore);
        move(lines,spaces);
        int ch;
        move(0,0);
        ch = getch();
        halfdelay(1);
        clear();
        switch(ch){
            case KEY_RIGHT:
                spaces++;
                direct = Right;
                break;
            case KEY_UP:
                lines--;
                direct = Up;
                break;
            case KEY_DOWN:
                lines++;
                direct = Down;
                break;
            case KEY_LEFT:
                spaces--;
                direct = Left;
                break;
            case 'a':
                controls = false;
                break;
            default:
                switch(direct){
                    case Up:
                        lines--;
                        break;
                    case Left:
                        spaces--;
                        break;
                    case Right:
                        spaces++;
                        break;
                    case Down:
                        lines++;
                        break;
                }
        }
        if(lines < 2 || spaces < 1 || spaces > x || lines > y || chart[lines][spaces] != 0)
        {
            clear();
            printw("You died. Final score: %d", realScore);
            controls = false;
        }
        else
        {
        deathBorder();
        updateArrays(lines,spaces);
        arrayAmount();
        correctArrays();
        checkArrays();
        putTarget(xPos,yPos);
        }
        recordTime++;
        refresh();
    }
}
void setup(int &spaces, int &lines, bool &controls, int &xPos, int &yPos)
{
    score = 2;
    move(2,1);
    printw("o");
    refresh();
    putTarget(8,8);
    xPos = 8;
    yPos = 8;
    spaces = 1;
    lines = 2;
    controls = true;
    direct = Right;
    amount = 1;
    recordTime = 1;
    clearArray();
}
int main(int argc, char *argv[])
{
	initscr();
    keypad(stdscr, true);
    int spaces, lines, xPos, yPos;
    bool controls;
    setup(spaces, lines, controls, xPos, yPos);
    dir(lines, spaces, controls, xPos, yPos);
    cbreak();
    getch();
	endwin();
	return 0;
}