#pragma once
#include "GLOBAL.h"

#define SNAKE_MAXLEN	100
#define SNAKE_INITLEN   17

typedef struct snake {
	COORD   coords[SNAKE_MAXLEN];
	int     len;
	Uint32 color;
} SNAKE;

typedef struct fruit {
	COORD   loc;                    
	Uint32  color;                 
} FRUIT;

void snakeCell(COORD c, SDL_bool head);


void snakeInit(SNAKE * s);

void snakeDraw(const SNAKE * s);

void snakeUpdate(SNAKE * s);

void fruitGen(FRUIT * f, const SNAKE * s);

void fruitDraw(const FRUIT * f);

void lifeDraw(int x, int y);

void gameOverDraw();
