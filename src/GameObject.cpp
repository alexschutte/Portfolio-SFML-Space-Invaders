#include "GameObject.h"

GameObject::GameObject()
{
  direction.x = 0;
  direction.y = 0;
}

GameObject::~GameObject()
{
}

bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename)
{
  sprite = new sf::Sprite();
  texture.loadFromFile(filename);
  sprite->setTexture(texture);
  return true;
}

sf::Sprite* GameObject::getSprite()
{
  return sprite;
}