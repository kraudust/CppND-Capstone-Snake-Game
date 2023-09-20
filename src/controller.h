#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool& running, std::vector<Snake*> snakes) const;
  void SelectPlayerCount(bool& one_player, bool& num_players_picked) const;

 private:
  void ChangeDirection(Snake* snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif