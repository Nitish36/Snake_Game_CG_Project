#ifndef GAME_H_INCLUDED //checks if file is included
#define GAME_H_INCLUDED

#define MAX 50
#define UP 1
#define RIGHT 2
#define DOWN -1
#define LEFT -2

void initGrid(int, int);
void draw_grid();
void draw_food();
void draw_snake();


#endif // GAME_H_INCLUDED
