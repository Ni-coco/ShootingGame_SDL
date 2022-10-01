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
	
	/* Position player */
	player.nb = 0;
	player.destx = 0;
	player.phealth = 3;
	player.radius = 50;
	player.px = (width - player.radius) / 2;
	player.py = (height - player.radius) / 2;

	/* Position enemies & life */
	for (int i = 0; i < 5; i++) {
		enemies[i].nb = 0;
		enemies[i].phealth = 1;
		enemies[i].radius = 50;
		enemies[i].px = 1940;
		enemies[i].py = rand() % 1017;
		for (int j = 0; j < 6; j++) {
			enemies[i].bx[j] = 9999;
			enemies[i].by[j] = 9999;
		}
	}

	/* Load texture */
	get_texture(game, &player, enemies, &ui);
	doInput(&game, &player);

	while (game.go == 0) {
		prepareScene(game);
		doInput(&game, &player);
		for (int i = 0; i < 2; i++)
			blit_wall(ui.texture[i], game, height, width, i);
		blit_player(player.texture_player[player.dp], player, game, height, width);
		blit_enter(ui.texture[4], game, height, width);
		presentScene(game);
		if (game.quit == 1)
			break;		
	} 
	
	for (;;)
	{
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

		/* Quit */
		if (game.quit == 1 || check_life(player, enemies))
			break;		

		/* Display */
		blit_player(player.texture_player[player.dp], player, game, height, width);
		for (int i = 0; i < 5; i++)
			blit_player(enemies[i].texture_player[enemies[i].dp], enemies[i], game, height, width);
		for (int i = 0; i < 2; i++)
			blit_wall(ui.texture[i], game, height, width, i);
		x = 100;
		for (int i = 0; i < player.phealth; i++)
			blit_life(ui.texture[2], game, height, width, &x);
		x = 1550;
		for (int i = 5; i >= player.nb; i--)
			blit_ammo(ui.texture[3], game, height, width, &x);

		presentScene(game);
		SDL_Delay(16);
	}
	printf("You kill %d enemies!", scoring);
    SDL_bye(game);
	return 0;
}