#include "Game.h"
#include <math.h>

Game::Game() {}
Game::~Game() {}

bool Game::Init()
{
	//Initialize SDL with all subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	//Create our window: title, x, y, w, h, flags
	Window = SDL_CreateWindow("Spaceship: arrow keys + space", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (Window == NULL)
	{
		SDL_Log("Unable to create window: %s", SDL_GetError());
		return false;
	}
	//Create a 2D rendering context for a window: window, device index, flags
	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if (Renderer == NULL)
	{
		SDL_Log("Unable to create rendering context: %s", SDL_GetError());
		return false;
	}
	//Initialize keys array
	for (int i = 0; i < MAX_KEYS; ++i)
		keys[i] = KEY_IDLE;

	//Init variables
	Player.Init(20, WINDOW_HEIGHT >> 1, 104, 82, 5);
	idx_shot = 0;
	Scene.Init(0, 0, 768, 1024, 0);


	// load support for the JPG and PNG image formats
	int flags = IMG_INIT_PNG;
	IMG_Init(flags);
	Surface = IMG_Load("spaceship.png");
	Texture[0] = SDL_CreateTextureFromSurface(Renderer, Surface);
	Surface = IMG_Load("shot.png");
	Texture[1] = SDL_CreateTextureFromSurface(Renderer, Surface);
	Surface = IMG_Load("background.png");
	Texture[2] = SDL_CreateTextureFromSurface(Renderer, Surface);
	int bg_width;
	SDL_QueryTexture(Texture[2], NULL, NULL, &bg_width, NULL);
	Scene.Init(0, 0, bg_width, WINDOW_HEIGHT, 4);
	
	return true;
}
void Game::Release()
{
	//Clean up all SDL initialized subsystems
	SDL_Quit();
	SDL_DestroyTexture(Texture[0]);
	SDL_DestroyTexture(Texture[1]);
	SDL_DestroyTexture(Texture[2]);
}
bool Game::Input()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	return false;
	}

	SDL_PumpEvents();
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i])
			keys[i] = (keys[i] == KEY_IDLE) ? KEY_DOWN : KEY_REPEAT;
		else
			keys[i] = (keys[i] == KEY_REPEAT || keys[i] == KEY_DOWN) ? KEY_UP : KEY_IDLE;
	}

	return true;
}
bool Game::Update()
{
	//Read Input
	if (!Input())	return true;

	//Process Input
	int fx = 0, fy = 0;
	if (keys[SDL_SCANCODE_ESCAPE] == KEY_DOWN)	return true;
	if (keys[SDL_SCANCODE_UP] == KEY_REPEAT)	fy = -1;
	if (keys[SDL_SCANCODE_DOWN] == KEY_REPEAT)	fy = 1;
	if (keys[SDL_SCANCODE_LEFT] == KEY_REPEAT)	fx = -1;
	if (keys[SDL_SCANCODE_RIGHT] == KEY_REPEAT)	fx = 1;
	if (keys[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		int x, y, w, h;
		Player.GetRect(&x, &y, &w, &h);
		Shots[idx_shot].Init(x + 29, y + 3, 56, 20, 10);
		idx_shot++;
		idx_shot %= MAX_SHOTS;
		Shots[idx_shot].Init(x + 29, y + 59, 56, 20, 10);
		idx_shot++;
		idx_shot %= MAX_SHOTS;
	}

	//Logic
	Scene.Move(-1, 0);
	if (Scene.GetX() <= -Scene.GetWidth()) {
		Scene.SetX(0);
	}
	//Player update
	Player.Move(fx, fy);
	//Shots update
	for (int i = 0; i < MAX_SHOTS; ++i)
	{
		if (Shots[i].IsAlive())
		{
			Shots[i].Move(1, 0);
			if (Shots[i].GetX() > WINDOW_WIDTH)	Shots[i].ShutDown();
		}
	}

	return false;
}
void Game::Draw()
{
	SDL_Rect rc;
	//Clear rendering target
	SDL_RenderClear(Renderer);
	Scene.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, Texture[2], NULL, &rc);
	rc.x += rc.w;
	SDL_RenderCopy(Renderer, Texture[2], NULL, &rc);

	//Draw player
	
	Player.GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
	SDL_RenderCopy(Renderer, Texture[0], NULL, &rc);
	//SDL_SetRenderDrawColor(Renderer, 0, 192, 0, 255);
	//SDL_RenderFillRect(Renderer, &rc);

	//Draw shots
	SDL_SetRenderDrawColor(Renderer, 192, 0, 0, 255);
	for (int i = 0; i < MAX_SHOTS; ++i)
	{
		if (Shots[i].IsAlive())
		{
			SDL_Rect rc;
			Shots[i].GetRect(&rc.x, &rc.y, &rc.w, &rc.h);
			SDL_RenderCopy(Renderer, Texture[1], NULL, &rc);
		}
	}

	//Update screen
	SDL_RenderPresent(Renderer);

	SDL_Delay(10);	// 1000/10 = 100 fps max
}