#pragma once
#include <SDL2/sdl.h>
#include <stdio.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>

#define BOARD_CELL		22
#define BOARD_HORZ		48
#define BOARD_VERT		30

#define CR_BLACK		0
#define CR_BLUE			1

#define CR_GREEN		2
#define CR_CYAN			3
#define CR_RED			4
#define CR_MAGENTA		5
#define CR_BROWN		6
#define CR_GRAY			7
#define CR_DKGRAY		8
#define CR_BRBLUE		9
#define CR_BRGREEN		10
#define CR_BRCYAN		11
#define CR_BRRED		12
#define CR_BRMAGENTA	13
#define CR_YELLOW		14
#define CR_WHITE		15
#define CR_SNAKE_HEAD	2
#define CR_SNAKE_BODY	3

#define CR_MAX_COLORS	18

#define DIGIT_WIDTH     3               /* chiều rộng 1 ký số */ 
#define DIGIT_HEIGHT    5               /* chiều cao 1 ký số */ 

typedef enum direction{DOWN,LEFT,RIGHT,UP}DIRECTION;

typedef struct coord {
	int x, y;
}COORD;

extern SDL_Window * g_window;
extern SDL_Renderer * g_renderer;
extern char DIGITS[10 * DIGIT_HEIGHT];

extern unsigned long GAME_PALETTE[CR_MAX_COLORS];

void setColor(int c);

void rectDraw(int x, int y, int w, int h, unsigned long color);

void digitDraw(int x, int y, int digit);
