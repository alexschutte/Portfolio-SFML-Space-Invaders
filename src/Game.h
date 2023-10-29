
#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  bool collisionPlayer(sf::Sprite player , sf::Sprite alien);
  bool shotDetector(sf::Sprite shot , sf::Sprite alien);

 private:
  sf::RenderWindow& window;
  sf::Font font;
  sf::Text main_menu_text;
  sf::Text play_text;
  sf::Text game_over_text;
  sf::Text game_won_text;
  sf::Text restart_text;
  sf::Text score_text;
  enum game_state {menu, gameplay, game_over, game_won};
  game_state current = menu;
  GameObject player;
  sf::Texture player_texture;
  GameObject alien[20];
  sf::Texture alien_texture;
  GameObject shots[23];
  sf::Texture shots_texture;
  int row_location = 0;
  int velocity = 0;
  int alien_v = 2;
  int current_shot_count = 0;
  int score = 0;
};

#endif // SPACEINVADERS_GAME_H
