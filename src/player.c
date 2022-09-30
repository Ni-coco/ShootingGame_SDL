void move_player(Entity *player, App *game, int height, int width)
{
	if (game->up && game->left)
		player->dp = 4;
	if (game->up && game->right)
		player->dp = 5;
	if (game->down && game->left)
		player->dp = 6;
	if (game->down && game->right)
		player->dp = 7;
	if (game->up && player->py > (height * 0.05)) {
		if (game->left || game->right)
			player->py -= (width / 350);
		else
			player->py -= (width / 200);
	}
	if (game->down && player->py < (height - (height * 0.18))) {
		if (game->left || game->right)
			player->py += (width / 350);
		else
			player->py += (width / 200);
	}
	if (game->left && player->px > (width * 0.027))
		player->px -= (width / 200);
	if (game->right && player->px < (width - (width * 0.1)))
		player->px += (width / 200);
}