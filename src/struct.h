typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	int up;
	int down;
	int left;
	int right;
	int shoot;
	int reload;
	int pause;
	int play;
	int quit;
} App;

typedef struct {
	int px;
	int py;
	int destx;
	int desty;
	int dp;
	int phealth;
	int radius;
	int bx[6];
	int by[6];
	int nb;
	int db[6];
	int bhealth[6];
	SDL_Texture *texture_player[8];
	SDL_Texture *texture_bullet[8];
} Entity;

typedef struct {
	int x;
	int y;
	SDL_Texture *texture[9];
} Stuff;