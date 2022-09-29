typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	int up;
	int down;
	int left;
	int right;
	int shoot;
	int reload;
	int quit;
} App;

typedef struct {
	int px;
	int py;
	int phealth;
	int bx[6];
	int by[6];
	int d[6];
	int bhealth[6];
	SDL_Texture *texture_player[8];
	SDL_Texture *texture_bullet[8];
} Entity;

typedef struct {
	int x;
	int y;
	SDL_Texture *texture[4];
} Stuff;