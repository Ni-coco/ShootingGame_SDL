#include "header.c"
#include "struct.h"
#include "input.c"
#include "init&quit.c"
#include "blit.c"
#include "texture.c"

int main(int argc, char *argv[])
{
	int width = 1920;
	int height = 1017;
	int d = 0, i = 0, n = 0, time = 0;
	Entity bullet[6];
	Entity player;
	Entity ui;
	App game;
	memset(&game, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	memset(&bullet, 0, sizeof(Entity));
	memset(&ui, 0, sizeof(Entity));

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
	printf("width = %d\n", width);
	printf("height = %d\n", height);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
	if (!game.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	/* Position player */
	player.x = (width / 2);
	player.y = (height / 2);

	/* Load texture */
	get_texture(game, &player, bullet, &ui);

	for (;;)
	{
		SDL_GetWindowSize(game.window, &width, &height);
		prepareScene(game);

		/* Direction && limit map */
		doInput(&game, player, &d, n);
		if (game.up && game.left)
			d = 4;
		if (game.up && game.right)
			d = 5;
		if (game.down && game.left)
			d = 6;
		if (game.down && game.right)
			d = 7;
		if (game.up && player.y > (height * 0.05)) {
			if (game.left || game.right)
				player.y -= (width / 350);
			else
				player.y -= (width / 200);
		}
		if (game.down && player.y < (height - (height * 0.18))) {
			if (game.left || game.right)
				player.y += (width / 350);
			else
				player.y += (width / 200);
		}
		if (game.left && player.x > (width * 0.027))
			player.x -= (width / 200);
		if (game.right && player.x < (width - (width * 0.1)))
			player.x += (width / 200);

		/* Shooting */
		if (game.shoot && n <= 5 && !time) {
			bullet[n].d = d;
			if (d == 0) {
				bullet[n].x = player.x + 48;
				bullet[n].y = player.y;
			}
			else if (d == 1) {
				bullet[n].x = player.x + 27;
				bullet[n].y = player.y + 115;
			}
			else if (d == 2) {
				bullet[n].x = player.x;
				bullet[n].y = player.y + 25;
			}
			else if (d == 3) {
				bullet[n].x = player.x + 115;
				bullet[n].y = player.y + 48;
			}
			else if (d == 4) {
				bullet[n].x = player.x;
				bullet[n].y = player.y;
			}
			else if (d == 5) {
				bullet[n].x = player.x + 120;
				bullet[n].y = player.y;
			}
			else if (d == 6) {
				bullet[n].x = player.x;
				bullet[n].y = player.y + 68;
			}
			else if (d == 7) {
				bullet[n].x = player.x + 68;
				bullet[n].y = player.y + 120;
			}
			bullet[n].health = 1;
			time = 15;
			n++;
			if (n == 6)
				printf("-- Press 'R' to reload --\n");
		}
		if (time)
			time--;

		/* Bullet after shooting */
		i = 0;
		while (i < 6) {
			if (bullet[i].d == 0)
				bullet[i].y += -16;
			if (bullet[i].d == 1)
				bullet[i].y += 16;
			if (bullet[i].d == 2)
				bullet[i].x += -16;
			if (bullet[i].d == 3)
				bullet[i].x += 16;
			if (bullet[i].d == 4) {
				bullet[i].x += -10;
				bullet[i].y += -10;
			}
			if (bullet[i].d == 5) {
				bullet[i].x += 10;
				bullet[i].y += -10;
			}
			if (bullet[i].d == 6) {
				bullet[i].x += -10;
				bullet[i].y += 10;
			}
			if (bullet[i].d == 7) {
				bullet[i].x += 10;
				bullet[i].y += 10;
			}
			if (bullet[i].x > width || bullet[i].x < 0 || bullet[i].y > height || bullet[i].y < 0)
				bullet[i].health = 0;
			if (bullet[i].health > 0)
				blit_bullet(bullet[i].texture[bullet[i].d], bullet[i], game, d, height, width);
			i++;
		}

		/* Reload */
		if (game.reload && n == 6) {
			n = 0;
			printf("...Reloading...\n");
		}

		/* Quit */
		if (game.quit == 1)
			break;

		/* Display player && wall */
		blit_player(player.texture[d], player, game, d, height, width);
		blit_walltb(ui.texture[0], game, height, width);
		blit_walllr(ui.texture[1], game, height, width);
		presentScene(game);
		SDL_Delay(16);
	}

    SDL_bye(game);
	return 0;
}