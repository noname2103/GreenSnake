#include "GAME.h"
#include<SDL2/SDL_mixer.h>

static SDL_Surface *g_screen = NULL;
static SDL_Surface *g_bkground = NULL;
static SDL_Event g_even;

static Mix_Chunk* g_sound_bullet[3];
static Mix_Chunk* g_sound_explosion = NULL;
static Mix_Chunk* g_sound_ex_main = NULL;

#ifdef _MSC_VER
#	pragma comment(lib, "sdl2main.lib")
#	pragma comment(lib, "sdl2.lib")

#	pragma comment(linker, "/entry:\"mainCRTStartup\"")
#	pragma comment(linker, "/subsystem:WINDOWS")
#endif

int main(int argc, char ** argv)
{
	GAME g;
	gameInit(&g, SDL_FALSE);

	/*if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == FAILED)
	{
		return false;
	}

	g_sound_bullet[0] = Mix_LoadWAV(g_name_audio_bullet_main1);		"laser.wav"
	g_sound_bullet[1] = Mix_LoadWAV(g_name_audio_bullet_main2);		Fire1.wav
	g_sound_explosion = Mix_LoadWAV(g_name_audio_ex_main);
	g_sound_ex_main = Mix_LoadWAV(g_name_audio_ex_threats);


	if (g_sound_bullet[0] == NULL || g_sound_bullet[1] == NULL || g_sound_explosion == NULL)
	{
		return false;
	}*/
	gameLoop(&g);
	gameShutdown(&g);
	return 0;
}
