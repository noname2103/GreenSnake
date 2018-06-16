//#include "stdafx.h" 
#include "entities.h" 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void snakeCell(COORD c, SDL_bool head,Uint32 color)
{
	int color1 = head ? color-1 : color;
	rectDraw(c.x * BOARD_CELL, c.y * BOARD_CELL, BOARD_CELL, BOARD_CELL, color1);
}

void snakeInit(SNAKE * s)
{
	s->coords[0].x = (BOARD_HORZ >> 1);
	s->coords[0].y = (BOARD_VERT >> 1);
	s->len = SNAKE_INITLEN;
	s->color = 2;
	for (int i = 1; i < s->len; i++) {
		s->coords[i].x = s->coords[i - 1].x;
		s->coords[i].y = (BOARD_VERT >> 1) + i;
	}
}


void snakeDraw(const SNAKE * s)
{
	snakeCell(s->coords[0], SDL_TRUE, s->color);
	for (int i = 1; i < s->len; i++)
		snakeCell(s->coords[i], SDL_FALSE, s->color);
}

void snakeUpdate(SNAKE * s)
{
	for (int i = s->len; i > 0; i--)
		s->coords[i] = s->coords[i - 1];
}

void fruitGen(FRUIT * f, const SNAKE * s)
{
	SDL_bool ok = SDL_FALSE;
	int i;
	while (!ok) {
		f->loc.x = rand() % BOARD_HORZ;
		f->loc.y = rand() % BOARD_VERT;
		for (i = 0; i < s->len; i++) {
			if (f->loc.x != s->coords[i].x &&
				f->loc.y != s->coords[i].y)
				continue;
		}
		if (i == s->len)
			ok = SDL_TRUE;
	}
	f->color = rand() % 14 + 1;
}

void fruitDraw(const FRUIT * f)
{
	rectDraw(f->loc.x * BOARD_CELL, f->loc.y * BOARD_CELL,
		BOARD_CELL, BOARD_CELL, f->color);
}

void lifeDraw(int x, int y)
{
	rectDraw(x * BOARD_CELL,y * BOARD_CELL,
		BOARD_CELL, BOARD_CELL,4);
}

void gameOverDraw()
{
	//Ve chu O
	for (int i = 0; i < 3; i++)
	{
		rectDraw((30 + i) * BOARD_CELL, 20 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw(29 * BOARD_CELL, (21 + i) * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw(33 * BOARD_CELL, (21 + i) * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw((30 + i) * BOARD_CELL, 24 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
	}

		rectDraw((35) * BOARD_CELL, 20 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw((35) * BOARD_CELL, 21 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw((36) * BOARD_CELL, 22 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw((36) * BOARD_CELL, 23 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw((37) * BOARD_CELL, 24 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw((38) * BOARD_CELL, 22 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw((38) * BOARD_CELL, 23 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw((39) * BOARD_CELL, 20 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
		rectDraw((39) * BOARD_CELL, 21 * BOARD_CELL,
			BOARD_CELL, BOARD_CELL, 4);
}
