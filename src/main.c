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
	int d = 0, i = 0;
	Entity player;
	Entity bullet[6];
	Entity wall;
	App game;
	memset(&game, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	memset(&bullet, 0, sizeof(Entity));
	memset(&wall, 0, sizeof(Entity));

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

	player.x = (width / 2);
	player.y = (height / 2);
	get_texture(game, &player, bullet, &wall);

	for (;;)
	{
		SDL_GetWindowSize(game.window, &width, &height);
		prepareScene(game);
		doInput(&game, player, &d);
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
		i = 0;
		while (i < 6) {
			if (game.shoot && bullet[i].health == 0) {
			bullet[i].d = d;
			bullet[i].x = player.x;
			bullet[i].y = player.y;
			bullet[i].health = 1;
			}
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
		if (game.quit == 1)
			break;
		blit_player(player.texture[d], player, game, d, height, width);
		blit_walltb(wall.texture[0], game, height, width);
		blit_walllr(wall.texture[1], game, height, width);
		presentScene(game);
		SDL_Delay(16);
	}

    SDL_bye(game);
	return 0;
}