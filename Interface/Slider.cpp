#include "Slider.hpp"

Slider::Slider(float x, float y, float width, float min, float max, int type)
    : minValue(min), maxValue(max), isDragging(false) {
  track.setSize({width, 5});
  track.setFillColor(sf::Color::Black);
  track.setPosition(x, y);
  thumb.setRadius(10);
  thumb.setFillColor(sf::Color::White);
  thumb.setOutlineThickness(2);
  thumb.setOutlineColor(sf::Color::Black);
  if (type == 1) {
    thumb.setPosition(x + width / 5 - thumb.getRadius(),
                      y - thumb.getRadius() + track.getSize().y / 2.0f);
  } else if (type == 2) {
    thumb.setPosition(x + width / 2 - thumb.getRadius(),
                      y - thumb.getRadius() + track.getSize().y / 2.0f);
  }
}

void Slider::draw(sf::RenderWindow &window) {
  window.draw(track);
  window.draw(thumb);
}

void Slider::handleEvent(sf::Event event, sf::RenderWindow &window,
                         sf::Music &music) {
  sf::Vector2f mousePos =
      window.mapPixelToCoords(sf::Mouse::getPosition(window));
  if (event.type == sf::Event::MouseButtonPressed) {
    if (thumb.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
      isDragging = true;
    }
  }
  if (event.type == sf::Event::MouseButtonReleased) {
    isDragging = false;
  }
  if (isDragging && event.type == sf::Event::MouseMoved) {
    float newX = mousePos.x - thumb.getRadius();
    float leftBound = track.getPosition().x;
    float rightBound = leftBound + track.getSize().x;
    if (newX < leftBound)
      newX = leftBound;
    if (newX > rightBound - thumb.getRadius() * 2)
      newX = rightBound - thumb.getRadius() * 2;
    thumb.setPosition(newX, thumb.getPosition().y);
    float trackWidth = rightBound - leftBound;
    if (trackWidth > 0) {
      float usableWidth = trackWidth - thumb.getRadius() * 2;
      if (usableWidth <= 0)
        usableWidth = 1.0f;
      float ratio = (newX - leftBound) / usableWidth;
      ratio = std::max(0.0f, std::min(1.0f, ratio));
      float volume = minValue + ratio * (maxValue - minValue);
      music.setVolume(std::max(minValue, std::min(maxValue, volume)));
    }
  }
}

void Slider::handleEvent(sf::Event event, sf::RenderWindow &window,
                         int &playersNumber) {
  sf::Vector2f mousePos =
      window.mapPixelToCoords(sf::Mouse::getPosition(window));
  if (event.type == sf::Event::MouseButtonPressed) {
    if (thumb.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
      isDragging = true;
    }
  }
  if (event.type == sf::Event::MouseButtonReleased) {
    isDragging = false;
  }
  if (isDragging && event.type == sf::Event::MouseMoved) {
    float newX = mousePos.x - thumb.getRadius();
    float leftBound = track.getPosition().x;
    float rightBound = leftBound + track.getSize().x;
    if (newX < leftBound)
      newX = leftBound;
    if (newX > rightBound - thumb.getRadius() * 2)
      newX = rightBound - thumb.getRadius() * 2;
    thumb.setPosition(newX, thumb.getPosition().y);
    float trackWidth = rightBound - leftBound;
    if (trackWidth > 0) {
      float usableWidth = trackWidth - thumb.getRadius() * 2;
      if (usableWidth <= 0)
        usableWidth = 1.0f;
      float ratio = (newX - leftBound) / usableWidth;
      ratio = std::max(0.0f, std::min(1.0f, ratio));
      float volume = minValue + ratio * (maxValue - minValue);
      playersNumber = std::max(minValue, std::min(maxValue, volume));
    }
  }
}
sf::FloatRect Slider::getBounds() const { return track.getGlobalBounds(); }
