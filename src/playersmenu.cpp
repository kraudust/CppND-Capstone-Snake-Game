#include "playersmenu.h"

PlayersMenu::PlayersMenu() : one_player_texture_(nullptr, SDL_DestroyTexture), two_player_texture_(nullptr, SDL_DestroyTexture)
{
}

void PlayersMenu::OnePlayer(SDL_Texture* texture)
{
  one_player_texture_.reset(texture);
}

SDL_Texture* PlayersMenu::OnePlayer()
{
  return one_player_texture_.get();
}

void PlayersMenu::TwoPlayer(SDL_Texture* texture)
{
  two_player_texture_.reset(texture);
}

SDL_Texture* PlayersMenu::TwoPlayer()
{
  return two_player_texture_.get();
}