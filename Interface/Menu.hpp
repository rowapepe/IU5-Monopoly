#pragma once
#include "Slider.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Slider;

class Menu {
public:
  enum class MenuAction { Continue, Play, Exit, WindowClosed };

private:
  sf::RenderWindow window;
  sf::Font font;
  sf::Text playText, settingsText, exitText, volumeText;
  sf::RectangleShape playButton, settingsButton, exitButton;
  sf::Texture backgroundTexture;
  sf::Sprite backgroundSprite;
  std::vector<sf::CircleShape> playCorners, settingsCorners, exitCorners;
  sf::Music backgroundMusic;
  Slider volumeSlider;
  enum class State { Running, ConfirmingExit };
  State currentState;
  sf::Text menuConfirmText;
  sf::RectangleShape menuConfirmBackground;
  sf::RectangleShape menuYesButton, menuNoButton;
  sf::Text menuYesText, menuNoText;
  void setupButton(sf::RectangleShape &button, sf::Text &text,
                   const std::wstring &str, sf::Vector2f position,
                   std::vector<sf::CircleShape> &corners);
  bool isMouseOverCorners(const std::vector<sf::CircleShape> &corners,
                          const sf::Vector2f &mousePos) const;
  void setupMenuConfirmationUI();
  void drawMenuConfirmationUI();
  void adjustWindowSize(sf::Event::SizeEvent sizeEvent);
  int playersNumber;

public:
  Menu();
  MenuAction run();
  MenuAction handleEvents();
  void render();
  int getPlayersNumber() const;
};
