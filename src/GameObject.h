#include "SFML/Graphics.hpp"
#include "Vector2.h"
#ifndef SPACEINVADERS_GAMEOBJECT_H
#define SPACEINVADERS_GAMEOBJECT_H

class GameObject
{
 public:
  GameObject();
  ~GameObject();
  bool initialiseSprite(sf::Texture &texture , std::string filename);
  sf::Sprite* getSprite();
  bool visibility = false;
  Vector2 direction;
  float speed;
 private:
  sf::Sprite* sprite = nullptr;
};


#endif // SPACEINVADERS_GAMEOBJECT_H
