#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake* snake, Snake::Direction input,
                                 Snake::Direction opposite) const 
{
  if (snake->direction != opposite || snake->size == 1) {
    snake->direction = input;
  }
  return;
}

void Controller::HandleInput(bool& running, std::vector<Snake*> snakes) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snakes[0], Snake::Direction::kUp, Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snakes[0], Snake::Direction::kDown, Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snakes[0], Snake::Direction::kLeft, Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snakes[0], Snake::Direction::kRight, Snake::Direction::kLeft);
          break;

        // Add controls for an optional second snake
        case SDLK_w:
          if (snakes.size() == 2) {
            ChangeDirection(snakes[1], Snake::Direction::kUp, Snake::Direction::kDown);
          }
          break;

        case SDLK_s:
          if (snakes.size() == 2) {
          ChangeDirection(snakes[1], Snake::Direction::kDown, Snake::Direction::kUp);
          }
          break;

        case SDLK_a:
          if (snakes.size() == 2) {
            ChangeDirection(snakes[1], Snake::Direction::kLeft, Snake::Direction::kRight);
          }
          break;

        case SDLK_d:
          if (snakes.size() == 2) {
            ChangeDirection(snakes[1], Snake::Direction::kRight, Snake::Direction::kLeft);
          }
          break;
      }
    }
  }
}

void Controller::SelectPlayerCount(bool& one_player, bool& num_players_picked) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      one_player = false;
      num_players_picked = true;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          one_player = !one_player;
          break;

        case SDLK_DOWN:
          one_player = !one_player;
          break;

        case SDLK_RETURN:
          num_players_picked = true;
          break;
      }
    }
  }
}