#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "SDL_ttf.h"
#include "snake.h"
#include "playersmenu.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(std::vector<Snake*>& snakes, SDL_Point const& food);
  void UpdateWindowTitle(std::vector<Snake*>& snakes, int fps, int two_p_time_left);
  void RenderPlayerSelectMenu(const bool& running);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  PlayersMenu players_menu_;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif