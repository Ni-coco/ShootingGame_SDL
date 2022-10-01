void doKeyDown(SDL_KeyboardEvent *event, App *game, Entity *player)
{
	if (event->repeat == 0)
	{
		if (game->go == 1) {
			if (event->keysym.scancode == SDL_SCANCODE_UP) {
				game->up = 1;
				player->dp = 0;
			}
			if (event->keysym.scancode == SDL_SCANCODE_DOWN) {
				game->down = 1;
				player->dp = 1;
			}
			if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
				game->left = 1;
				player->dp = 2;
			}
			if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
				game->right = 1;
				player->dp = 3;
			}
			if (event->keysym.scancode == SDL_SCANCODE_SPACE)
				game->shoot = 1;
			if (event->keysym.scancode == SDL_SCANCODE_R)
				game->reload = 1;
		}
		if (event->keysym.scancode == SDL_SCANCODE_RETURN)
			game->go = 1;
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

void doInput(App *game, Entity *player)
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
				doKeyDown(&event.key, game, player);
				break;
			case SDL_KEYUP:
				doKeyUp(&event.key, game);
				break;
			default:
				break;
		}
	}
}