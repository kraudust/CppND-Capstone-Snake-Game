#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, Controller* controller, Renderer* renderer, std::size_t target_frame_duration);
  void Run();
  void PrintScore();
 private:
  Snake snake1_;
  Snake snake2_;
  std::vector<Snake*> snake_vec_;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  void PlaceFood();
  void Update();
  int title_timestamp;
  int frame_start;
  int frame_end;
  int frame_duration;
  int game_start;
  int two_p_game_duration;
  int game_runtime;
  int frame_count{0};
  Controller* controller_;
  Renderer* renderer_;
  std::size_t target_frame_duration_;
  bool one_player_;
};

#endif