void move_enemies(Entity *enemies, int height, int width, int x)
{
    for (int i = 0; i < 5; i++) {
		if (enemies[i].px > width && x == 0) {
			enemies[i].destx = rand() % (1820 - 15 + 1) + 15;
			enemies[i].desty = rand() % (910 - 15 + 1) + 15;
		}
		else if (!(enemies[i].px < enemies[i].destx - 5 || enemies[i].px > enemies[i].destx + 5))
			enemies[i].destx = rand() % (1820 - 15 + 1) + 15;
		else if (!(enemies[i].py < enemies[i].desty - 5 || enemies[i].py > enemies[i].desty + 5))
			enemies[i].desty = rand() % (910 - 15 + 1) + 15;
		else {
			if (enemies[i].destx < enemies[i].px)
				enemies[i].px -= (width / 500);
			else if (enemies[i].destx > enemies[i].px)
				enemies[i].px += (width / 500);
			if (enemies[i].desty < enemies[i].py)
				enemies[i].py -= (width / 500);
			else if (enemies[i].desty > enemies[i].py)
				enemies[i].py += (width / 500);
		}
	}
}

void get_way(Entity *enemies, Entity player)
{
	for (int i = 0; i < 5; i++) {
		if (enemies[i].px > player.px) {
			if (enemies[i].py > player.py)
				enemies[i].dp = 4;
			else if (enemies[i].py < player.py)
				enemies[i].dp = 6;
		}
		else if (enemies[i].px < player.px) {
			if (enemies[i].py > player.py)
				enemies[i].dp = 5;
			else if (enemies[i].py < player.py)
				enemies[i].dp = 7;
		}
	}
}

void shoot_enemies(Entity *enemies, int *time)
{
	int i = rand() % 5;
	if (enemies[i].nb <= 5 && !time[1]) {
		enemies[i].db[enemies[i].nb] = enemies[i].dp;
		if (enemies[i].dp == 4) {
			enemies[i].bx[enemies[i].nb] = enemies[i].px;
			enemies[i].by[enemies[i].nb] = enemies[i].py;
		}
		else if (enemies[i].dp == 5) {
			enemies[i].bx[enemies[i].nb] = enemies[i].px + 120;
			enemies[i].by[enemies[i].nb] = enemies[i].py;
		}
		else if (enemies[i].dp == 6) {
			enemies[i].bx[enemies[i].nb] = enemies[i].px;
			enemies[i].by[enemies[i].nb] = enemies[i].py + 68;
		}
		else if (enemies[i].dp == 7) {
			enemies[i].bx[enemies[i].nb] = enemies[i].px + 68;
			enemies[i].by[enemies[i].nb] = enemies[i].py + 120;
		}
		enemies[i].bhealth[enemies[i].nb] = 1;
		enemies[i].nb += 1;
		time[1] = 50; // Cadence tir enemies.
	}
	if (time[1])
		time[1] -= 1;
}