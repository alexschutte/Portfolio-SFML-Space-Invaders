
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  /*These values must be reinitialised in this function because they need to be
  set to specific values for a restart*/
  int row_location = 0;
  int velocity = 0;
  int alien_v = 2;
  int current_shot_count = 0;
  int score = 0;
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "FONT DID NOT LOAD!\n";
  }

  //Initialising all the text used

  play_text.setString("PRESS ENTER TO START");
  play_text.setFont(font);
  play_text.setFillColor(sf::Color(255, 255, 255, 255));
  play_text.setCharacterSize(50);
  play_text.setPosition(window.getSize().x/2 - play_text.getGlobalBounds().width/2 , window.getSize().y/2 - play_text.getGlobalBounds().height/2);

  game_over_text.setString("YOU DIED");
  game_over_text.setFont(font);
  game_over_text.setFillColor(sf::Color(255, 255, 255, 255));
  game_over_text.setCharacterSize(80);
  game_over_text.setPosition(window.getSize().x/2 - game_over_text.getGlobalBounds().width/2 , window.getSize().y/3 - game_over_text.getGlobalBounds().height/2);

  game_won_text.setString("YOU WON!");
  game_won_text.setFont(font);
  game_won_text.setFillColor(sf::Color(255, 255, 255, 255));
  game_won_text.setCharacterSize(80);
  game_won_text.setPosition(window.getSize().x/2 - game_won_text.getGlobalBounds().width/2 , window.getSize().y/3 - game_won_text.getGlobalBounds().height/2);

  restart_text.setString("PRESS ENTER TO PLAY AGAIN ...");
  restart_text.setFont(font);
  restart_text.setFillColor(sf::Color(255, 255, 255, 255));
  restart_text.setCharacterSize(50);
  restart_text.setPosition(window.getSize().x/2 - restart_text.getGlobalBounds().width/2 , window.getSize().y/2 - restart_text.getGlobalBounds().height/2);

  main_menu_text.setString("SPACE INVADERS");
  main_menu_text.setFont(font);
  main_menu_text.setFillColor(sf::Color(255, 255, 255, 255));
  main_menu_text.setCharacterSize(80);
  main_menu_text.setPosition(window.getSize().x/2 - main_menu_text.getGlobalBounds().width/2 , window.getSize().y/3 - main_menu_text.getGlobalBounds().height/2);

  score_text.setString("Score: ");
  score_text.setFont(font);
  score_text.setFillColor(sf::Color(255, 255, 255, 255));
  score_text.setCharacterSize(40);
  score_text.setPosition(window.getSize().x/25 , window.getSize().y/20);

  //Initialising all sprites

  player.initialiseSprite(player_texture , "Data/Images/SpaceShooterRedux/PNG/playerShip3_green.png");
  player.getSprite()->setPosition(window.getSize().x/2 - player.getSprite()->getGlobalBounds().width/2 , window.getSize().y/1.2 - player.getSprite()->getGlobalBounds().height/2);

  //For loop that cycles through the array used for the aliens

  for (int i = 0; i < 20; i ++)
  {
    alien[i].initialiseSprite(alien_texture , "Data/Images/SpaceShooterRedux/PNG/ufoRed.png");
    alien[i].visibility = true;

    if (i < 10)
    {
      alien[i].getSprite()->setPosition(player.getSprite()->getGlobalBounds().width / 2 + row_location * 100 ,window.getSize().y / 5 - player.getSprite()->getGlobalBounds().height / 2);
      row_location++;
    }
    else
    {
      if (i == 10)
      {
        row_location = 0;
      }
      alien[i].getSprite()->setPosition(player.getSprite()->getGlobalBounds().width / 2 + row_location * 100 ,window.getSize().y / 2.8 - player.getSprite()->getGlobalBounds().height / 2);
      row_location++;
    }
  }

  for (int i = 0; i < 23; i++)
  {
    shots[i].initialiseSprite(shots_texture , "Data/Images/SpaceShooterRedux/PNG/Lasers/laserRed14.png");
    shots[i].visibility = false;
    shots[i].getSprite()->setPosition(window.getSize().x/2 - player.getSprite()->getGlobalBounds().width/2 , window.getSize().y/1.2 - player.getSprite()->getGlobalBounds().height/2);
  }

  return true;
}

void Game::update(float dt)
{
  switch (current)
  {
    case menu:
      break;
    case gameplay:
      score_text.setString("Score: " + std::to_string(score));
      player.getSprite()->move(velocity * dt , 0);
      if (player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width > window.getSize().x)
      {
        velocity = 0;
        player.getSprite()->move(-10 , 0);
      }
      if (player.getSprite()->getPosition().x < 0)
      {
        velocity = 0;
        player.getSprite()->move(10 , 0);
      }
      if ((alien[9].getSprite()->getPosition().x + alien[9].getSprite()->getGlobalBounds().width > window.getSize().x) or (alien[0].getSprite()->getPosition().x < 0))
      {
        alien_v = - alien_v;
      }
      for (int i = 0; i < 20; i ++)
      {
          alien[i].getSprite()->move(alien_v , 0);
          if ((alien[9].getSprite()->getPosition().x + alien[9].getSprite()->getGlobalBounds().width > window.getSize().x) or (alien[0].getSprite()->getPosition().x < 0))
          {
            alien[i].getSprite()->setPosition(alien[i].getSprite()->getPosition().x , alien[i].getSprite()->getPosition().y + 4);
          }
      }
      for (int i = 0; i < 23; i ++)
      {
        if (shots[i].visibility == true)
        {

          shots[i].getSprite()->move(0 , -10);
          if (shots[i].getSprite()->getPosition().y + shots[i].getSprite()->getGlobalBounds().height < 0)
          {
            shots[i].visibility = false;
            score --;
          }
        }
      }
      for (int i = 0 ; i < 20 ; i++)
      {
        if (collisionPlayer(*player.getSprite(), *alien[i].getSprite()))
        {
          current = game_over;
        }
      }

      for (int i = 0 ; i < 23 ; i++)
      {
        if (shots[i].visibility)
        {
          for (int f = 0; f < 20; f++)
          {
            if (alien[f].visibility)
            {
              if (shotDetector(*shots[i].getSprite(), *alien[f].getSprite()))
              {
                shots[i].visibility = false;
                alien[f].visibility = false;
                score ++;
              }
            }
          }
        }
      }
      /*I tried to do this with std::all_of , but I could not get the function
      to check a bool value on all elements of the array and return a bool*/
      if (!alien[0].visibility and !alien[1].visibility and !alien[2].visibility
          and !alien[3].visibility and !alien[4].visibility
          and !alien[5].visibility and !alien[6].visibility
          and !alien[7].visibility and !alien[8].visibility
          and !alien[9].visibility and !alien[10].visibility
          and !alien[11].visibility and !alien[12].visibility
          and !alien[13].visibility and !alien[14].visibility
          and !alien[15].visibility and !alien[16].visibility
          and !alien[17].visibility and !alien[18].visibility
          and !alien[19].visibility)
      {
        current = game_won;
      }

//      if (std::all_of(alien[0] , alien[19] , [](bool visibility){return !visibility;}))
//      {
//        current = game_won;
//      }

      break;
  }

}

void Game::render()
{
  switch (current)
  {
    case menu:
      window.draw(main_menu_text);
      window.draw(play_text);
      break;
    case gameplay:
      window.draw(score_text);
      window.draw(*player.getSprite());
      for (int i = 0; i < 20; i ++)
      {
        if (alien[i].visibility)
        {
          window.draw(*alien[i].getSprite());
        }
      }
      for (int i = 0; i < 23; i ++)
      {
        if (shots[i].visibility)
        {
          window.draw(*shots[i].getSprite());
        }
      }
      break;
    case game_over:
      score = 0;
      window.draw(game_over_text);
      window.draw(restart_text);
      break;
    case game_won:
      score = 0;
      window.draw(game_won_text);
      window.draw(restart_text);
      break;
  }

}

//Function to detect if the alien ships have hit the player

bool Game::collisionPlayer(sf::Sprite player , sf::Sprite alien)
{
  if (player.getPosition().y <= alien.getPosition().y + alien.getGlobalBounds().height)
  {
    return true;
  }
  return false;
}

//Function for shot hit boxes

bool Game::shotDetector(sf::Sprite shot , sf::Sprite alien)
{
  if (shot.getPosition().y <= alien.getPosition().y + alien.getGlobalBounds().height
      && shot.getPosition().x >= alien.getPosition().x
      && shot.getPosition().x <= alien.getPosition().x + alien.getGlobalBounds().width
      && shot.getPosition().y >= alien.getPosition().y)
  {
    return true;
  }
  return false;
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
  switch (current)
  {
    case menu:
      if (event.key.code == sf::Keyboard::Enter)
      {
        current = gameplay;
      }
      break;
    case gameplay:
      if (event.key.code == sf::Keyboard::D)
      {
        velocity = 500;
      }
      if (event.key.code == sf::Keyboard::A)
      {
        velocity = -500;
      }
      if (event.key.code == sf::Keyboard::Space)
      {
        if (current_shot_count < 23)
        {
          shots[current_shot_count].getSprite()->setPosition(player.getSprite()->getPosition().x + player.getSprite()->getGlobalBounds().width / 2 - 7 , player.getSprite()->getPosition().y);
          shots[current_shot_count].visibility = true;
          current_shot_count ++;
        }
        else
        {
          current_shot_count = 0;
        }
      }
      break;
    case game_won:
      if (event.key.code == sf::Keyboard::Enter)
      {
        init();
        current = gameplay;
      }
      break;
    case game_over:
      if (event.key.code == sf::Keyboard::Enter)
      {
        init();
        current = gameplay;
      }
      break;
  }
}

void Game::keyReleased(sf::Event event)
{
  if (event.key.code == sf::Keyboard::D)
  {
    velocity = 0;
  }
  if (event.key.code == sf::Keyboard::A)
  {
    velocity = 0;
  }
}

