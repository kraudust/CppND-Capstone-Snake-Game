#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height),
      players_menu_()
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  TTF_Init();

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // TODO: Customize -------------------------------------------------------
  auto font = std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>
          (TTF_OpenFont("../roboto/Roboto-Bold.ttf", 25), TTF_CloseFont);

  if(font == nullptr){
    std::cerr << "Font was not found.\n";
    exit(EXIT_FAILURE);
  }

  // Render text
  SDL_Color color = { 255, 255, 255 };
  players_menu_.OnePlayer(SDL_CreateTextureFromSurface(
          sdl_renderer, TTF_RenderText_Solid(font.get(),"One Player", color)));
  players_menu_.TwoPlayer(SDL_CreateTextureFromSurface(
          sdl_renderer, TTF_RenderText_Solid(font.get(),"Two Player", color)));
  // End TODO: Customize -------------------------------------------------------
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::vector<Snake*> snakes, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body(s)
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (Snake* snake : snakes) {
    for (SDL_Point const &point : snake->body) {
      block.x = point.x * block.w;
      block.y = point.y * block.h;
      SDL_RenderFillRect(sdl_renderer, &block);
    }
  }

  // Render snake's head(s)
  bool first_snake = true;
  for (Snake* snake : snakes) {
    block.x = static_cast<int>(snake->head_x) * block.w;
    block.y = static_cast<int>(snake->head_y) * block.h;
    if (snake->alive) {
      if (first_snake) {
        SDL_SetRenderDrawColor(sdl_renderer, 0, 122, 204, 255);
        first_snake = false;
      } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0, 204, 122, 255);
      }
      
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);
    }
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::renderPlayerSelectMenu(const bool& one_player){
  // TODO: Customize -------------------------------------------------------
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  SDL_Rect message_rect_1;
  SDL_Rect message_rect_2;

  message_rect_1.x = 180;
  message_rect_1.y = 370;
  message_rect_1.w = 300;
  message_rect_1.h = 70;

  message_rect_2.x = 180;
  message_rect_2.y = 435;
  message_rect_2.w = 300;
  message_rect_2.h = 70;

  // Update Screen
  if(SDL_RenderCopy(sdl_renderer, players_menu_.OnePlayer(), NULL, &message_rect_1) < 0)
    std::cerr << "SDL_RenderCopy ERROR.\n";

  if(SDL_RenderCopy(sdl_renderer, players_menu_.TwoPlayer(), NULL, &message_rect_2) < 0)
    std::cerr << "SDL_RenderCopy ERROR.\n";

  SDL_Rect block_1;
  block_1.w = 50;
  block_1.h = 50;

  block_1.x = 110;
  block_1.y = 380;

  SDL_Rect block_2;
  block_2.w = 50;
  block_2.h = 50;

  block_2.x = 110;
  block_2.y = 445;

  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  if(one_player)
    SDL_RenderFillRect(sdl_renderer, &block_1);
  else
    SDL_RenderFillRect(sdl_renderer, &block_2);

  SDL_RenderPresent(sdl_renderer);
  // End TODO: Customize -------------------------------------------------------
}

