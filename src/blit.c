void blit_walltb(SDL_Texture *texture, App game, int height, int width)
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

void blit_walllr(SDL_Texture *texture, App game, int height, int width)
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

void blit_bullet(SDL_Texture *texture, Entity bullet, App game, int d, int height, int width)
{
	SDL_Rect dest;

	dest.x = bullet.x;
	dest.y = bullet.y;
	if (bullet.d == 0 || bullet.d == 1) {
		dest.w = height * 0.005;
		dest.h = width * 0.008;
	}
	if (bullet.d == 2 || bullet.d == 3) {
		dest.w = width * 0.008;
		dest.h = height * 0.005;
	}
	if (bullet.d == 4 || bullet.d == 7) {
		dest.w = width * 0.007;
		dest.h = height * 0.0125;
	}
	if (bullet.d == 5 || bullet.d == 6) {
		dest.w = height * 0.0125;
		dest.h = width * 0.007;
	}
	SDL_QueryTexture(texture, NULL, NULL, NULL, NULL);
	SDL_RenderCopy(game.renderer, texture, NULL, &dest);
}