SDL_Texture *loadTexture(char *filename, App game)
{
	SDL_Texture *texture = NULL;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(game.renderer, filename);

	return texture;
}

void get_texture(App game, Entity *player, Entity *bullet, Entity *ui) {
	player->texture[0] = loadTexture("Sprite/Player/Top.png", game); //0 -> Top
	player->texture[1] = loadTexture("Sprite/Player/Down.png", game); //1 -> down
	player->texture[2] = loadTexture("Sprite/Player/Left.png", game); //2 -> left
	player->texture[3] = loadTexture("Sprite/Player/Right.png", game); //3 -> right
	player->texture[4] = loadTexture("Sprite/Player/TopLeft.png", game); //4 -> topleft
	player->texture[5] = loadTexture("Sprite/Player/TopRight.png", game); //5 -> topright
	player->texture[6] = loadTexture("Sprite/Player/DownLeft.png", game); //6 -> downleft
	player->texture[7] = loadTexture("Sprite/Player/DownRight.png", game); //7 -> downright
	for (int i = 0; i < 6; i++) {
		bullet[i].texture[0] = loadTexture("Sprite/bullet/top.png", game); //Top
		bullet[i].texture[1] = loadTexture("Sprite/bullet/down.png", game); //down
		bullet[i].texture[2] = loadTexture("Sprite/bullet/left.png", game); //left
		bullet[i].texture[3] = loadTexture("Sprite/bullet/right.png", game); //right
		bullet[i].texture[4] = loadTexture("Sprite/bullet/Topleft.png", game); //topleft
		bullet[i].texture[5] = loadTexture("Sprite/bullet/Topright.png", game); //topright
		bullet[i].texture[6] = loadTexture("Sprite/bullet/Downleft.png", game); //downleft
		bullet[i].texture[7] = loadTexture("Sprite/bullet/Downright.png", game); //downright
	}
	ui->texture[0] = loadTexture("Sprite/UI/wall.png", game); //0 -> wall top and bottom
	ui->texture[1] = loadTexture("Sprite/UI/wall2.png", game); //1 -> wall left and right
	ui->texture[2] = loadTexture("Sprite/UI/life.png", game); //2 -> life
	ui->texture[3] = loadTexture("Sprite/UI/ammo.png", game); //3 -> ammo
}