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
		if (game.up && player.py > (height * 0.05)) {
			if (game.left || game.right)
				player.py -= (width / 350);
			else
				player.py -= (width / 200);
		}
		if (game.down && player.py < (height - (height * 0.18))) {
			if (game.left || game.right)
				player.py += (width / 350);
			else
				player.py += (width / 200);
		}
		if (game.left && player.px > (width * 0.027))
			player.px -= (width / 200);
		if (game.right && player.px < (width - (width * 0.1)))
			player.px += (width / 200);

		/* Shooting */
		if (game.shoot && n <= 5 && !time) {
			player.d[n] = d;
			if (d == 0) {
				player.bx[n] = player.px + 48;
				player.by[n] = player.py;
			}
			else if (d == 1) {
				player.bx[n] = player.px + 27;
				player.by[n] = player.py + 115;
			}
			else if (d == 2) {
				player.bx[n] = player.px;
				player.by[n] = player.py + 25;
			}
			else if (d == 3) {
				player.bx[n] = player.px + 115;
				player.by[n] = player.py + 48;
			}
			else if (d == 4) {
				player.bx[n] = player.px;
				player.by[n] = player.py;
			}
			else if (d == 5) {
				player.bx[n] = player.px + 120;
				player.by[n] = player.py;
			}
			else if (d == 6) {
				player.bx[n] = player.px;
				player.by[n] = player.py + 68;
			}
			else if (d == 7) {
				player.bx[n] = player.px + 68;
				player.by[n] = player.py + 120;
			}
			player.bhealth[n] = 1;
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
			if (player.d[i] == 0)
				player.by[i] += -16;
			if (player.d[i] == 1)
				player.by[i] += 16;
			if (player.d[i] == 2)
				player.bx[i] += -16;
			if (player.d[i] == 3)
				player.bx[i] += 16;
			if (player.d[i] == 4) {
				player.bx[i] += -10;
				player.by[i] += -10;
			}
			if (player.d[i] == 5) {
				player.bx[i] += 10;
				player.by[i] += -10;
			}
			if (player.d[i] == 6) {
				player.bx[i] += -10;
				player.by[i] += 10;
			}
			if (player.d[i] == 7) {
				player.bx[i] += 10;
				player.by[i] += 10;
			}
			if (player.bx[i] > width || player.bx[i] < 0 || player.by[i] > height || player.by[i] < 0)
				player.bhealth[i] = 0;
			if (player.bhealth[i] > 0)
				blit_bullet(player.texture_bullet[player.d[i]], player, game, height, width, i);
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
		blit_player(player.texture_player[d], player, game, height, width, d);
		x = 100;
		for (int i = 0; i < life; i++)
			blit_life(ui.texture[2], game, height, width, &x);
		x = 1550;
		for (int i = 5; i >= n; i--)
			blit_ammo(ui.texture[3], game, height, width, &x);
		blit_walltb(ui.texture[0], game, height, width);
		blit_walllr(ui.texture[1], game, height, width);
		presentScene(game);
		SDL_Delay(16);
	}
    SDL_bye(game);
	return 0;
}