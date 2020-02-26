#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 800;

void move(bool* exit)
{

	if (SDLK_ESCAPE) {
		*(exit) = true;
		
	}
}

int main(int argc, char* args[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window

	SDL_Renderer* renderer = NULL;

	//Definir keys

	Uint8* Keys;

	//Rect properties
	SDL_Rect rect = { 500,350,32,32 };



	bool exit = false;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			
			while (exit == false)
			{

				//Get window surface
				renderer = SDL_CreateRenderer(window, -1, 0);

				//Render Color
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				//Clar Renderer
				SDL_RenderClear(renderer);

				//Render Geometry
				SDL_Rect rect = { 500,350,32,32 };
				SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
				SDL_RenderFillRect(renderer, &rect);

				//Update the surface
				SDL_RenderPresent(renderer);

				//Key
				move(&exit);
			}

			//Wait two seconds
			//SDL_Delay(2000);
		}
	}



	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
