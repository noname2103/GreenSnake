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
	//snakeCell(s->coords[0], SDL_TRUE, s->color);
	snakeHeadDraw(s->coords[0].x, s->coords[0].y, s->color);
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
	/*rectDraw(f->loc.x * BOARD_CELL, f->loc.y * BOARD_CELL,
		BOARD_CELL, BOARD_CELL, f->color);*/
	appleDraw(f->loc.x * BOARD_CELL, f->loc.y * BOARD_CELL, f->color);
}

void lifeDraw(int x, int y,int w)
{
	heartDraw(x, y, w);
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

void heartDraw(int x, int y, int w)
{
	for (int i = 0; i < 3; i++)
	{
		rectDraw((x+i) * w, w*y,
			w, w, 4);

		rectDraw((x + 6 + i) * w, w * y,
			w, w, 4);
	}
	for (int i = 0; i < 5; i++)
	{
		rectDraw((x - 1 + i) * w, w * (y + 1),
			w, w, 4);
		if (i == 1 || i == 2)
		{
			rectDraw((x - 1 + i) * w, w * (y + 1),
				w, w, 15);
		}

		rectDraw((x +5 + i) * w, w * (y + 1),
			w, w, 4);
	}
	for (int i = 0; i < 13; i++)
	{
		rectDraw((x -2 + i) * w, w * (y + 2),
			w, w, 4);
		if (i == 1 || i == 2)
		{
			rectDraw((x - 2 + i) * w, w * (y + 2),
				w, w, 15);
		}
	}
	for (int i = 0; i < 13; i++)
	{
		rectDraw((x - 2 + i) * w, w * (y + 3),
			w, w, 4);
		if (i == 1)
		{
			rectDraw((x - 2 + i) * w, w * (y + 3),
				w, w, 15);
		}
	}
	for (int i = 0; i < 13; i++)
	{
		rectDraw((x - 2 + i) * w, w * (y + 4),
			w, w, 4);
	}
	for (int i = 0; i < 13; i++)
	{
		rectDraw((x - 2 + i) * w, w * (y + 5),
			w, w, 4);
	}
	int t = 11;
	int dem = -1;
	for (int i = 6; i < 12; i++)
	{
		for (int j = 0; j < t; j++)
		{
			rectDraw((x + dem + j) * w, w * (y + i),
				w, w, 4);
		}
		dem++;
		t = t - 2;
	}
}

void appleDraw(int x, int y, Uint32 color)
{
	int w = 1;
	for (int i = 0; i < 5; i++)
	{
		rectDraw((x + 12 + i)*w, y*w,
			w, w, 2);
	}
	for (int i = 0; i < 5; i++)
	{
		rectDraw((x + 11 + i)*w, (y+1)*w,
			w, w, 2);
	}
	for (int i = 0; i < 6; i++)
	{
		rectDraw((x + 9 + i)*w, (y + 2)*w,
			w, w, 2);
		if (i == 0 || i == 1)
		{
			rectDraw((x + 9 + i)*w, (y + 2)*w,
				w, w, 6);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		rectDraw((x + 9)*w, (y + 3 + i)*w,
			w, w, 6);
	}
	for (int i = 0; i < 11; i++)
	{
		rectDraw((x + 4 + i)*w, (y + 6)*w,
			w, w, color);
		if (i == 4 || i == 5 || i == 6 || i == 7 || i == 3)
		{
			rectDraw((x + 4 + i)*w, (y + 6)*w,
				w, w, 6);
		}
	}
	int t = 13;
	int dem = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < t; j++)
		{
			rectDraw((x + 4 - dem + j)*w, (y + 7 + i )*w,
				w, w, color);
		}
		dem++;
		t = t + 2;
	}
	for (int i = 0; i < 17; i++)
	{
		rectDraw((x + 1 + i)*w, (y + 10)*w,
			w, w, color);
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			rectDraw((x + j)*w, (y + 11 + i)*w,
				w, w, color);
		}	
	}
	for (int i = 0; i < 4; i++)
	{
		rectDraw((x + 3 + i)*w, (y + 10)*w,
			w, w, 12);
	}
	for (int i = 0; i < 2; i++)
	{
		rectDraw((x + 4 + i)*w, (y + 9)*w,
			w, w, 12);
		rectDraw((x + 3 + i)*w, (y + 11)*w,
			w, w, 12);
	}
	for (int i = 0; i < 17; i++)
	{
		rectDraw((x + 1 + i)*w, (y + 17)*w,
			w, w, color);
	}
	t = 17;
	dem = 1;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < t; j++)
		{
			rectDraw((x + dem + j)*w, (y + 18 + i)*w,
				w, w, color);
		}
		t = t - 2;
		dem++;
	}
	for (int i = 0; i < 3; i++)
	{
			rectDraw((x + 5 + i)*w, (y + 22)*w,
				w, w, color);
			rectDraw((x + 11 + i)*w, (y + 22)*w,
				w, w, color);
	}

}

void snakeHeadDraw(int a, int b, Uint32 color)
{
	int w = 3;
	int t = 4;
	int x = a*BOARD_CELL / w;
	int y = b*BOARD_CELL / w;
	x = x - 2;
	int dem = 1;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			rectDraw((x + 5 + j)*w, (y - i)*w,
				w, w, 12);
		}
	}
	rectDraw((x + 4)*w, (y - 3)*w,
		w, w, 12);
	rectDraw((x + 7)*w, (y - 3)*w,
		w, w, 12);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < t; j++)
		{
			rectDraw((x + 5 - dem + j)*w, (y +i)*w,
				w, w, color);
		}
		t = t + 2;
		dem++;
	}
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			rectDraw((x + 1+  j)*w, (y + 3 + i)*w,
				w, w, color);
		}
	}
	for (int i = 0; i < 8; i++)
	{
		rectDraw((x + 2 + i)*w, (y + 9)*w,
			w, w, color);
	}
	for (int i = 0; i < 2; i++)
	{
		rectDraw((x + 3+i)*w, (y + 4)*w,
			w, w, 15);
		rectDraw((x + 7+i)*w, (y + 4)*w,
			w, w, 15);
	}
	rectDraw((x + 3)*w, (y + 3)*w,
		w, w, 15);
	rectDraw((x + 8)*w, (y + 3)*w,
		w, w, 15);
	rectDraw((x + 4)*w, (y + 3)*w,
		w, w, 0);
	rectDraw((x + 7)*w, (y + 3)*w,
		w, w, 0);
}