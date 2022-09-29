SDL_Texture *loadTexture(char *filename, App game)
{
	SDL_Texture *texture = NULL;
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
	texture = IMG_LoadTexture(game.renderer, filename);
	return texture;
}

void get_texture(App game, Entity *player, Entity *enemies, Stuff *ui) {
	/* Player */
	player->texture_player[0] = loadTexture("Sprite/Player/Top.png", game); //0 -> Top
	player->texture_player[1] = loadTexture("Sprite/Player/Down.png", game); //1 -> down
	player->texture_player[2] = loadTexture("Sprite/Player/Left.png", game); //2 -> left
	player->texture_player[3] = loadTexture("Sprite/Player/Right.png", game); //3 -> right
	player->texture_player[4] = loadTexture("Sprite/Player/TopLeft.png", game); //4 -> topleft
	player->texture_player[5] = loadTexture("Sprite/Player/TopRight.png", game); //5 -> topright
	player->texture_player[6] = loadTexture("Sprite/Player/DownLeft.png", game); //6 -> downleft
	player->texture_player[7] = loadTexture("Sprite/Player/DownRight.png", game); //7 -> downright
	player->texture_bullet[0] = loadTexture("Sprite/bullet/top.png", game); //Top
	player->texture_bullet[1] = loadTexture("Sprite/bullet/down.png", game); //down
	player->texture_bullet[2] = loadTexture("Sprite/bullet/left.png", game); //left
	player->texture_bullet[3] = loadTexture("Sprite/bullet/right.png", game); //right
	player->texture_bullet[4] = loadTexture("Sprite/bullet/Topleft.png", game); //topleft
	player->texture_bullet[5] = loadTexture("Sprite/bullet/Topright.png", game); //topright
	player->texture_bullet[6] = loadTexture("Sprite/bullet/Downleft.png", game); //downleft
	player->texture_bullet[7] = loadTexture("Sprite/bullet/Downright.png", game); //downright

	/* Enemies */
	enemies->texture_player[0] = loadTexture("Sprite/enemies/Top.png", game); //0 -> Top
	enemies->texture_player[1] = loadTexture("Sprite/enemies/Down.png", game); //1 -> down
	enemies->texture_player[2] = loadTexture("Sprite/enemies/Left.png", game); //2 -> left
	enemies->texture_player[3] = loadTexture("Sprite/enemies/Right.png", game); //3 -> right
	enemies->texture_player[4] = loadTexture("Sprite/enemies/TopLeft.png", game); //4 -> topleft
	enemies->texture_player[5] = loadTexture("Sprite/enemies/TopRight.png", game); //5 -> topright
	enemies->texture_player[6] = loadTexture("Sprite/enemies/DownLeft.png", game); //6 -> downleft
	enemies->texture_player[7] = loadTexture("Sprite/enemies/DownRight.png", game); //7 -> downright
	enemies->texture_bullet[0] = loadTexture("Sprite/bullet/top.png", game); //Top
	enemies->texture_bullet[1] = loadTexture("Sprite/bullet/down.png", game); //down
	enemies->texture_bullet[2] = loadTexture("Sprite/bullet/left.png", game); //left
	enemies->texture_bullet[3] = loadTexture("Sprite/bullet/right.png", game); //right
	enemies->texture_bullet[4] = loadTexture("Sprite/bullet/Topleft.png", game); //topleft
	enemies->texture_bullet[5] = loadTexture("Sprite/bullet/Topright.png", game); //topright
	enemies->texture_bullet[6] = loadTexture("Sprite/bullet/Downleft.png", game); //downleft
	enemies->texture_bullet[7] = loadTexture("Sprite/bullet/Downright.png", game); //downright

	/* UI */
	ui->texture[0] = loadTexture("Sprite/UI/wall.png", game); //0 -> wall top and bottom
	ui->texture[1] = loadTexture("Sprite/UI/wall2.png", game); //1 -> wall left and right
	ui->texture[2] = loadTexture("Sprite/UI/life.png", game); //2 -> life
	ui->texture[3] = loadTexture("Sprite/UI/ammo.png", game); //3 -> ammo
}