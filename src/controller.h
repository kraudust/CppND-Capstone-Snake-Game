#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool& running, Snake& snake1, Snake& snake2) const;
  void selectPlayerCount(bool& one_player, bool& num_players_picked) const;

 private:
  void ChangeDirection(Snake& snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif