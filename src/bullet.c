void shoot (Entity *player, App game, int d, int *n, int *time)
{
    if (game.shoot && *n <= 5 && !*time) {
		player->d[*n] = d;
		if (d == 0) {
			player->bx[*n] = player->px + 48;
			player->by[*n] = player->py;
		}
		else if (d == 1) {
			player->bx[*n] = player->px + 27;
			player->by[*n] = player->py + 115;
		}
		else if (d == 2) {
			player->bx[*n] = player->px;
			player->by[*n] = player->py + 25;
		}
		else if (d == 3) {
			player->bx[*n] = player->px + 115;
			player->by[*n] = player->py + 48;
		}
		else if (d == 4) {
			player->bx[*n] = player->px;
			player->by[*n] = player->py;
		}
		else if (d == 5) {
			player->bx[*n] = player->px + 120;
			player->by[*n] = player->py;
		}
		else if (d == 6) {
			player->bx[*n] = player->px;
			player->by[*n] = player->py + 68;
		}
		else if (d == 7) {
			player->bx[*n] = player->px + 68;
			player->by[*n] = player->py + 120;
		}
		player->bhealth[*n] = 1;
		*time = 15;
		*n += 1;
		if (*n == 6)
			printf("-- Press 'R' to reload --\n");
	}
	if (*time)
		*time -= 1;
}

void bulletillw (Entity *player, App game, int height, int width, int i)
{
	i = 0;
	while (i < 6) {
		if (player->d[i] == 0)
			player->by[i] += -16;
		if (player->d[i] == 1)
			player->by[i] += 16;
		if (player->d[i] == 2)
			player->bx[i] += -16;
		if (player->d[i] == 3)
			player->bx[i] += 16;
		if (player->d[i] == 4) {
			player->bx[i] += -10;
			player->by[i] += -10;
		}
		if (player->d[i] == 5) {
			player->bx[i] += 10;
			player->by[i] += -10;
		}
		if (player->d[i] == 6) {
			player->bx[i] += -10;
			player->by[i] += 10;
		}
		if (player->d[i] == 7) {
			player->bx[i] += 10;
			player->by[i] += 10;
		}
		if (player->bx[i] > width || player->bx[i] < 0 || player->by[i] > height || player->by[i] < 0)
			player->bhealth[i] = 0;
		if (player->bhealth[i] > 0)
			blit_bullet(player->texture_bullet[player->d[i]], *player, game, height, width, i);
		i++;
	}
}

void reload (App game, int *n) {
	if (game.reload && *n == 6) {
		*n = 0;
		printf("...Reloading...\n");
	}
}