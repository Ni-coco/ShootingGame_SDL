void prepareScene(App game)
{
	SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
	SDL_RenderClear(game.renderer);
}

void presentScene(App game)
{
	SDL_RenderPresent(game.renderer);
}

int check_life(Entity player, Entity *enemies)
{
    int k = 0;
    for (int i = 0; i < 5; i++)
        if (enemies[i].phealth != 1)
            k += 1;
    if (k == 5)
        return (1);
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