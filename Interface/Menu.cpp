#include "Menu.hpp"
#include "Slider.hpp"
#include <iostream>

Menu::Menu()
    : window(sf::VideoMode(1280, 800), L"Монополия - Меню",
             sf::Style::Titlebar | sf::Style::Close),
      volumeSlider(800, 500, 200, 0, 100) {
  window.setVerticalSyncEnabled(true);
  if (!font.loadFromFile("../assets/KabelCTT Medium.ttf")) {
    std::cerr << "Ошибка загрузки шрифта!" << std::endl;
  }
  if (!backgroundTexture.loadFromFile("../assets/background.jpg")) {
    std::cerr << "Ошибка загрузки фонового изображения!" << std::endl;
  }
  backgroundSprite.setTexture(backgroundTexture);
  setupButton(playButton, playText, L"Играть", {800, 150}, playCorners);
  setupButton(settingsButton, settingsText, L"Настройки", {800, 250},
              settingsCorners);
  setupButton(exitButton, exitText, L"Выход", {800, 350}, exitCorners);
  if (!backgroundMusic.openFromFile("../assets/5.-Flip-of-a-Coin.wav")) {
    std::cerr << "Ошибка загрузки музыки!" << std::endl;
  } else {
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(20);
    backgroundMusic.play();
  }
  volumeText.setFont(font);
  volumeText.setString(L"Громкость");
  volumeText.setCharacterSize(24);
  volumeText.setFillColor(sf::Color::Black);
  volumeText.setPosition(850, 460);
  currentState = State::Running;
  setupMenuConfirmationUI();
}

void Menu::setupButton(sf::RectangleShape &button, sf::Text &text,
                       const std::wstring &str, sf::Vector2f position,
                       std::vector<sf::CircleShape> &corners) {
  float cornerRadius = 25.0f;
  float buttonWidth = 200.0f;
  float buttonHeight = 50.0f;
  button.setSize({buttonWidth - 2 * cornerRadius, buttonHeight});
  button.setFillColor(sf::Color::Red);
  button.setPosition(position.x + cornerRadius, position.y);
  text.setFont(font);
  text.setString(sf::String::fromUtf32(str.begin(), str.end()));
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

bool Menu::isMouseOverCorners(const std::vector<sf::CircleShape> &corners,
                              const sf::Vector2f &mousePos) const {
  for (const auto &corner : corners) {
    if (corner.getGlobalBounds().contains(mousePos)) {
      return true;
    }
  }
  return false;
}

void Menu::setupMenuConfirmationUI() {
  sf::Vector2u windowSize = window.getSize();
  float centerX = windowSize.x / 2.0f;
  float centerY = windowSize.y / 2.0f;
  menuConfirmBackground.setSize({400, 150});
  menuConfirmBackground.setFillColor(sf::Color(0, 0, 0, 200));
  menuConfirmBackground.setOutlineColor(sf::Color::White);
  menuConfirmBackground.setOutlineThickness(2);
  menuConfirmBackground.setOrigin(200, 75);
  menuConfirmBackground.setPosition(centerX, centerY);
  menuConfirmText.setFont(font);
  menuConfirmText.setString(L"Вы уверены, что хотите выйти?");
  menuConfirmText.setCharacterSize(24);
  menuConfirmText.setFillColor(sf::Color::White);
  sf::FloatRect textBounds = menuConfirmText.getLocalBounds();
  menuConfirmText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                            textBounds.top + textBounds.height / 2.0f);
  menuConfirmText.setPosition(centerX, centerY - 30);
  menuYesButton.setSize({100, 40});
  menuYesButton.setFillColor(sf::Color(50, 150, 50));
  menuYesButton.setOrigin(50, 20);
  menuYesButton.setPosition(centerX - 70, centerY + 40);
  menuYesText.setFont(font);
  menuYesText.setString(L"Да");
  menuYesText.setCharacterSize(20);
  menuYesText.setFillColor(sf::Color::White);
  textBounds = menuYesText.getLocalBounds();
  menuYesText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                        textBounds.top + textBounds.height / 2.0f);
  menuYesText.setPosition(menuYesButton.getPosition());
  menuNoButton.setSize({100, 40});
  menuNoButton.setFillColor(sf::Color(150, 50, 50));
  menuNoButton.setOrigin(50, 20);
  menuNoButton.setPosition(centerX + 70, centerY + 40);
  menuNoText.setFont(font);
  menuNoText.setString(L"Нет");
  menuNoText.setCharacterSize(20);
  menuNoText.setFillColor(sf::Color::White);
  textBounds = menuNoText.getLocalBounds();
  menuNoText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                       textBounds.top + textBounds.height / 2.0f);
  menuNoText.setPosition(menuNoButton.getPosition());
}

void Menu::drawMenuConfirmationUI() {
  window.draw(menuConfirmBackground);
  window.draw(menuConfirmText);
  window.draw(menuYesButton);
  window.draw(menuYesText);
  window.draw(menuNoButton);
  window.draw(menuNoText);
}

Menu::MenuAction Menu::run() {
  while (window.isOpen()) {
    MenuAction currentAction = handleEvents();
    if (currentAction != MenuAction::Continue) {
      return currentAction;
    }
    render();
  }
  return MenuAction::WindowClosed;
}

Menu::MenuAction Menu::handleEvents() {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (currentState == State::Running) {
      if (event.type == sf::Event::Closed) {
        currentState = State::ConfirmingExit;
        return MenuAction::Continue;
      }
      if (event.type == sf::Event::Resized) {
        sf::FloatRect visibleArea(0.f, 0.f,
                                  static_cast<float>(event.size.width),
                                  static_cast<float>(event.size.height));
        window.setView(sf::View(visibleArea));
        setupMenuConfirmationUI();
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape) {
        currentState = State::ConfirmingExit;
        return MenuAction::Continue;
      }
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2f mousePos = window.mapPixelToCoords(
              {event.mouseButton.x, event.mouseButton.y});
          if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y) ||
              isMouseOverCorners(playCorners, mousePos)) {
            window.clear(sf::Color::White);
            window.display();
            backgroundMusic.stop();
            window.close();
            return MenuAction::Play;
          } else if (settingsButton.getGlobalBounds().contains(mousePos.x,
                                                               mousePos.y) ||
                     isMouseOverCorners(settingsCorners, mousePos)) {
            std::wcout << L"Настройки нажаты!" << std::endl;
          } else if (exitButton.getGlobalBounds().contains(mousePos.x,
                                                           mousePos.y) ||
                     isMouseOverCorners(exitCorners, mousePos)) {
            currentState = State::ConfirmingExit;
            return MenuAction::Continue;
          }
        }
      }
      volumeSlider.handleEvent(event, window, backgroundMusic);
    } else if (currentState == State::ConfirmingExit) {
      if (event.type == sf::Event::Closed) {
        window.close();
        return MenuAction::Exit;
      }
      if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Escape) {
        currentState = State::Running;
        return MenuAction::Continue;
      }
      if (event.type == sf::Event::MouseButtonPressed &&
          event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos =
            window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        if (menuYesButton.getGlobalBounds().contains(mousePos)) {
          window.close();
          return MenuAction::Exit;
        } else if (menuNoButton.getGlobalBounds().contains(mousePos)) {
          currentState = State::Running;
          return MenuAction::Continue;
        }
      }
    }
  }
  return MenuAction::Continue;
}

void Menu::render() {
  window.clear(sf::Color::Black);
  window.draw(backgroundSprite);
  if (currentState == State::Running) {
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
  } else if (currentState == State::ConfirmingExit) {
    drawMenuConfirmationUI();
  }
  window.display();
}

void Menu::adjustWindowSize(sf::Event::SizeEvent sizeEvent) {
  float aspectRatio = 16.0f / 9.0f;
  sf::Vector2u new_size;
  if (sizeEvent.width < sizeEvent.height * aspectRatio) {
    new_size.x = static_cast<unsigned int>(sizeEvent.height * aspectRatio);
    new_size.y = sizeEvent.height;
  } else {
    new_size.x = sizeEvent.width;
    new_size.y = static_cast<unsigned int>(sizeEvent.width / aspectRatio);
  }
  window.setSize(new_size);
  sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(new_size.x),
                            static_cast<float>(new_size.y));
  window.setView(sf::View(visibleArea));
}
