//#include "stdafx.h" 
#include "game.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void gameInit(GAME * g, SDL_bool fullscreen)
{
	
	srand((unsigned int)time(0));
	SDL_Init(SDL_INIT_VIDEO);
	g_window = SDL_CreateWindow("Snake",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		BOARD_CELL * BOARD_HORZ, BOARD_CELL * BOARD_VERT,
		SDL_WINDOW_SHOWN |
		(fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
	g_renderer = SDL_CreateRenderer(g_window, -1,
		SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	g->dir = UP;
	snakeInit(&g->s);
	g->score = 0;
	fruitGen(&g->f, &g->s);
	g->life = 3;
}

void gameShutdown(GAME * g)
{
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

void gameUpdate(GAME * g)
{
	snakeUpdate(&g->s);        
	switch (g->dir) {           
	case UP:    g->s.coords[0].y--; break;  
	case DOWN:  g->s.coords[0].y++; break;  
	case LEFT:  g->s.coords[0].x--; break; 
	case RIGHT: g->s.coords[0].x++; break;  
	}

	if (g->s.coords[0].x == g->f.loc.x &&
		g->s.coords[0].y == g->f.loc.y) {
		g->s.len++;
		g->score++;
		g->s.color = g->f.color;
		fruitGen(&g->f, &g->s); 
	}

	if (g->s.coords[0].x >= BOARD_HORZ) g->s.coords[0].x = 0;
	if (g->s.coords[0].x < 0) g->s.coords[0].x = BOARD_HORZ;
	if (g->s.coords[0].y >= BOARD_VERT) g->s.coords[0].y = 0;
	if (g->s.coords[0].y < 0) g->s.coords[0].y = BOARD_VERT;

	for (int i = 1; i < g->s.len; i++)
		if (g->s.coords[0].x == g->s.coords[i].x &&
			g->s.coords[0].y == g->s.coords[i].y)
			g->life--;
			if (g->life == 0)
			{
				gameOverDraw();
				/*g->running = SDL_FALSE;*/
			}
}

void gameDraw(GAME * g)
{
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);
	SDL_RenderClear(g_renderer);
	for (int i = 0; i < g->life; i++)
	{
		lifeDraw(42 + i*2, 1);
	}
	fruitDraw(&g->f);
	snakeDraw(&g->s);
	if (g->score > 9)
	{
		digitDraw((BOARD_HORZ >> 1) + BOARD_CELL * 6, BOARD_VERT * 2, g->score%10);
		digitDraw((BOARD_HORZ >> 1) + BOARD_CELL * 2, BOARD_VERT * 2, g->score/10);
	}
	else
	{
		digitDraw((BOARD_HORZ >> 1) + BOARD_CELL * 2, BOARD_VERT * 2, g->score);
	}
	SDL_RenderPresent(g_renderer);
}

void gameInput(GAME * g)
{
	SDL_Event   e;
	SDL_PollEvent(&e);
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:       if (g->dir != DOWN) { g->dir = UP; break; }
		case SDLK_DOWN:     if (g->dir != UP)	{ g->dir = DOWN; break;}
		case SDLK_LEFT:     if (g->dir != RIGHT) { g->dir = LEFT; break; }
		case SDLK_RIGHT:    if (g->dir != LEFT) { g->dir = RIGHT; break; }
		case SDLK_ESCAPE:   g->running = SDL_FALSE; break;
		}
		break;
	case SDL_QUIT:
		g->running = SDL_FALSE;
		break;
	}
}

void gameLoop(GAME * g)
{
	long timerBegin, timerDiff, timerSleep;
	g->running = SDL_TRUE;
	while (g->running) {
		timerBegin = SDL_GetTicks();
		gameUpdate(g);      
		gameInput(g);     
		gameDraw(g);       
							
		timerDiff = SDL_GetTicks() - timerBegin;
		timerSleep = GAME_FRAME_TIME - timerDiff;
		if (timerSleep > 0)
			SDL_Delay(timerSleep); 
	}
}