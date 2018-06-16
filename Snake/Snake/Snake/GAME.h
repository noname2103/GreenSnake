#pragma once
#include "ENTITIES.h"
//#include "stdafx.h"
#include "global.h" 
#include "game.h" 

#define GAME_MAX_FPS        12
#define GAME_FRAME_TIME     (1000 / GAME_MAX_FPS) 

typedef struct game        
{
	FRUIT f;                
	SNAKE s;     
	int score;
	int life;
	DIRECTION dir;          
	SDL_bool running;       
} GAME;

void gameInit(GAME * g, SDL_bool fullscreen);

void gameShutdown(GAME * g);

void gameLoop(GAME * g);

void gameUpdate(GAME * g);

void gameDraw(GAME * g);

void gameInput(GAME * g);

void block(int x, int y);
