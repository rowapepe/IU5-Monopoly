#include "Game.hpp"
#include <SFML/System/String.hpp>
#include <algorithm>
#include <string>

Game::Game()
    : gameWindow(sf::VideoMode(1280, 800), L"Монополия - Игра",
                 sf::Style::Titlebar | sf::Style::Close),
      chanceDeck("шанс"), communityChestDeck("казна") {
  gameWindow.setVerticalSyncEnabled(true);
  loadResources();
  setupPlayers(3);
  setupUI();
  currentState = State::Running;
  previousState = State::Running;

  currentPlayerIndex = 0;
  rolledDoubleCurrentMove = false;
  turnInProgress = true;
  actionRequired = false;
  showBuyButton = false;
  showEndTurnButton = false;

  rollDiceButton.setFillColor(sf::Color::Green);
  jailPayButton.setFillColor(sf::Color::Yellow);
  updateUI();
  diceResultText.setString(L"Ход Игрока 1! Бросайте кости.");

  std::cout << "\n--- Ход игрока " << currentPlayerIndex + 1 << " ---"
            << std::endl;
}

void Game::loadResources() {
  if (!gameFont.loadFromFile("../assets/KabelCTT Medium.ttf")) {
    std::cerr << "Не удалось загрузить шрифт assets/KabelCTT Medium.ttf!"
              << std::endl;
  }

  if (!gameBackgroundTexture.loadFromFile("../assets/game_background.jpg")) {
    std::cerr << "Не удалось загрузить фон assets/game_background.jpg!"
              << std::endl;
  } else {
    gameBackgroundTexture.setSmooth(true);
    gameBackgroundSprite.setTexture(gameBackgroundTexture);
    updateGameBackground();
  }
}

bool Game::IsPositionValid(int position) const {
  return position >= 0 && position < static_cast<int>(gameBoard.board.size());
}

void Game::setupUI() {
  setupGameUI();
  setupConfirmationUI();
  setupMessageBoxUI();
  updateUI();
}

void Game::setupConfirmationUI() {
  sf::Vector2u windowSize = gameWindow.getSize();
  float centerX = windowSize.x / 2.0f;
  float centerY = windowSize.y / 2.0f;

  confirmationBackground.setSize({400, 150});
  confirmationBackground.setFillColor(sf::Color(0, 0, 0, 200));
  confirmationBackground.setOutlineColor(sf::Color::White);
  confirmationBackground.setOutlineThickness(2);
  confirmationBackground.setOrigin(200, 75);
  confirmationBackground.setPosition(centerX, centerY);

  confirmationText.setFont(gameFont);
  confirmationText.setString(L"Вернуться в главное меню?");
  confirmationText.setCharacterSize(24);
  confirmationText.setFillColor(sf::Color::White);
  sf::FloatRect textBounds = confirmationText.getLocalBounds();
  confirmationText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                             textBounds.top + textBounds.height / 2.0f);
  confirmationText.setPosition(centerX, centerY - 30);

  yesButton.setSize({100, 40});
  yesButton.setFillColor(sf::Color(50, 150, 50));
  yesButton.setOrigin(50, 20);
  yesButton.setPosition(centerX - 70, centerY + 40);
  yesText.setFont(gameFont);
  yesText.setString(L"Да");
  yesText.setCharacterSize(20);
  yesText.setFillColor(sf::Color::White);
  textBounds = yesText.getLocalBounds();
  yesText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                    textBounds.top + textBounds.height / 2.0f);
  yesText.setPosition(yesButton.getPosition());

  noButton.setSize({100, 40});
  noButton.setFillColor(sf::Color(150, 50, 50));
  noButton.setOrigin(50, 20);
  noButton.setPosition(centerX + 70, centerY + 40);
  noText.setFont(gameFont);
  noText.setString(L"Нет");
  noText.setCharacterSize(20);
  noText.setFillColor(sf::Color::White);
  textBounds = noText.getLocalBounds();
  noText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                   textBounds.top + textBounds.height / 2.0f);
  noText.setPosition(noButton.getPosition());
}

void Game::setupGameUI() {
  sf::Vector2u windowSize = gameWindow.getSize();
  float buttonY = windowSize.y - 60.f;

  rollDiceButton.setSize({150, 50});
  rollDiceButton.setFillColor(sf::Color::Green);
  rollDiceButton.setPosition(50, buttonY - 60);
  rollDiceText.setFont(gameFont);
  rollDiceText.setString(L"Бросить кости");
  rollDiceText.setCharacterSize(20);
  rollDiceText.setFillColor(sf::Color::Black);
  sf::FloatRect textBounds = rollDiceText.getLocalBounds();
  rollDiceText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                         textBounds.top + textBounds.height / 2.0f);
  rollDiceText.setPosition(
      rollDiceButton.getPosition().x + rollDiceButton.getSize().x / 2.0f,
      rollDiceButton.getPosition().y + rollDiceButton.getSize().y / 2.0f);

  buyButton.setSize({150, 50});
  buyButton.setFillColor(sf::Color::Blue);
  buyButton.setPosition(50, buttonY - 120);
  buyText.setFont(gameFont);
  buyText.setString(L"Купить");
  buyText.setCharacterSize(20);
  buyText.setFillColor(sf::Color::White);
  textBounds = buyText.getLocalBounds();
  buyText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                    textBounds.top + textBounds.height / 2.0f);
  buyText.setPosition(buyButton.getPosition().x + buyButton.getSize().x / 2.0f,
                      buyButton.getPosition().y + buyButton.getSize().y / 2.0f);

  endTurnButton.setSize({180, 50});
  endTurnButton.setFillColor(sf::Color::Red);
  endTurnButton.setPosition(50, buttonY - 180);
  endTurnText.setFont(gameFont);
  endTurnText.setString(L"Закончить ход");
  endTurnText.setCharacterSize(20);
  endTurnText.setFillColor(sf::Color::White);
  endTurnText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                        textBounds.top + textBounds.height / 2.0f);
  endTurnText.setPosition(
      endTurnButton.getPosition().x + endTurnButton.getSize().x / 3.0f,
      endTurnButton.getPosition().y + endTurnButton.getSize().y / 2.0f);

  diceResultText.setFont(gameFont);
  diceResultText.setCharacterSize(18);
  diceResultText.setFillColor(sf::Color::Black);
  diceResultText.setPosition(0, rollDiceButton.getPosition().y / 2.0f);
  diceResultText.setString(L"");

  playerInfoText.setFont(gameFont);
  playerInfoText.setCharacterSize(18);
  playerInfoText.setFillColor(sf::Color::Black);
  playerInfoText.setPosition(windowSize.x - 230.f, windowSize.y - 150.f);
  playerInfoText.setString(L"");
}

void Game::setupMessageBoxUI() {
  sf::Vector2u windowSize = gameWindow.getSize();
  float centerX = windowSize.x / 2.0f;
  float centerY = windowSize.y / 2.0f;

  messageBoxBackground.setSize({600, 200});
  messageBoxBackground.setFillColor(sf::Color(50, 50, 150, 220));
  messageBoxBackground.setOutlineColor(sf::Color::White);
  messageBoxBackground.setOutlineThickness(2);
  messageBoxBackground.setOrigin(messageBoxBackground.getSize().x / 2.0f,
                                 messageBoxBackground.getSize().y / 2.0f);
  messageBoxBackground.setPosition(centerX, centerY);

  messageBoxText.setFont(gameFont);
  messageBoxText.setCharacterSize(20);
  messageBoxText.setFillColor(sf::Color::White);
  messageBoxText.setOrigin(0, 0);

  messageBoxOkButton.setSize({100, 40});
  messageBoxOkButton.setFillColor(sf::Color(0, 100, 0));
  messageBoxOkButton.setOrigin(messageBoxOkButton.getSize().x / 2.0f,
                               messageBoxOkButton.getSize().y / 2.0f);
  messageBoxOkButton.setPosition(
      centerX, centerY + messageBoxBackground.getSize().y / 2.0f - 40.f);

  messageBoxOkText.setFont(gameFont);
  messageBoxOkText.setString(L"OK");
  messageBoxOkText.setCharacterSize(20);
  messageBoxOkText.setFillColor(sf::Color::White);
  sf::FloatRect textBounds = messageBoxOkText.getLocalBounds();
  messageBoxOkText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                             textBounds.top + textBounds.height / 2.0f);
  messageBoxOkText.setPosition(messageBoxOkButton.getPosition());
}

void Game::setupPlayers(int numberOfPlayers) {
  players.clear();
  playerTokens.clear();
  std::vector<sf::Color> colors = {sf::Color::Red,     sf::Color::Blue,
                                   sf::Color::Green,   sf::Color::Yellow,
                                   sf::Color::Magenta, sf::Color::Cyan};
  for (int i = 0; i < numberOfPlayers; ++i) {
    players.emplace_back();
    sf::CircleShape token(15.f);
    token.setFillColor(colors[i % colors.size()]);
    token.setOutlineThickness(2.f);
    token.setOutlineColor(sf::Color::Black);
    token.setOrigin(token.getRadius(), token.getRadius());
    token.setPosition(getPositionOnScreen(players[i].GetPosition()));
    playerTokens.push_back(token);
  }
  currentPlayerIndex = 0;
  updatePlayerTokens();
}

void Game::updateGameBackground() {
  if (gameBackgroundTexture.getSize().x == 0 ||
      gameBackgroundTexture.getSize().y == 0) {
    return;
  }

  sf::Vector2u windowSize = gameWindow.getSize();
  sf::Vector2u textureSize = gameBackgroundTexture.getSize();
  float winWidth = static_cast<float>(windowSize.x);
  float winHeight = static_cast<float>(windowSize.y);
  float texWidth = static_cast<float>(textureSize.x);
  float texHeight = static_cast<float>(textureSize.y);

  float scale = std::min(winWidth / texWidth, winHeight / texHeight);
  gameBackgroundSprite.setScale(scale, scale);

  sf::FloatRect spriteBounds = gameBackgroundSprite.getGlobalBounds();
  float posX = (winWidth - spriteBounds.width) / 2.0f;
  float posY = (winHeight - spriteBounds.height) / 2.0f;
  gameBackgroundSprite.setPosition(posX, posY);
}

sf::Vector2f Game::getPositionOnScreen(int boardPosition) {
  if (!IsPositionValid(boardPosition)) {
    std::cerr << "ОШИБКА: Неверная позиция на поле запрошенная: "
              << boardPosition << std::endl;
    return {gameWindow.getSize().x / 2.0f, gameWindow.getSize().y / 2.0f};
  }

  const Streets::Streets &cell = gameBoard.board[boardPosition];

  float screenX = static_cast<float>(cell.getPosX());
  float screenY = static_cast<float>(cell.getPosY());

  return {screenX, screenY};
}

Game::GameAction Game::run() {
  while (gameWindow.isOpen()) {
    handleEvents();
    updateUI();
    render();
  }
  if (currentState == State::Running || previousState == State::Running) {
    return GameAction::WindowClosed;
  } else {
    return GameAction::Continue;
  }
}

void Game::handleEvents() {
  sf::Event event;
  while (gameWindow.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      if (currentState == State::Running) {
        previousState = currentState;
        currentState = State::ConfirmingExit;
      } else {
        gameWindow.close();
      }
      return;
    }
    if (event.type == sf::Event::Resized) {
      sf::FloatRect visibleArea(0.f, 0.f, static_cast<float>(event.size.width),
                                static_cast<float>(event.size.height));
      gameWindow.setView(sf::View(visibleArea));
      updateGameBackground();
      setupGameUI();
      setupConfirmationUI();
      setupMessageBoxUI();
      updatePlayerTokens();
    }
    if (event.type == sf::Event::KeyPressed &&
        event.key.code == sf::Keyboard::Escape) {
      if (currentState == State::Running) {
        previousState = currentState;
        currentState = State::ConfirmingExit;
      } else if (currentState == State::ConfirmingExit) {
        currentState = previousState;
      } else if (currentState == State::DisplayingMessage) {
        currentState = previousState;
        if (!turnInProgress && !actionRequired) {
          startNextTurn();
        }
      }
    }

    switch (currentState) {
    case State::Running:
      handleGameInput(event);
      break;
    case State::ConfirmingExit:
      handleConfirmationInput(event);
      break;
    case State::DisplayingMessage:
      handleMessageBoxInput(event);
      break;
    case State::GameOver:
      break;
    }
  }
}

void Game::handleGameInput(sf::Event event) {
  if (currentState != State::Running)
    return;

  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePos =
        gameWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

    if (rollDiceButton.getGlobalBounds().contains(mousePos)) {
      int roll1 = Dice::RollDice();
      int roll2 = Dice::RollDice();
      int totalRoll = roll1 + roll2;
      bool isDouble = (roll1 == roll2);

      std::wstringstream ss;
      ss << L"Выпало: " << roll1 << L" + " << roll2 << L" = " << totalRoll
         << (isDouble ? L" (Дубль!)" : L"");
      diceResultText.setString(ss.str());

      turnInProgress = false;
      actionRequired = true;
      rollDiceButton.setFillColor(sf::Color(150, 150, 150));

      processTurn(totalRoll, isDouble);
      return;
    }

    if (showBuyButton && buyButton.getGlobalBounds().contains(mousePos)) {
      playerAction_BuyProperty();
      return;
    }

    if (showEndTurnButton &&
        endTurnButton.getGlobalBounds().contains(mousePos)) {
      playerAction_EndTurn();
      return;
    }
  }
}

void Game::handleConfirmationInput(sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePos =
        gameWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    if (yesButton.getGlobalBounds().contains(mousePos)) {
      gameWindow.close();
    } else if (noButton.getGlobalBounds().contains(mousePos)) {
      currentState = previousState;
    }
  }
}

void Game::handleMessageBoxInput(sf::Event event) {
  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePos =
        gameWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
    if (messageBoxOkButton.getGlobalBounds().contains(mousePos)) {
      State stateBeforeMessage = previousState;
      currentState = previousState;

      if (rolledDoubleCurrentMove && !players[currentPlayerIndex].IsInJail()) {
        diceResultText.setString(L"Дубль! Бросайте снова.");
        actionRequired = false;
        turnInProgress = true;
        rollDiceButton.setFillColor(sf::Color::Green);
        showBuyButton = false;
        showEndTurnButton = false;
        rolledDoubleCurrentMove = false;
      } else {
        rolledDoubleCurrentMove = false;
        if (stateBeforeMessage == State::Running) {
          if (!turnInProgress && !actionRequired) {
            startNextTurn();
          }
        }
      }
    }
  }
}

void Game::handleChanceCard() {
  Cards::Card card = chanceDeck.drawCard();
  std::wstring message = L"Вы попали на шанс!\n" + card.description;
  auto &player = players[currentPlayerIndex];

  switch (card.effect) {
  case Cards::EffectType::Move: {
    int targetPos = card.value;
    player.SetPosition(targetPos);
    message += L"\nНовая позиция: " + std::to_wstring(targetPos);
    updatePlayerTokens();
    processTurn(0, false);
    break;
  }
  case Cards::EffectType::Money: {
    int amount = card.value;
    player.EarnMoney(amount);
    message += L"\nБаланс: $" + std::to_wstring(player.GetMoney());
    break;
  }
  }

  showMessage(message, false);
}

void Game::handleCommunityChestCard() {
  Cards::Card card = communityChestDeck.drawCard();
  std::wstring message =
      L"Вы попали на общественную казну!\n" + card.description;
  auto &player = players[currentPlayerIndex];

  switch (card.effect) {
  case Cards::EffectType::Move: {
    int targetPos = card.value;
    player.SetPosition(targetPos);
    message += L"\nНовая позиция: " + std::to_wstring(targetPos);
    updatePlayerTokens();
    processTurn(0, false);
    break;
  }
  case Cards::EffectType::Money: {
    int amount = card.value;
    player.EarnMoney(amount);
    message += L"\nБаланс: $" + std::to_wstring(player.GetMoney());
    break;
  }
  }
  showMessage(message, false);
}

void Game::handleJail() {
  auto &player = players[currentPlayerIndex];
  player.GoToJail();
  updatePlayerTokens();
  showMessage(L"Вы в тюрьме! Оплатите $50 или дождитесь дубля.", false);
}

void Game::processTurn(int diceRoll, bool isDouble) {
  if (players.empty() || currentPlayerIndex >= players.size())
    return;

  rolledDoubleCurrentMove = false;

  Players::Players &currentPlayer = players[currentPlayerIndex];

  if (currentPlayer.IsInJail()) {
    currentPlayer.PayTax(50);
    currentPlayer.LeaveJail();
    updateUI();
    diceResultText.setString(
        L"Вы заплатили $50 и вышли из тюрьмы. \nБросайте кости.");
    turnInProgress = true;
    actionRequired = false;
    rollDiceButton.setFillColor(sf::Color::Green);
    consecutiveDoubles = 0;
    return;
  }

  std::wstring turnLog = diceResultText.getString();

  if (isDouble) {
    consecutiveDoubles++;
    if (consecutiveDoubles == 3) {
      turnLog += L"\n3 дубля подряд! Отправляйтесь в тюрьму!";
      handleJail();
      consecutiveDoubles = 0;
      actionRequired = false;
      showMessage(turnLog, true);
    }
    rolledDoubleCurrentMove = true;
  } else {
    consecutiveDoubles = 0;
  }

  int oldPosition = currentPlayer.GetPosition();
  currentPlayer.Move(diceRoll, gameBoard.board.size());
  int newPosition = currentPlayer.GetPosition();

  if (!IsPositionValid(newPosition)) {
    std::cerr << "ОШИБКА: Неверная новая позиция игрока: " << newPosition
              << std::endl;
    showMessage(L"Ошибка: Неверная позиция игрока! Ход прерван.", true);
    actionRequired = false;
    rolledDoubleCurrentMove = false;
    return;
  }

  turnLog += L"\nПеремещение на " + std::to_wstring(newPosition);

  if (diceRoll > 0 && newPosition < oldPosition) {
    int goMoney = 200;
    currentPlayer.EarnMoney(goMoney);
    turnLog += L"\nПройден Старт: +$" + std::to_wstring(goMoney);
    std::cout << "Игрок " << currentPlayerIndex + 1
              << " прошёл Старт, получил $" << goMoney << std::endl;
  }

  updatePlayerTokens();

  Streets::Streets &currentCell = gameBoard.board[newPosition];
  std::string cellType = currentCell.getType();
  std::string cellNameStr = currentCell.getName();
  sf::String safeCellName =
      sf::String::fromUtf8(cellNameStr.begin(), cellNameStr.end());
  turnLog += L"\nПопали на: \n" + safeCellName.toWideString();
  std::cout << "Игрок " << currentPlayerIndex + 1 << " оказался на клетке "
            << newPosition << ": " << cellNameStr << " (Тип: " << cellType
            << ")" << std::endl;

  showBuyButton = false;
  showEndTurnButton = false;
  actionRequired = false;
  turnInProgress = false;
  bool actionIsImmediatelyPending = false;

  if (cellType == "улица" || cellType == "имущество") {
    int ownerIndex = currentCell.getOwnerIndex();
    int price = currentCell.getPrice();
    int rent = currentCell.getRent();

    if (ownerIndex < 0) {
      turnLog += L"\nНичейная. Цена: $" + std::to_wstring(price);
      if (currentPlayer.GetMoney() >= price) {
        turnLog += L"\nНажмите 'Купить' или \n'Закончить ход'.";
        showBuyButton = true;
        actionIsImmediatelyPending = true;
      } else {
        turnLog += L"\nНедостаточно средств для покупки.";
      }
    } else if (ownerIndex == (currentPlayerIndex + 1)) {
      turnLog += L"\nВаша собственность.";
    } else {
      currentPlayer.PayRent(currentCell, players);
      turnLog += L"\nСобственность Игрока " + std::to_wstring(ownerIndex) +
                 L". \nРента: $" + std::to_wstring(rent);
    }
  } else if (cellType == "шанс") {
    diceResultText.setString(turnLog);
    handleChanceCard();
    return;
  } else if (cellType == "казна") {
    diceResultText.setString(turnLog);
    handleCommunityChestCard();
    return;
  } else if (cellType == "налог") {
    int taxAmount = currentCell.getRent();
    turnLog += L"\nНалог! Заплатите $" + std::to_wstring(taxAmount);
    currentPlayer.PayTax(taxAmount);
  } else if (cellType == "тюрьма" && cellNameStr == "Отправляйся в тюрьму") {
    turnLog += L"\nОтправляйтесь в тюрьму!";
    diceResultText.setString(turnLog);
    handleJail();
    consecutiveDoubles = 0;
    rolledDoubleCurrentMove = false;
    return;
  } else {
    turnLog += L"\n ";
  }

  diceResultText.setString(turnLog);

  if (actionIsImmediatelyPending) {
    actionRequired = true;
    turnInProgress = false;
    showEndTurnButton = true;
  } else if (rolledDoubleCurrentMove && !currentPlayer.IsInJail()) {
    diceResultText.setString(diceResultText.getString() +
                             L"\nДубль! Бросайте снова.");
    actionRequired = false;
    turnInProgress = true;
    rollDiceButton.setFillColor(sf::Color::Green);
    showBuyButton = false;
    showEndTurnButton = false;
  } else {
    if (currentState != State::DisplayingMessage) {
      showEndTurnButton = true;
      actionRequired = true;
      turnInProgress = false;
    }
  }
}

void Game::playerAction_BuyProperty() {
  if (!actionRequired || !showBuyButton)
    return;

  Players::Players &currentPlayer = players[currentPlayerIndex];
  int pos = currentPlayer.GetPosition();

  if (!IsPositionValid(pos))
    return;

  Streets::Streets &currentCell = gameBoard.board[pos];
  std::string cellNameStr = currentCell.getName();
  sf::String safeCellName =
      sf::String::fromUtf8(cellNameStr.begin(), cellNameStr.end());
  int price = currentCell.getPrice();

  if (currentPlayer.GetMoney() >= price) {
    currentPlayer.BuyStreet(gameBoard.board, currentPlayerIndex + 1);
    std::cout << "Игрок " << currentPlayerIndex + 1 << " купил " << cellNameStr
              << std::endl;
    diceResultText.setString(L"Вы купили: " + safeCellName.toWideString());
    showMessage(L"Вы купили: " + safeCellName.toWideString(), true);
  } else {
    diceResultText.setString(L"Не удалось купить: " +
                             safeCellName.toWideString() +
                             L" (Недостаточно средств)");
    std::cout << "Ошибка: Кнопка покупки нажата, но у игрока "
              << currentPlayerIndex + 1 << " недостаточно средств для покупки "
              << cellNameStr << std::endl;
  }

  showBuyButton = false;
  showEndTurnButton = true;
  actionRequired = true;
}

void Game::playerAction_EndTurn() {
  std::cout << "Игрок " << currentPlayerIndex + 1 << " завершил действие/ход."
            << std::endl;

  showBuyButton = false;
  showEndTurnButton = false;
  actionRequired = false;

  if (rolledDoubleCurrentMove && !players[currentPlayerIndex].IsInJail()) {
    diceResultText.setString(L"Действие завершено. Дубль! \nБросайте снова.");
    turnInProgress = true;
    rollDiceButton.setFillColor(sf::Color::Green);
    rolledDoubleCurrentMove = false;
  } else {
    rolledDoubleCurrentMove = false;
    startNextTurn();
  }
}

void Game::startNextTurn() {
  currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
  consecutiveDoubles = 0;
  rolledDoubleCurrentMove = false;

  turnInProgress = true;
  actionRequired = false;
  showBuyButton = false;
  showEndTurnButton = false;
  rollDiceButton.setFillColor(sf::Color::Green);

  updateUI();
  diceResultText.setString(L"Ваш ход! Бросайте кости.");

  std::cout << "\n--- Ход игрока " << currentPlayerIndex + 1 << " ---"
            << std::endl;
}

void Game::showMessage(const std::wstring &message, bool endTurnAfter) {
  messageBoxText.setString(message);
  sf::FloatRect textBounds = messageBoxText.getLocalBounds();
  messageBoxText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);
  messageBoxText.setPosition(messageBoxBackground.getPosition().x,
                             messageBoxBackground.getPosition().y - 20.f);

  updatePlayerTokens();
  updateUI();
  render();

  previousState = currentState;
  currentState = State::DisplayingMessage;

  if (endTurnAfter) {
    actionRequired = false;
    turnInProgress = false;
  }
}

void Game::updatePlayerTokens() {
  float baseOffsetX = -5.0f;
  float baseOffsetY = -5.0f;
  float incrementX = 10.0f;
  float incrementY = 0.0f;
  std::vector<int> playersOnCell(gameBoard.board.size(), 0);

  for (size_t i = 0; i < players.size(); ++i) {
    if (i < playerTokens.size()) {
      int pos = players[i].GetPosition();
      if (!IsPositionValid(pos)) {
        std::cerr << "ОШИБКА: Неверная позиция " << pos << " для игрока "
                  << i + 1 << " в updatePlayerTokens." << std::endl;
        continue;
      }
      sf::Vector2f screenPos = getPositionOnScreen(pos);
      float offsetX = baseOffsetX + playersOnCell[pos] * incrementX;
      float offsetY = baseOffsetY + playersOnCell[pos] * incrementY;
      playerTokens[i].setPosition(screenPos.x + offsetX, screenPos.y + offsetY);
      playersOnCell[pos]++;
    }
  }
}

void Game::updateUI() {
  if (currentState == State::Running ||
      currentState == State::DisplayingMessage) {
    if (!players.empty() && currentPlayerIndex < players.size()) {
      Players::Players &currentPlayer = players[currentPlayerIndex];
      int currentPosition = currentPlayer.GetPosition();

      if (!IsPositionValid(currentPosition)) {
        std::cerr << "ОШИБКА: Неверная позиция игрока в updateUI: "
                  << currentPosition << " для игрока " << currentPlayerIndex + 1
                  << std::endl;
        playerInfoText.setString(L"Игрок " +
                                 std::to_wstring(currentPlayerIndex + 1) +
                                 L": ОШИБКА ПОЗИЦИИ");
        turnIndicatorText.setString(L"ОШИБКА!");
        return;
      }

      Streets::Streets &currentCell = gameBoard.board[currentPosition];
      std::wstringstream piSs;

      std::string utf8CellName = currentCell.getName();
      sf::String safeCellName =
          sf::String::fromUtf8(utf8CellName.begin(), utf8CellName.end());

      piSs << L"Игрок " << (currentPlayerIndex + 1) << L": $"
           << currentPlayer.GetMoney() << L"\nПозиция: " << currentPosition
           << L"\n(" << safeCellName.toWideString() << L")";

      playerInfoText.setString(piSs.str());

      std::wstringstream turnSs;
      turnSs << L"Ход Игрока " << (currentPlayerIndex + 1);
      turnIndicatorText.setString(turnSs.str());
      sf::FloatRect turnBounds = turnIndicatorText.getLocalBounds();
      turnIndicatorText.setOrigin(turnBounds.left + turnBounds.width / 2.0f,
                                  turnBounds.top + turnBounds.height / 2.0f);
      turnIndicatorText.setPosition(gameWindow.getSize().x / 2.f, 35.f);
    }
  } else {
    playerInfoText.setString(L"");
    turnIndicatorText.setString(L"");
  }
}

void Game::render() {
  gameWindow.clear(sf::Color(200, 225, 255));
  gameWindow.draw(gameBackgroundSprite);

  if (currentState == State::Running || currentState == State::ConfirmingExit ||
      currentState == State::DisplayingMessage) {
    renderGame();
  }

  if (currentState == State::ConfirmingExit) {
    renderConfirmationUI();
  } else if (currentState == State::DisplayingMessage) {
    renderMessageBoxUI();
  }

  gameWindow.display();
}

void Game::renderGame() {
  for (const auto &token : playerTokens) {
    gameWindow.draw(token);
  }

  for (const auto &cell : gameBoard.board) {
    if (cell.getLVL() > 0) {
      sf::CircleShape levelMarker(5.f);
      levelMarker.setPosition(cell.getPosX() + 10, cell.getPosY() + 10);
      levelMarker.setFillColor(sf::Color::Red);
      gameWindow.draw(levelMarker);
    }
  }

  if (players[currentPlayerIndex].IsInJail()) {
    gameWindow.draw(jailPayButton);
    gameWindow.draw(jailPayText);
  }

  if (turnInProgress) {
    gameWindow.draw(rollDiceButton);
    gameWindow.draw(rollDiceText);
  }

  if (showBuyButton) {
    gameWindow.draw(buyButton);
    gameWindow.draw(buyText);
  }

  if (showEndTurnButton) {
    gameWindow.draw(endTurnButton);
    gameWindow.draw(endTurnText);
  }

  gameWindow.draw(diceResultText);
  gameWindow.draw(playerInfoText);
  gameWindow.draw(turnIndicatorText);
}

void Game::renderConfirmationUI() {
  gameWindow.draw(confirmationBackground);
  gameWindow.draw(confirmationText);
  gameWindow.draw(yesButton);
  gameWindow.draw(yesText);
  gameWindow.draw(noButton);
  gameWindow.draw(noText);
}

void Game::renderMessageBoxUI() {
  gameWindow.draw(messageBoxBackground);
  gameWindow.draw(messageBoxText);
  gameWindow.draw(messageBoxOkButton);
  gameWindow.draw(messageBoxOkText);
}
