#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class Slider {
private:
  sf::RectangleShape track;
  sf::CircleShape thumb;
  float minValue, maxValue;
  bool isDragging;

public:
  Slider(float x, float y, float width, float min, float max, int type);
  void draw(sf::RenderWindow &window);
  void handleEvent(sf::Event event, sf::RenderWindow &window, sf::Music &music);
  void handleEvent(sf::Event event, sf::RenderWindow &window, int& playersNumber);
  sf::FloatRect getBounds() const;
};
