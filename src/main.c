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
	int shoot;
	int quit;
} App;

typedef struct {
	int x;
	int y;
	SDL_Texture *texture_skin[8];
	SDL_Texture *texture_bullet[8];
	SDL_Texture *texture_wall[2];
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
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
			game->shoot = 1;
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
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
			game->shoot = 0;
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

void blit_walltb(SDL_Texture *texture, Entity player, App game, int height, int width)
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

void blit_bullet(SDL_Texture *texture, Entity player, App game, int d, int height, int width)
{
	SDL_Rect dest;

	dest.x = player.x + 47;
	dest.y = player.y - 25;
	if (d == 0 || d == 1) {
		dest.w = height * 0.005;
		dest.h = width * 0.008;
	}
	if (d == 2 || d == 3) {
		dest.w = width * 0.008;
		dest.h = height * 0.005;
	}
	if (d == 4 || d == 7) {
		dest.w = width * 0.007;
		dest.h = height * 0.0125;
	}
	if (d == 5 || d == 6) {
		dest.w = height * 0.0125;
		dest.h = width * 0.007;
	}
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}

void get_texture(App game, Entity *player) {
	player->texture_skin[0] = loadTexture("Sprite/Player/Top.png", game); //0 -> Top
	player->texture_skin[1] = loadTexture("Sprite/Player/Down.png", game); //1 -> down
	player->texture_skin[2] = loadTexture("Sprite/Player/Left.png", game); //2 -> left
	player->texture_skin[3] = loadTexture("Sprite/Player/Right.png", game); //3 -> right
	player->texture_skin[4] = loadTexture("Sprite/Player/TopLeft.png", game); //4 -> topleft
	player->texture_skin[5] = loadTexture("Sprite/Player/TopRight.png", game); //5 -> topright
	player->texture_skin[6] = loadTexture("Sprite/Player/DownLeft.png", game); //6 -> downleft
	player->texture_skin[7] = loadTexture("Sprite/Player/DownRight.png", game); //7 -> downright
	player->texture_bullet[0] = loadTexture("Sprite/bullet/top.png", game); //bullet
	player->texture_bullet[1] = loadTexture("Sprite/bullet/down.png", game); //bullet
	player->texture_bullet[2] = loadTexture("Sprite/bullet/left.png", game); //bullet
	player->texture_bullet[3] = loadTexture("Sprite/bullet/right.png", game); //bullet
	player->texture_bullet[4] = loadTexture("Sprite/bullet/Topleft.png", game); //bullet
	player->texture_bullet[5] = loadTexture("Sprite/bullet/Topright.png", game); //bullet
	player->texture_bullet[6] = loadTexture("Sprite/bullet/Downleft.png", game); //bullet
	player->texture_bullet[7] = loadTexture("Sprite/bullet/Downright.png", game); //bullet
	player->texture_wall[0] = loadTexture("Sprite/wall.png", game); //8 -> wall top and bottom
	player->texture_wall[1] = loadTexture("Sprite/wall2.png", game); //9 -> wall left and right
}

int main(int argc, char *argv[])
{
	int width = 1920;
	int height = 1017;
	int d = 0;
	Entity player;
	App game;
	memset(&game, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));

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
		if (game.shoot)
			blit_bullet(player.texture_bullet[d], player, game, d, height, width);
		if (game.quit == 1)
			break;
		blit_player(player.texture_skin[d], player, game, d, height, width);
		blit_walltb(player.texture_wall[0], player, game, height, width);
		blit_walllr(player.texture_wall[1], player, game, height, width);
		presentScene(game);
		SDL_Delay(16);
	}

    SDL_bye(game);
	return 0;
}