//===============================================================================
//-------------------------------------------------------------------------------
#include<SDL/SDL.h>
#include<iostream>
#include<chrono>
#include"Tree.h"
//-------------------------------------------------------------------------------
//===============================================================================

//-------------------------------------------------------------------------------
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define AVG_FRAME 50
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
SDL_Window * gWindow = nullptr;
SDL_Renderer * gRenderer = nullptr;
unsigned int gFrameCounter;
float gCumulativeDiff;
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
bool init()
{
	//create gWindow and surfaces
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not be initialized error : \" %s \"", SDL_GetError());
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("SDL gWindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == nullptr)
		{
			printf("SDL gWindow could not be created error : \" %s \"", SDL_GetError());
			return false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == nullptr)
			{
				printf("Could not create the gRenderer error : \" %s \"", SDL_GetError());
				return false;
			}

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF,0xFF);
		}
	}
	//-------------------------------------------------------------------------------

	return true;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
void destroy()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	SDL_Quit();
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
int main(int /*argc*/, char */*argv*/[])
{
	Tree *tree = new Tree(0);
	for (int i = 0; i < 10; ++i)
	{
		tree->add(i + 1);
	}

	tree->traverseInOrder(0);
	std::cout << "size : " << pow(2,sizeof(short)*8);
	getchar();

	if (!init())
	{
		std::cout << "Could not initialize SDL";
		return 0;
	}



	//main loop
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		clock_t start = clock();

		gFrameCounter++;

		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);

		SDL_SetRenderDrawColor(gRenderer, 0xF0, 0x00, 0xFF, 0xFF);
		tree->draw(gRenderer);

		SDL_RenderPresent(gRenderer);
		
		//Calculate frame rate
		clock_t end = clock();
		clock_t diff = end - start;

		gCumulativeDiff += diff;

		if (gFrameCounter == AVG_FRAME)
		{
			gFrameCounter = 0;
			system("CLS");
			
			std::cout << "FPS : \"" << CLOCKS_PER_SEC / (gCumulativeDiff / AVG_FRAME) << "\"";
			gCumulativeDiff = 0.0f;
		}
		//-------------------------------------------------------------------------------

	}
	//-------------------------------------------------------------------------------

	//cleanup
	destroy();
	delete tree;
	return 0;
	//-------------------
}
//-------------------------------------------------------------------------------
