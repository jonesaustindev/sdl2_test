#include <SDL2/SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SQUARE_SIZE = 50;
const SDL_Color COLOR1 = {35, 56, 80, 255};
const SDL_Color COLOR2 = {51, 81, 115, 255};

void drawCheckeredBackground(SDL_Renderer *renderer)
{
  for (int y = 0; y < SCREEN_HEIGHT; y += SQUARE_SIZE)
  {
    for (int x = 0; x < SCREEN_WIDTH; x += SQUARE_SIZE)
    {
      SDL_Color color = ((x / SQUARE_SIZE) % 2 == (y / SQUARE_SIZE) % 2) ? COLOR1 : COLOR2;
      SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
      SDL_Rect rect = {x, y, SQUARE_SIZE, SQUARE_SIZE};
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

int main(int argc, char *argv[])
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("SDL Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  if (window == nullptr)
  {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr)
  {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  bool quit = false;
  SDL_Event e;
  while (!quit)
  {
    while (SDL_PollEvent(&e) != 0)
    {
      if (e.type == SDL_QUIT)
      {
        quit = true;
      }
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);

    drawCheckeredBackground(renderer);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
