#include "header.c"
#include "struct.h"
#include "init&quit.c"
#include "texture.c"
#include "input.c"
#include "player.c"
#include "enemies.c"
#include "blit.c"
#include "bullet.c"

int main(int argc, char *argv[])
{
	int width = 1920;
	int height = 1017;
	int time[2] = {0, 25}, x = 0, scoring = 0;
	Entity player;
	Entity enemies[5];
	Stuff ui;
	App game;
	memset(&game, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	memset(&enemies, 0, sizeof(Entity));
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
	
	/* Load texture */
	get_texture(game, &player, enemies, &ui);

	/* Reset all */
	reset(&player, enemies, width, height);
	

	for (;;)
	{
		while (game.play == 0) {
			prepareScene(game);
			doInput(&game, &player);
			for (int i = 0; i < 2; i++)
				blit_wall(ui.texture[i], game, height, width, i);
			blit_player(player.texture_player[player.dp], player, game, height, width);
			blit_play(ui.texture[5], game, height, width);
			presentScene(game);
			if (game.quit == 1)
				break;		
		}
		SDL_GetWindowSize(game.window, &width, &height);
		prepareScene(game);

		/* Input */
		doInput(&game, &player);

		/* Player */
			/* Direction && limit map */
		move_player(&player, &game, height, width);
			/* Shooting */
		shoot(&player, game, time);
			/* Bullet after shooting */
		bullet(&player, game, height, width);
			/* Reload */
		reload(game, &player);
			/* Check_Hit */
		for (int i = 0; i < 5; i++)
			check_hit(&player, &enemies[i], &scoring);

		/* Enenmies */
			/* Direction && limit map */
		move_enemies(enemies, height, width, x);
			/* Aim to player */
		get_way(enemies, player);
			/* Shooting */
		shoot_enemies(enemies, time);
			/* Bullet after shooting */
		for (int i = 0; i < 5; i++)
			bullet(&enemies[i], game, height, width);
			/* Reload */
		for (int i = 0; i < 5; i++)
			reload(game, &enemies[i]);
		/* Check_Hit */
		for (int i = 0; i < 5; i++)
			check_hit(&enemies[i], &player, &scoring);	

		/* Display */
		display_all(&player, enemies, &ui, game, width, height, &x);

		presentScene(game);
		SDL_Delay(16);
		//printf("%d\n", game.play);

		/* Pause */
		while (game.pause == 1) {
			doInput(&game, &player);
			prepareScene(game);
			display_all(&player, enemies, &ui, game, width, height, &x);
			blit_pause(ui.texture[8], game, height, width);
			presentScene(game);
		}

		/* Quit */
		while (check_life(player, enemies)) {
			game.play = 0;
			doInput(&game, &player);
			prepareScene(game);
			blit_pause(ui.texture[4], game, height, width);
			x = 1800;
			for (int i = 6; i < 8; i++) {
				blit_menu(ui.texture[i], game, width, height, x);
				x = -100;
			}
			presentScene(game);
			if (game.play == 1) {
				reset(&player, enemies, width, height);
				game.play = 0;
				break;
			}
			if (game.pause == 1)
				break;
		}
		if (game.pause == 1 && check_life(player, enemies))
			break;
	}
	printf("You kill %d enemies in total!", scoring);
    SDL_bye(game);
	return 0;
} 