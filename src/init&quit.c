void prepareScene(App game)
{
	SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
	SDL_RenderClear(game.renderer);
}

void presentScene(App game)
{
	SDL_RenderPresent(game.renderer);
}

void reset(Entity *player, Entity *enemies, int width, int height)
{
    /* Position player */
	player->dp = 0;
	player->nb = 0;
	player->destx = 0;
	player->phealth = 3;
	player->radius = 50;
	player->px = (width - player->radius) / 2;
	player->py = (height - player->radius) / 2;

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
}

int check_life(Entity player, Entity *enemies)
{
    if (player.phealth == 0)
        return (1);
    return (0);
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