void init_stage(App game, int width, int height)
{
	int time[2] = {0, 25}, x = 0;
	Entity player;
	Entity enemies[5];
	Stuff ui;
	memset(&game, 0, sizeof(App));
	memset(&player, 0, sizeof(Entity));
	memset(&enemies, 0, sizeof(Entity));
	memset(&ui, 0, sizeof(Stuff));
	

    	/* Position player */
	player.nb = 0;
	player.destx = 0;
	player.phealth = 3;
	player.radius = 50;
	player.px = (width / 2);
	player.py = (height / 2);

	/* Position enemies & life */
	for (int i = 0; i < 5; i++) {
		enemies[i].nb = 0;
		enemies[i].phealth = 1;
		enemies[i].radius = 50;
		enemies[i].px = 1940;
		enemies[i].py = rand() % 1017;
		for (int j = 0; j < 6; j++) {
			enemies[i].bx[j] = 9999;
			enemies[i].by[j] = 9999;
		}
	}
    	/* Load texture */
	get_texture(game, &player, enemies, &ui);

    for (;;)
	{
		SDL_GetWindowSize(game.window, &width, &height);
		prepareScene(game);

		/* Input */
		doInput(&game, &player);

		/* Player */
			/* Direction && limit map */
		move_player(&player, &game, height, width);
			/* Shooting */
		shoot(&player, game, time);
			/* Bullet after shooting */
		bullet(&player, game, height, width);
			/* Reload */
		reload(game, &player);
			/* Check_Hit */
		for (int i = 0; i < 5; i++)
			check_hit(&player, &enemies[i]);

		/* Enenmies */
			/* Direction && limit map */
		move_enemies(enemies, height, width, x);
			/* Aim to player */
		get_way(enemies, player);
			/* Shooting */
		shoot_enemies(enemies, time);
			/* Bullet after shooting */
		for (int i = 0; i < 5; i++)
			if (enemies[i].phealth == 1)
				bullet(&enemies[i], game, height, width);
			/* Reload */
		for (int i = 0; i < 5; i++)
			if (enemies[i].phealth == 1)
				reload(game, &enemies[i]);
		/* Check_Hit */
		for (int i = 0; i < 5; i++)
			if (enemies[i].phealth == 1)
				check_hit(&enemies[i], &player);

		/* Quit */
		if (game.quit == 1 || check_life(player, enemies))
			break;		

		/* Display */
		blit_player(player.texture_player[player.dp], player, game, height, width);
		for (int i = 0; i < 5; i++)
			if (enemies[i].phealth == 1)
				blit_player(enemies[i].texture_player[enemies[i].dp], enemies[i], game, height, width);
		for (int i = 0; i < 2; i++)
			blit_wall(ui.texture[i], game, height, width, i);
		x = 100;
		for (int i = 0; i < player.phealth; i++)
			blit_life(ui.texture[2], game, height, width, &x);
		x = 1550;
		for (int i = 5; i >= player.nb; i--)
			blit_ammo(ui.texture[3], game, height, width, &x);

		presentScene(game);
		SDL_Delay(16);
	}
}