#include "header.c"
#include "struct.h"
#include "init&quit.c"
#include "texture.c"
#include "input.c"
#include "player.c"
#include "blit.c"
#include "bullet.c"

int main(int argc, char *argv[])
{
	int width = 1920;
	int height = 1017;
	int d = 0, i = 0, n = 0, time = 0, life = 3, x = 0;
	Entity player;
	Stuff ui;
	App game;
	memset(&game, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	memset(&ui, 0, sizeof(Stuff));

	/* Init window */
	IMG_Init(IMG_INIT_PNG);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	game.window = SDL_CreateWindow("ShooterGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (!game.window)
	{
		printf("Failed to open %d x %d window: %s\n", width, height, SDL_GetError());
		exit(1);
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
	if (!game.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
	
	/* Position player */
	player.px = (width / 2);
	player.py = (height / 2);

	/* Load texture */
	get_texture(game, &player, &ui);

	for (;;)
	{
		SDL_GetWindowSize(game.window, &width, &height);
		prepareScene(game);

		/* Input */
		doInput(&game, player, &d);

		/* Direction && limit map */
		move_player(&player, &game, &d, height, width);
		
		/* Shooting */
		shoot(&player, game, d, &n, &time);

		/* Bullet after shooting */
		bulletillw(&player, game, height, width, i);

		/* Reload */
		reload(game, &n);

		/* Quit */
		if (game.quit == 1)
			break;

		/* Display player && wall */
		blit_player(player.texture_player[d], player, game, height, width, d);
		for (int i = 0; i < 2; i++)
			blit_wall(ui.texture[i], game, height, width, i);
		x = 100;
		for (int i = 0; i < life; i++)
			blit_life(ui.texture[2], game, height, width, &x);
		x = 1550;
		for (int i = 5; i >= n; i--)
			blit_ammo(ui.texture[3], game, height, width, &x);

		presentScene(game);
		SDL_Delay(16);
	}
    SDL_bye(game);
	return 0;
}