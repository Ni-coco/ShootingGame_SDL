#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	int up;
	int down;
	int left;
	int right;
	int quit;
} App;

typedef struct {
	int x;
	int y;
	SDL_Texture *texture[10];
} Entity;

void doKeyDown(SDL_KeyboardEvent *event, App *game, Entity player, int *d)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP) {
			game->up = 1;
			*d = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
			game->down = 1;
			*d = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
			game->left = 1;
			*d = 2;
		}
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
			game->right = 1;
			*d = 3;
		}
		if (event->keysym.scancode == SDL_SCANCODE_I)
		{
			printf("%d", game->up);
			printf("x = %d\n", player.x);
			printf("y = %d\n", player.y);

		}
	}
}

void doKeyUp(SDL_KeyboardEvent *event, App *game)
{
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_UP)
			game->up = 0;
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
			game->down = 0;
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
			game->left = 0;
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
			game->right = 0;
		if (event->keysym.scancode == SDL_SCANCODE_ESCAPE)
			game->quit = 1;
	}
}

void doInput(App *game, Entity player, int *d)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
				break;
			case SDL_KEYDOWN:
				doKeyDown(&event.key, game, player, d);
				break;
			case SDL_KEYUP:
				doKeyUp(&event.key, game);
				break;
			default:
				break;
		}
	}
}

void prepareScene(App game)
{
	SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
	SDL_RenderClear(game.renderer);
}

void presentScene(App game)
{
	SDL_RenderPresent(game.renderer);
}

void SDL_Exit(char *output) {
    SDL_Log("Erreur : %s > %s", output, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_bye(App game)
{
   SDL_DestroyRenderer(game.renderer);
   SDL_DestroyWindow(game.window);
   SDL_Quit(); 
}

SDL_Texture *loadTexture(char *filename, App game)
{
	SDL_Texture *texture = NULL;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(game.renderer, filename);

	return texture;
}

void blit_walltd(SDL_Texture *texture, Entity player, App game, int height, int width)
{
	SDL_Rect dest[2];
	dest[0].x = 0;
	dest[0].y = 0;
	dest[0].w = width;
	dest[0].h = width * 0.025;
	dest[1].x = 0;
	dest[1].y = (height - ((width * 0.025) - 1));
	dest[1].w = width;
	dest[1].h = width * 0.025;
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest[0]);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest[1]);
}

void blit_walllr(SDL_Texture *texture, Entity player, App game, int height, int width)
{
	SDL_Rect dest[2];
	dest[0].x = 0;
	dest[0].y = 0;
	dest[0].w = width * 0.025;
	dest[0].h = height;
	dest[1].x = (width - (width * 0.025) + 1);
	dest[1].y = 0;
	dest[1].w = width * 0.025;
	dest[1].h = height;
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest[0]);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest[1]);
}

void blit_player(SDL_Texture *texture, Entity player, App game, int d, int height, int width)
{
	SDL_Rect dest;

	dest.x = player.x;
	dest.y = player.y;
	/* Up and down */ /* topleft & downright */
	if (d == 0 || d == 1 || d == 4 || d == 7) {
		dest.w = height * 0.08;
		dest.h = width * 0.07;
	}
	/*left and right */ /* topright & downleft */
	if (d == 2 || d == 3 || d == 5 || d == 6) {
		dest.w = width * 0.07;
		dest.h = height * 0.08;
	}
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}

void get_texture(App game, Entity *player) {
	player->texture[0] = loadTexture("Sprite/player/top.png", game); //0 -> Top
	player->texture[1] = loadTexture("Sprite/player/down.png", game); //1 -> down
	player->texture[2] = loadTexture("Sprite/player/left.png", game); //2 -> left
	player->texture[3] = loadTexture("Sprite/player/right.png", game); //3 -> right
	player->texture[4] = loadTexture("Sprite/player/topleft.png", game); //4 -> topleft
	player->texture[5] = loadTexture("Sprite/player/topright.png", game); //5 -> topright
	player->texture[6] = loadTexture("Sprite/player/dleft.png", game); //6 -> downleft
	player->texture[7] = loadTexture("Sprite/player/dright.png", game); //7 -> downright
	player->texture[8] = loadTexture("Sprite/wall.png", game); //8 -> wall top and bottom
	player->texture[9] = loadTexture("Sprite/wall2.png", game); //8 -> wall left and right
}

int main(int argc, char *argv[])
{
	int width = 640;
	int height = 480;
	App game;
	Entity player;
	memset(&game, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	int d = 0;

	IMG_Init(IMG_INIT_PNG);
	int rendererFlags, windowFlags;
	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	game.window = SDL_CreateWindow("ShooterGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_RESIZABLE);

	if (!game.window)
	{
		printf("Failed to open %d x %d window: %s\n", width, height, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	game.renderer = SDL_CreateRenderer(game.window, -1, rendererFlags);

	if (!game.renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}
	player.x = (width / 2);
	player.y = (height / 2);
	get_texture(game, &player);
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
		if (game.up && player.y > (height * 0.036)) {
			if (game.left || game.right)
				player.y -= (width / 350);
			else
				player.y -= (width / 200);
		}
		if (game.down && player.y < (height - (height * 0.125))) {
			if (game.left || game.right)
				player.y += (width / 350);
			else
				player.y += (width / 200);
		}
		if (game.left && player.x > (width * 0.027))
			player.x -= (width / 200);
		if (game.right && player.x < (width - (width * 0.1)))
			player.x += (width / 200);
		if (game.quit == 1)
			break;
		blit_player(player.texture[d], player, game, d, height, width);
		blit_walltd(player.texture[8], player, game, height, width);
		blit_walllr(player.texture[9], player, game, height, width);

		presentScene(game);
		SDL_Delay(16);
	}

    SDL_bye(game);
	return 0;
}