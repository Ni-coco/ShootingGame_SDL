typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	int up;
	int down;
	int left;
	int right;
	int shoot;
	int quit;
} App;

typedef struct {
	int x;
	int y;
	int d;
	int health;
	SDL_Texture *texture[8];
} Entity;