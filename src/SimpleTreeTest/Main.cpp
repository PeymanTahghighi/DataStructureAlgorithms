//===============================================================================
//===============================================================================
#include<SDL/SDL.h>
#include<SDL_TTF\SDL_ttf.h>
#include<iostream>
#include<chrono>
#include"Tree/Tree.h"
//===============================================================================
//===============================================================================

//-------------------------------------------------------------------------------
#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 600
#define AVG_FRAME 50
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
SDL_Window * gWindow = nullptr;
SDL_Renderer * gRenderer = nullptr;
TTF_Font* gFont = nullptr;
uint32_t gFrameCounter;
float gCumulativeDiff;
bool gIsDragging = false;
int mouseXOffset = 0;
int lastMousePositionX = 0;
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
bool init();
void destroy();
void handleMouseDrag();
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
int main(int /*argc*/, char * /*argv*/[])
{
	//enable memory leak checks.
#if defined(_DEBUG) | (DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	//------------------------------------------

	srand((unsigned int)time(nullptr));
	Tree *tree = new Tree((float)rand());

	//generate random tree.
	for (int i = 0; i < 14; ++i)
	{
		tree->add((float)rand());
	}
	
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
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				gIsDragging = true;
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{
				gIsDragging = false;
			}
		}

		//handle moue dragging.
		if (gIsDragging)
			handleMouseDrag();
		else
		{
			int x, y;
			SDL_GetMouseState(&x, &y);
			lastMousePositionX = x;
		}
		//-------------------------------

		SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
		SDL_RenderClear(gRenderer);

		SDL_SetRenderDrawColor(gRenderer, 0xF0, 0x00, 0xFF, 0xFF);
		tree->draw(gRenderer, gFont);


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
	//--------------------------

	//dump memory leaks
	_CrtDumpMemoryLeaks();

	return 0;
}
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
		gWindow = SDL_CreateWindow("Simple Tree Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
	//-------------------------------------------------------------------------------

	//Create font rendering system
	TTF_Init();
	gFont = TTF_OpenFont("tahoma.ttf", 9);
	TTF_SetFontStyle(gFont, TTF_STYLE_BOLD);
	//-------------------------------------------------------------------------------

	return true;
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
void destroy()
{
	SDL_DestroyWindow(gWindow);
	SDL_DestroyRenderer(gRenderer);
	TTF_Quit();
	SDL_Quit();
}
//-------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
void handleMouseDrag()
{
	int x, y;
	SDL_GetMouseState(&x, &y);

	mouseXOffset += x - lastMousePositionX;
	lastMousePositionX = x;
}
//-------------------------------------------------------------------------------