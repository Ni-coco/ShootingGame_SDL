void blit_wall(SDL_Texture *texture, App game, int height, int width, int i)
{
	SDL_Rect dest[2];
	dest[0].x = 0;
	dest[0].y = 0;
	if (i == 0) {
		dest[0].w = width;
		dest[0].h = width * 0.025;
		dest[1].x = 0;
		dest[1].y = (height - ((width * 0.025) - 1));
		dest[1].w = width;
		dest[1].h = width * 0.025;
	}
	else if (i == 1) {
		dest[0].w = width * 0.025;
		dest[0].h = height;
		dest[1].x = (width - (width * 0.025) + 1);
		dest[1].y = 0;
		dest[1].w = width * 0.025;
		dest[1].h = height;
	}
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest[0]);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest[1]);
}

void blit_player(SDL_Texture *texture, Entity player, App game, int height, int width)
{
	SDL_Rect dest;
	dest.x = player.px;
	dest.y = player.py;
	/* Up and down */ /* topleft & downright */
	if (player.dp == 0 || player.dp == 1 || player.dp == 4 || player.dp == 7) {
		dest.w = height * 0.08;
		dest.h = width * 0.07;
	}
	/*left and right */ /* topright & downleft */
	if (player.dp == 2 || player.dp == 3 || player.dp == 5 || player.dp == 6) {
		dest.w = width * 0.07;
		dest.h = height * 0.08;
	}
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}

void blit_bullet(SDL_Texture *texture, Entity player, App game, int height, int width, int i)
{
	SDL_Rect dest;

	dest.x = player.bx[i];
	dest.y = player.by[i];
	if (player.db[i] == 0 || player.db[i] == 1) {
		dest.w = height * 0.005;
		dest.h = width * 0.008;
	}
	if (player.db[i] == 2 || player.db[i] == 3) {
		dest.w = width * 0.008;
		dest.h = height * 0.005;
	}
	if (player.db[i] == 4 || player.db[i] == 7) {
		dest.w = width * 0.007;
		dest.h = height * 0.0125;
	}
	if (player.db[i] == 5 || player.db[i] == 6) {
		dest.w = height * 0.0125;
		dest.h = width * 0.007;
	}
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}

void blit_life (SDL_Texture *texture, App game, int height, int width, int *x) {
	SDL_Rect dest;
	dest.x = *x;
	dest.y = 75;
	dest.w = width * 0.02;
	dest.h = height * 0.04;
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
	*x += 65;
}

void blit_ammo (SDL_Texture *texture, App game, int height, int width, int *x) {
	SDL_Rect dest;
	dest.x = *x;
	dest.y = 75;
	dest.w = width * 0.007;
	dest.h = height * 0.04;
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
	*x += 50;
}