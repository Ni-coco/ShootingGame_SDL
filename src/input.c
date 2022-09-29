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
		if (event->keysym.scancode == SDL_SCANCODE_R)
			game->reload = 1;
		if (event->keysym.scancode == SDL_SCANCODE_I)
		{
			printf("x = %d\n", player.px);
			printf("y = %d\n", player.py);
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
		if (event->keysym.scancode == SDL_SCANCODE_R)
			game->reload = 0;
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