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

  TTF_Font* font = TTF_OpenFont("../roboto/Roboto-Bold.ttf", 25);

  if(font == nullptr){
    std::cerr << "Font not loaded properly.\n";
    exit(0);
  }

  SDL_Color font_color = { 255, 255, 255 }; // White
  players_menu_.OnePlayer(SDL_CreateTextureFromSurface(
          sdl_renderer, TTF_RenderText_Solid(font,"One Player", font_color)));
  players_menu_.TwoPlayer(SDL_CreateTextureFromSurface(
          sdl_renderer, TTF_RenderText_Solid(font,"Two Player", font_color)));
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(std::vector<Snake*>& snakes, SDL_Point const &food) {
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
  bool first_snake = true;
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (Snake* snake : snakes) {
    if (first_snake) {
      SDL_SetRenderDrawColor(sdl_renderer, 0, 150, 255, 255);
      first_snake = false;
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 150, 255);
    }
    for (SDL_Point const &point : snake->body) {
      block.x = point.x * block.w;
      block.y = point.y * block.h;
      SDL_RenderFillRect(sdl_renderer, &block);
    }
  }

  // Render snake's head(s)
  first_snake = true;
  for (Snake* snake : snakes) {
    block.x = static_cast<int>(snake->head_x) * block.w;
    block.y = static_cast<int>(snake->head_y) * block.h;
    if (snake->alive) {
      if (first_snake) {
        SDL_SetRenderDrawColor(sdl_renderer, 0, 50, 255, 255);
        first_snake = false;
      } else {
        SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0, 255);
      }
      
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);
    }
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(std::vector<Snake*>& snakes, int fps, int two_p_time_left)
{
  std::string title;
  if (snakes.size() == 1) {
    int score = snakes[0]->size - 1;
    title = ("Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps));
  } else {
    int blue_score = snakes[0]->size - 1;
    int green_score = snakes[1]->size - 1;
    title = (
      "Time Left: " + std::to_string(two_p_time_left) + " - Blue Score: " + std::to_string(blue_score) +
      " - Green Score: " + std::to_string(green_score) + " - FPS: " + std::to_string(fps));
  }
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderPlayerSelectMenu(const bool& one_player){
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Set up rectangles to hold the player font textures
  SDL_Rect one_player_rect;
  SDL_Rect two_player_rect;
  one_player_rect.x = screen_width / 4;
  one_player_rect.y = screen_height / 2 - screen_height / 10;
  one_player_rect.w = screen_width / 2;
  one_player_rect.h = screen_height / 10;
  two_player_rect.x = screen_width / 4;
  two_player_rect.y = screen_height / 2 + screen_height / 10;
  two_player_rect.w = screen_width / 2;
  two_player_rect.h = screen_height / 10;

  // Copy the player font textures to the renderer
  SDL_RenderCopy(sdl_renderer, players_menu_.OnePlayer(), NULL, &one_player_rect);
  SDL_RenderCopy(sdl_renderer, players_menu_.TwoPlayer(), NULL, &two_player_rect);

  // Make blocks that hover on the two menu options
  SDL_Rect select_p_one_block;
  select_p_one_block.w = 30;
  select_p_one_block.h = 30;  
  select_p_one_block.x = screen_width / 4 - select_p_one_block.w;
  select_p_one_block.y = screen_height / 2 - screen_height / 10 + select_p_one_block.h / 2;
  SDL_Rect select_p_two_block;
  select_p_two_block.x = screen_width / 4 - select_p_one_block.w;;
  select_p_two_block.y = screen_height / 2 + screen_height / 10  + select_p_one_block.h / 2;
  select_p_two_block.w = 30;
  select_p_two_block.h = 30;

  // Switch between rendering the two menu option blocks as the user arrows between them
  SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255);
  if(one_player) {
    SDL_RenderFillRect(sdl_renderer, &select_p_one_block);
  } else {
    SDL_RenderFillRect(sdl_renderer, &select_p_two_block);
  }

  // Update screen
  SDL_RenderPresent(sdl_renderer);
}

