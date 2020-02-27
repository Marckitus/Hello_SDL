#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;



int main(int argc, char* args[])
{
	bool exit = false;
	int x = 500, y = 400, xb = 2000, yb = 2000;

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window

	SDL_Renderer* renderer = NULL;

	//Definir keys

	Uint32* key;

	//Bullet properties
	SDL_Rect Bullet = { 600, 500, 10, 5 };

	//Rect properties
	SDL_Rect rect = { 500,350,32,32 };


	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{

		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Render Geometry
			SDL_Rect rect = { x,y,32,32 };
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			SDL_RenderFillRect(renderer, &rect);

			//Get window surface
			renderer = SDL_CreateRenderer(window, -1, 0);

			//Render Color
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			//Clar Renderer
			SDL_RenderClear(renderer);
			//Create window
			while (exit == false)
			{

				

				//Render Geometry
				SDL_Rect rect = { x, y,32,32 };

			
				//Update the surface
				SDL_RenderPresent(renderer);

				//Key
				SDL_Event event;

				while (SDL_PollEvent(&event))
				{
					if (event.type == SDL_KEYDOWN)
					{
						if (event.key.keysym.sym == SDLK_ESCAPE)
						{
							// ESC has been pressed
							exit = true;
						}
						if (event.key.keysym.sym == SDLK_x)
						{
							// ESC has been pressed
							exit = true;
						}
						if (event.key.keysym.sym == SDLK_s)
						{
							y = y + 10;

						}
						if (event.key.keysym.sym == SDLK_a)
						{

							x = x - 10;
						}
						if (event.key.keysym.sym == SDLK_w)
						{

							y = y - 10;
						}
						if (event.key.keysym.sym == SDLK_d)
						{
							x = x + 10;

						}
						if (event.key.keysym.sym == SDLK_SPACE) {
							Bullet.x = x + 25;
							Bullet.y = y + 25;
						
						}
						

					}
	
				}
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);
				//Draw the bullet in loop
				SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
				SDL_RenderFillRect(renderer, &Bullet);
				Bullet.x += 1;
			}

			//Wait two seconds
			//SDL_Delay(2000);
		}
	}



	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
