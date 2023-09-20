#ifndef PLAYERS_MENU_H
#define PLAYERS_MENU_H

#include <memory>
#include "SDL.h"

class PlayersMenu
{
public:
  PlayersMenu();

  void OnePlayer(SDL_Texture* texture);
  SDL_Texture* OnePlayer();

  void TwoPlayer(SDL_Texture* texture);
  SDL_Texture* TwoPlayer();

private:
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> one_player_texture_;
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> two_player_texture_;
};

#endif