#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include "game.h"

#define ROWS 40.0               // no of row squares on the screen
#define COLUMNS 40.0            // no of column squares on the screen
#define MAX 50
#define UP 1                    
#define RIGHT 2
#define DOWN -1
#define LEFT -2

void initGrid(int, int);
void draw_grid();                   //used to draw grid 
void draw_food();                   // a square shape indicated as food
void draw_snake();                  // as the snake passes the red square its length increases by one pixel
std::ofstream ofile;
std::ifstream ifile;
bool game_over = false; //used to display message on the console
extern int sDirection;
int score = 0;

void init();
void display_callback();
void input_callback(int, int, int);
void reshape_callback(int, int);
void timer_callback(int);       //to time the moment of snake on the screen

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    initGrid(COLUMNS, ROWS);
}

//Callbacks
void display_callback()
{
    if (game_over)              //to display final score
    {
        ofile.open("score.dat", std::ios::trunc);   //to open the src file and calculate the score
        ofile << score << std::endl;
        ofile.close();                              //closes the file
        ifile.open("score.dat", std::ios::in);
        char a[4];
        ifile >> a;
        std::cout << a;
        char text[50] = "Your score : ";
        strcat_s(text, a);              //concatenates the the score value with string text
        std::cout << text;
        exit(0);
    }
    glClear(GL_COLOR_BUFFER_BIT);       //used to clear a buffer
    glLoadIdentity();
    draw_grid();                            //the grid is drawn using the 
    draw_food();
    draw_snake();
    glutSwapBuffers();                  //used to swap the buffers
}
void reshape_callback(int w, int h)
{
    glViewport(0, 0, (GLfloat)w, GLfloat(h));     // first two parameters specify leftmost and rightmost window
                                                  // last tow parameters specify the range where obj is visible
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    //leftmost point of origin 0.0 
    //-ve coming towards us +ve going towards screen
    glOrtho(0.0, COLUMNS, 0.0, ROWS, -1.0, 1.0); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void timer_callback(int) //to set fps
{
    glutPostRedisplay();
    glutTimerFunc(100, timer_callback, 0);
}
void input_callback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:               //keyboard key up to move the snake up
        if (sDirection != DOWN)
            sDirection = UP;
        break;
    case GLUT_KEY_DOWN:             //keyboard key up to move the snake down
        if (sDirection != UP)
            sDirection = DOWN;
        break;
    case GLUT_KEY_RIGHT:            //keyboard key up to move the snake right
        if (sDirection != LEFT)
            sDirection = RIGHT;
        break;
    case GLUT_KEY_LEFT:             ////keyboard key up to move the snake left
        if (sDirection != RIGHT)
            sDirection = LEFT;
        break;
    }
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(600, 600);
    glutCreateWindow("SNAKE v1.0");
    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutSpecialFunc(input_callback);
    glutTimerFunc(100, timer_callback, 0);          //100 frames have been set
    init();
    glutMainLoop();
    return 0;
}