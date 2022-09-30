void shoot (Entity *player, App game, int *time)
{
    if (game.shoot && player->nb <= 5 && !time[0]) {
		player->db[player->nb] = player->dp;
		if (player->dp == 0) {
			player->bx[player->nb] = player->px + 48;
			player->by[player->nb] = player->py;
		}
		else if (player->dp == 1) {
			player->bx[player->nb] = player->px + 27;
			player->by[player->nb] = player->py + 115;
		}
		else if (player->dp == 2) {
			player->bx[player->nb] = player->px;
			player->by[player->nb] = player->py + 25;
		}
		else if (player->dp == 3) {
			player->bx[player->nb] = player->px + 115;
			player->by[player->nb] = player->py + 48;
		}
		else if (player->dp == 4) {
			player->bx[player->nb] = player->px;
			player->by[player->nb] = player->py;
		}
		else if (player->dp == 5) {
			player->bx[player->nb] = player->px + 120;
			player->by[player->nb] = player->py;
		}
		else if (player->dp == 6) {
			player->bx[player->nb] = player->px;
			player->by[player->nb] = player->py + 68;
		}
		else if (player->dp == 7) {
			player->bx[player->nb] = player->px + 68;
			player->by[player->nb] = player->py + 120;
		}
		player->bhealth[player->nb] = 1;
		player->nb += 1;
		time[0] = 15;
		if (player->nb == 6)
			printf("-- Press 'R' to reload --\n");
	}
	if (time[0])
		time[0] -= 1;
}

void bullet (Entity *player, App game, int height, int width)
{
	for (int i = 0; i <= 5; i++) {
		if (!player->destx) {
			if (player->db[i] == 0)
				player->by[i] += -16;
			if (player->db[i] == 1)
				player->by[i] += 16;
			if (player->db[i] == 2)
				player->bx[i] += -16;
			if (player->db[i] == 3)
				player->bx[i] += 16;
		}
		if (player->db[i] == 4) {
			player->bx[i] += -10;
			player->by[i] += -10;
		}
		if (player->db[i] == 5) {
			player->bx[i] += 10;
			player->by[i] += -10;
		}
		if (player->db[i] == 6) {
			player->bx[i] += -10;
			player->by[i] += 10;
		}
		if (player->db[i] == 7) {
			player->bx[i] += 10;
			player->by[i] += 10;
		}
		if (player->bx[i] > width || player->bx[i] < 0 || player->by[i] > height || player->by[i] < 0)
			player->bhealth[i] = 0;
		if (player->bhealth[i] == 1)
			blit_bullet(player->texture_bullet[player->db[i]], *player, game, height, width, i);
	}
}

void reload (App game, Entity *player) {
	if (player->destx != 0 && player->nb == 6)
		player->nb = 0;
	if (game.reload && player->nb == 6) {
		player->nb = 0;
		printf("...Reloading...\n");
	}
}

int get_distance (int x1, int y1, int x2, int y2)
{
	int x = x1 - x2;
	int y = y1 - y2;
	return (sqrt(x * x + y * y));
}

void check_hit (Entity *from, Entity *to)
{
	for (int i = 0; i < 6; i++) {
		if (from->bhealth[i] == 1) {
			int distance = get_distance(to->px, to->py, from->bx[i], from->by[i]);
			if (distance < to->radius) {
				from->bhealth[i] = 0;
				to->phealth -= 1;
			}
		}
	}
}