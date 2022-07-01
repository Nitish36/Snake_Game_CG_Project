#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include "game.h"
#define MAX 50
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2

void initGrid(int, int);
void draw_grid();
void draw_food();
void draw_snake();
void unit(int, int);            //each pixel unit is taken as a single square
int random(int, int);

bool length_inc = false;
bool seedflag = false;
extern int score;
extern bool game_over;
bool food = false;
int rows = 0, columns = 0;
int sDirection = RIGHT;         //initially the snake will be seeing moving right
int foodx, foody;               // coordinate position of the food
int posx[MAX + 1] = { 4,3,2,1,0,-1,-1 };
int posy[MAX + 1] = { 10,10,10,10,10,10,10 };
int length = 7;


void initGrid(int x, int y)         // specify the coordinate values so as to create the grid
{
    columns = x;
    rows = y;
}
//drawing of grid
void draw_grid()
{
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            unit(i, j);
        }
    }
}

void draw_snake()
{
    for (int i = length - 1; i > 0; i--)
    {
        posx[i] = posx[i - 1];
        posy[i] = posy[i - 1];
    }
    for (int i = 0; i < length; i++)
    {
        glColor3f(0.0, 1.0, 0.0);
        if (i == 0)
        {
            glColor3f(0.0, 0.0, 1.0);
            switch (sDirection)
            {
            case UP:                //keyboard key UP moves the snake one unit up 
                posy[i]++;
                break;
            case DOWN:              //keyboard key DOWN moves the snake one unit down
                posy[i]--;
                break;
            case RIGHT:             //keyboard key right moves the snake one unit right
                posx[i]++;
                break;
            case LEFT:              //keyboard key left moves the snake one unit left
                posx[i]--;
                break;
            }
            if (posx[i] == 0 || posx[i] == columns - 1 || posy[i] == 0 || posy[i] == rows - 1) 
                
                //if it touches the red squares on the corener edges  game over


                game_over = true;
            else if (posx[i] == foodx && posy[i] == foody)
            {
                food = false;
                score++;
                if (length <= MAX)
                    length_inc = true;
                if (length == MAX)
                    std::cout << "The snake has reached max length";
            }
            for (int j = 1; j < length; j++)
            {
                if (posx[j] == posx[0] && posy[j] == posy[0])
                    game_over = true;
            }
        }
        glBegin(GL_QUADS);
        glVertex2d(posx[i], posy[i]); glVertex2d(posx[i] + 1, posy[i]); glVertex2d(posx[i] + 1, posy[i] + 1); glVertex2d(posx[i], posy[i] + 1);
        glEnd();
    }
    if (length_inc)     
    {
        length++;
        length_inc = false; //to reset the length value
    }
}

void draw_food()
{
    if (!food)
    {
        foodx = random(2, columns - 2); //Since it should not cross the red line
        foody = random(2, rows - 2);
        std::cout << foodx << foody << std::endl;
        food = true;
    }
    glBegin(GL_QUADS);
    glVertex2d(foodx, foody); glVertex2d(foodx + 1, foody); glVertex2d(foodx + 1, foody + 1); glVertex2d(foodx, foody + 1);
    glEnd();
}

void unit(int x, int y)
{
    glLoadIdentity();
    //x==0 y==0 to check if the box is left and bottom of the screen
    //x==columns-1 and y==rows-1 if the box is towards the end
    if (x == 0 || x == columns - 1 || y == 0 || y == rows - 1)
    {
        //edges of the box are red hence snake is not allowed to move here
        glLineWidth(4.0);
        glColor3f(1.0, 0.0, 0.0);
    }
    else
    {   
        //edges are coloured white 
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(1.0);
    }
    glBegin(GL_LINES);
    //bottom left corner
    glVertex2d(x, y);
    glVertex2d(x + 1, y);
    glVertex2d(x + 1, y); glVertex2d(x + 1, y + 1);
    glVertex2d(x + 1, y + 1); glVertex2d(x, y + 1);
    glVertex2d(x, y + 1); glVertex2d(x, y);
    glEnd();
}
int random(int _min, int _max) //for random position of food
{
    if (!seedflag)
    {
        srand(time(NULL));
        seedflag = true;
    }
    else
        seedflag = false;
    return _min + rand() % (_max - _min);
}
