#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Slider {
private:
  sf::RectangleShape track; // Полоса ползунка
  sf::CircleShape thumb;    // Бегунок
  float minValue, maxValue; // Диапазон значений (0 - 100)
  bool isDragging = false;  // Флаг перемещения бегунка

public:
  Slider(float x, float y, float width, float min, float max)
      : minValue(min), maxValue(max) {
    track.setSize({width, 5});
    track.setFillColor(sf::Color::Black); // Черная полоса для контраста
    track.setPosition(x, y);

    thumb.setRadius(10);
    thumb.setFillColor(sf::Color::White); // Белый бегунок
    thumb.setOutlineThickness(2); // Черная обводка для видимости
    thumb.setOutlineColor(sf::Color::Black);
    thumb.setPosition(x + width / 2 - thumb.getRadius(), y - thumb.getRadius());
  }

  void draw(sf::RenderWindow &window) {
    window.draw(track);
    window.draw(thumb);
  }

  void handleEvent(sf::Event event, sf::RenderWindow &window,
                   sf::Music &music) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

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

      float volume = ((newX - leftBound) / (rightBound - leftBound)) *
                         (maxValue - minValue) +
                     minValue;
      music.setVolume(volume);
    }
  }
};

class Menu {
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

public:
  Menu()
      : window(sf::VideoMode(1280, 800), L"Монополия - Меню"),
        volumeSlider(800, 500, 200, 0, 100) {
    if (!font.loadFromFile("KabelCTT Medium.ttf")) {
      std::cerr << "Ошибка загрузки шрифта!" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("background.jpg")) {
      std::cerr << "Ошибка загрузки фонового изображения!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    setupButton(playButton, playText, L"Играть", {800, 150}, playCorners);
    setupButton(settingsButton, settingsText, L"Настройки", {800, 250},
                settingsCorners);
    setupButton(exitButton, exitText, L"Выход", {800, 350}, exitCorners);

    if (!backgroundMusic.openFromFile("5.-Flip-of-a-Coin.wav")) {
      std::cerr << "Ошибка загрузки музыки!" << std::endl;
    } else {
      backgroundMusic.setLoop(true);
      backgroundMusic.setVolume(10);
      backgroundMusic.play();
    }

    volumeText.setFont(font);
    volumeText.setString(L"Громкость");
    volumeText.setCharacterSize(24);
    volumeText.setFillColor(sf::Color::Black);
    volumeText.setPosition(850, 460);
  }

  void setupButton(sf::RectangleShape &button, sf::Text &text,
                   const std::wstring &str, sf::Vector2f position,
                   std::vector<sf::CircleShape> &corners) {
    float cornerRadius = 25.0f;
    float buttonWidth = 200.0f;
    float buttonHeight = 50.0f;

    button.setSize({buttonWidth - 2 * cornerRadius, buttonHeight});
    button.setFillColor(sf::Color::Red);
    button.setPosition(position.x + cornerRadius, position.y);

    text.setFont(font);
    text.setString(sf::String(str));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
    text.setPosition(position.x + buttonWidth / 2.0f,
                     position.y + buttonHeight / 2.0f);

    corners.clear();
    for (int i = 0; i < 2; ++i) {
      sf::CircleShape corner(cornerRadius, 30);
      corner.setFillColor(sf::Color::Red);
      if (i == 0) {
        corner.setPosition(position.x, position.y);
      } else {
        corner.setPosition(position.x + buttonWidth - 2 * cornerRadius,
                           position.y);
      }
      corners.push_back(corner);
    }
  }

  void run() {
    while (window.isOpen()) {
      handleEvents();
      render();
    }
  }

  void handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
          std::wcout << L"Играть нажато!" << std::endl;
        } else if (settingsButton.getGlobalBounds().contains(mousePos.x,
                                                             mousePos.y)) {
          std::wcout << L"Настройки нажаты!" << std::endl;
        } else if (exitButton.getGlobalBounds().contains(mousePos.x,
                                                         mousePos.y)) {
          window.close();
        }
      }

      volumeSlider.handleEvent(event, window, backgroundMusic);
    }
  }

  void render() {
    window.clear(sf::Color::Black);
    window.draw(backgroundSprite);

    for (const auto &corner : playCorners)
      window.draw(corner);
    window.draw(playButton);
    window.draw(playText);

    for (const auto &corner : settingsCorners)
      window.draw(corner);
    window.draw(settingsButton);
    window.draw(settingsText);

    for (const auto &corner : exitCorners)
      window.draw(corner);
    window.draw(exitButton);
    window.draw(exitText);

    window.draw(volumeText);
    volumeSlider.draw(window);

    window.display();
  }
};

int main() {
  setlocale(LC_ALL, "ru_RU.utf8");
  Menu menu;
  menu.run();
  return 0;
}
