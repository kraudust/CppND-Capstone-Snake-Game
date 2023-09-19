#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, Controller* controller,
  Renderer* renderer, std::size_t target_frame_duration)
  : snake1_(grid_width, grid_height, false),
    snake2_(grid_width, grid_height, true),
    engine(dev()),
    random_w(0, static_cast<int>(grid_width - 1)),
    random_h(0, static_cast<int>(grid_height - 1)),
    controller_(controller),
    renderer_(renderer),
    target_frame_duration_(target_frame_duration),
    one_player_(true)
{
  // Before entering the main game loop, open the start menu where player must select 1 or 2 player
  bool num_players_picked(false);
  title_timestamp = SDL_GetTicks();

  while (!num_players_picked) {
    frame_start = SDL_GetTicks();

    controller_->selectPlayerCount(one_player_, num_players_picked);
    renderer_->renderPlayerSelectMenu(one_player_);

    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer_->UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration_) {
      SDL_Delay(target_frame_duration_ - frame_duration);
    }
  }
  // Populate snake vector with either 1 or 2 players based on user input
  snake_vec_.push_back(&snake1_);
  if (!one_player_) {
    snake_vec_.push_back(&snake2_);
  }
  PlaceFood();
}

void Game::Run() {
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller_->HandleInput(running, snake_vec_);
    Update();
    renderer_->Render(snake_vec_, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer_->UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration_) {
      SDL_Delay(target_frame_duration_ - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  bool occupied;
  while (true) {
    occupied = false;
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing food
    for (Snake* snake : snake_vec_) {
      if (snake->SnakeCell(x, y)) {
        occupied = true;
        break;
      }
    }
    if (!occupied) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  // Stop the game if any snakes are dead
  for (Snake* snake : snake_vec_) {
    if (!snake->alive) {
      return;
    }
  }

  // Update the snakes
  for (Snake* snake : snake_vec_) {
    snake->Update();
    int new_x = static_cast<int>(snake->head_x);
    int new_y = static_cast<int>(snake->head_y);

    if (food.x == new_x && food.y == new_y) {
      score++;
      PlaceFood();
      // Grow snake and increase speed.
      snake->GrowBody();
      snake->speed += 0.005;
    }
  }
}

int Game::GetScore() const { return score; } // TODO:
int Game::GetSize() const { return snake_vec_[0]->size; } //TODO: