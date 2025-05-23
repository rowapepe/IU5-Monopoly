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
  showRollDiceButton = true;
  showBuyButton = false;
  showEndTurnButton = false;
  showBuildHouseButton = false;

  showPayButton = false;
  amountDueForPayment = 0;
  currentPaymentContext = PaymentContext::None;
  rentRecipientPlayerIndex = -1;

  rollDiceButton.setFillColor(sf::Color::Green);
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

  if (!markerTexture.loadFromFile("../assets/home.jpg")) {
    std::cerr << "Не удалось загрузить фон assets/home.jpg!" << std::endl;
  } else {
    markerTexture.setSmooth(true);
    markerSprite.setTexture(markerTexture);
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
  buyButton.setPosition(50, buttonY - 180);
  buyText.setFont(gameFont);
  buyText.setString(L"Купить");
  buyText.setCharacterSize(20);
  buyText.setFillColor(sf::Color::White);
  textBounds = buyText.getLocalBounds();
  buyText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                    textBounds.top + textBounds.height / 2.0f);
  buyText.setPosition(buyButton.getPosition().x + buyButton.getSize().x / 2.0f,
                      buyButton.getPosition().y + buyButton.getSize().y / 2.0f);

  sellButton.setSize({150, 50});
  sellButton.setFillColor(sf::Color::Magenta);
  sellButton.setPosition(windowSize.x - 230.f, buttonY - 180.f);
  sellText.setFont(gameFont);
  sellText.setString(L"Продать");
  sellText.setCharacterSize(20);
  sf::FloatRect textBoundsSell = sellText.getLocalBounds();
  sellText.setOrigin(textBoundsSell.left + textBoundsSell.width / 2.0f,
                     textBoundsSell.top + textBoundsSell.height / 2.0f);
  sellText.setPosition(
      sellButton.getPosition().x + sellButton.getSize().x / 2.0f,
      sellButton.getPosition().y + sellButton.getSize().y / 2.0f);

  endTurnButton.setSize({180, 50});
  endTurnButton.setFillColor(sf::Color::Red);
  endTurnButton.setPosition(50, buttonY - 120);
  endTurnText.setFont(gameFont);
  endTurnText.setString(L"Закончить ход");
  endTurnText.setCharacterSize(20);
  endTurnText.setFillColor(sf::Color::White);
  sf::FloatRect endTurnTextBounds = endTurnText.getLocalBounds();
  endTurnText.setOrigin(endTurnTextBounds.left + endTurnTextBounds.width / 2.0f,
                        endTurnTextBounds.top +
                            endTurnTextBounds.height / 2.0f);
  endTurnText.setPosition(
      endTurnButton.getPosition().x + endTurnButton.getSize().x / 2.0f,
      endTurnButton.getPosition().y + endTurnButton.getSize().y / 2.0f);

  payButton.setSize({150, 50});
  payButton.setFillColor(sf::Color(255, 165, 0));
  payButton.setPosition(50, buttonY - 240);
  payButtonText.setFont(gameFont);
  payButtonText.setString(L"Оплатить");
  payButtonText.setCharacterSize(20);
  payButtonText.setFillColor(sf::Color::Black);
  sf::FloatRect textBoundsPay = payButtonText.getLocalBounds();
  payButtonText.setOrigin(textBoundsPay.left + textBoundsPay.width / 2.0f,
                          textBoundsPay.top + textBoundsPay.height / 2.0f);
  payButtonText.setPosition(
      payButton.getPosition().x + payButton.getSize().x / 2.0f,
      payButton.getPosition().y + payButton.getSize().y / 2.0f);

  buildHouseButton.setFillColor(sf::Color::Cyan);
  buildHouseButtonText.setString(L"Построить дом");
  buildHouseButtonText.setFillColor(sf::Color::Black);
  buildHouseButton.setSize({180, 50});
  buildHouseButton.setPosition(windowSize.x - 230.f, buttonY - 300);
  buildHouseButtonText.setFont(gameFont);
  buildHouseButtonText.setCharacterSize(20);
  sf::FloatRect textBoundsBuild = buildHouseButtonText.getLocalBounds();
  buildHouseButtonText.setOrigin(
      textBoundsBuild.left + textBoundsBuild.width / 2.0f,
      textBoundsBuild.top + textBoundsBuild.height / 2.0f);
  buildHouseButtonText.setPosition(
      buildHouseButton.getPosition().x + buildHouseButton.getSize().x / 2.0f,
      buildHouseButton.getPosition().y + buildHouseButton.getSize().y / 2.0f);

  sellHouseButton.setFillColor(sf::Color::Red);
  sellHouseButtonText.setString(L"Продать дом");
  sellHouseButtonText.setFillColor(sf::Color::White);
  sellHouseButton.setSize({180, 50});
  sellHouseButton.setPosition(windowSize.x - 230.f, buttonY - 240);
  sellHouseButtonText.setFont(gameFont);
  sellHouseButtonText.setCharacterSize(20);
  sf::FloatRect textBoundsSellHouse = sellHouseButtonText.getLocalBounds();
  sellHouseButtonText.setOrigin(
      textBoundsSellHouse.left + textBoundsSellHouse.width / 2.0f,
      textBoundsSellHouse.top + textBoundsSellHouse.height / 2.0f);
  sellHouseButtonText.setPosition(
      sellHouseButton.getPosition().x + sellHouseButton.getSize().x / 2.0f,
      sellHouseButton.getPosition().y + sellHouseButton.getSize().y / 2.0f);

  payAmountText.setFont(gameFont);
  payAmountText.setCharacterSize(18);
  payAmountText.setFillColor(sf::Color::Black);
  payAmountText.setPosition(payButton.getSize().x / 2.0f - 5.f,
                            payButton.getPosition().y +
                                payButton.getSize().y / 2.0f + 30.f);
  payAmountText.setString(L"");

  diceResultText.setFont(gameFont);
  diceResultText.setCharacterSize(18);
  diceResultText.setFillColor(sf::Color::Black);
  diceResultText.setPosition(0, rollDiceButton.getPosition().y / 3.0f);
  diceResultText.setString(L"");

  playerInfoText.setFont(gameFont);
  playerInfoText.setCharacterSize(18);
  playerInfoText.setFillColor(sf::Color::Black);
  playerInfoText.setPosition(windowSize.x - 230.f,
                             rollDiceButton.getPosition().y / 2.0f);
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

  markerText.setFont(gameFont);
  markerText.setCharacterSize(14);
  markerText.setFillColor(sf::Color::Black);
}

void Game::setupPlayers(int numberOfPlayers) {
  players.clear();
  playerTokens.clear();
  std::vector<sf::Color> colors = {sf::Color::Red, sf::Color::Blue,
                                   sf::Color::Green, sf::Color::Yellow};
  for (int i = 0; i < numberOfPlayers; ++i) {
    players.emplace_back();
    sf::CircleShape token(15.f);
    token.setFillColor(colors[i % colors.size()]);
    token.setOutlineThickness(2.f);
    token.setOutlineColor(sf::Color::Black);
    token.setOrigin(token.getRadius(), token.getRadius());
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
  float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
  float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
  float scale = std::min(scaleX, scaleY);
  gameBackgroundSprite.setScale(scale, scale);

  sf::FloatRect spriteBounds = gameBackgroundSprite.getGlobalBounds();
  float posX = (static_cast<float>(windowSize.x) - spriteBounds.width) / 2.0f;
  float posY = (static_cast<float>(windowSize.y) - spriteBounds.height) / 2.0f;
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

  if (currentState == State::GameOver) {
    return GameAction::Continue;
  }

  return GameAction::WindowClosed;
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
      handleGameOverMessage();
      break;
    }
  }
}

void Game::handleGameOverMessage() {
  std::wstring text = L"Победитель игры:\n";
  for (int i = 0; i < players.size(); ++i) {
    if (!players[i].GetBankrupt()) {
      text += L"Игрок " + std::to_wstring(i + 1) + L"\n";
      text += L"С балансом: $" + std::to_wstring(players[i].GetMoney()) + L"\n";
    }
  }

  messageBoxText.setString(text);
  sf::FloatRect textBounds = messageBoxText.getLocalBounds();
  messageBoxText.setOrigin(textBounds.left + textBounds.width / 2.0f,
                           textBounds.top + textBounds.height / 2.0f);
  messageBoxText.setPosition(messageBoxBackground.getPosition().x,
                             messageBoxBackground.getPosition().y);

  previousState = currentState;
  currentState = State::DisplayingMessage;
}

void Game::handleGameInput(sf::Event event) {
  if (Players::Players::IsEnd(players)) {
    currentState = State::GameOver;
  }

  if (event.type == sf::Event::MouseButtonPressed &&
      event.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePos =
        gameWindow.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

    if (showRollDiceButton &&
        rollDiceButton.getGlobalBounds().contains(mousePos)) {

      if (actionRequired && !players[currentPlayerIndex].IsInJail()) {
        return;
      }

      int roll1 = Dice::RollDice();
      int roll2 = Dice::RollDice();
      int totalRoll = roll1 + roll2;
      bool isDouble = (roll1 == roll2);

      Players::Players &currentPlayer = players[currentPlayerIndex];

      if (currentPaymentContext != PaymentContext::JailFee) {
        showPayButton = false;
        payAmountText.setString(L"");
      }

      if (currentPlayer.IsInJail()) {
        if (isDouble) {
          currentPlayer.LeaveJail();
          std::wstringstream ss;
          ss << L"Дубль! (" << roll1 << L"+" << roll2
             << L") Вы вышли из тюрьмы!\nДвигайтесь на " << totalRoll;
          diceResultText.setString(ss.str());

          showPayButton = false;
          currentPaymentContext = PaymentContext::None;
          payAmountText.setString(L"");

          showRollDiceButton = false;
          processTurn(totalRoll, false);
        } else {
          std::wstringstream ss;
          ss << L"Не дубль (" << roll1 << L"+" << roll2
             << L"). Остаетесь в тюрьме.";
          diceResultText.setString(ss.str());
          showRollDiceButton = false;
          showPayButton = true;
          actionRequired = true;
          turnInProgress = false;
          showEndTurnButton = true;
        }
      } else {
        std::wstringstream ss;
        ss << L"Выпало: " << roll1 << L" + " << roll2 << L" = " << totalRoll
           << (isDouble ? L" (Дубль!)" : L"");
        diceResultText.setString(ss.str());

        processTurn(totalRoll, isDouble);
      }
      return;
    }

    if (showBuyButton && buyButton.getGlobalBounds().contains(mousePos)) {
      playerAction_BuyProperty();
      return;
    }

    if (showSellButton && sellButton.getGlobalBounds().contains(mousePos)) {
      playerAction_SellProperty();
      return;
    }

    if (showEndTurnButton &&
        endTurnButton.getGlobalBounds().contains(mousePos)) {
      playerAction_EndTurn();
      return;
    }

    if (showPayButton && payButton.getGlobalBounds().contains(mousePos)) {
      playerAction_PayFee();
      return;
    }

    if (showBuildHouseButton &&
        buildHouseButton.getGlobalBounds().contains(mousePos)) {
      playerAction_BuildHouse();
      return;
    }

    if (showSellHouseButton &&
        sellHouseButton.getGlobalBounds().contains(mousePos)) {
      playerAction_SellHouse();
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

      if (stateBeforeMessage == State::GameOver) {
        gameWindow.close();
      } else {
        if (rolledDoubleCurrentMove &&
            !players[currentPlayerIndex].IsInJail()) {
          diceResultText.setString(L"Дубль! Бросайте снова.");
          actionRequired = false;
          turnInProgress = true;
          showRollDiceButton = true;
          rollDiceButton.setFillColor(sf::Color::Green);
          rolledDoubleCurrentMove = false;
        } else {
          rolledDoubleCurrentMove = false;
          if (stateBeforeMessage == State::Running && !turnInProgress &&
              !actionRequired) {
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
  Players::Players &currentPlayer = players[currentPlayerIndex];
  currentPlayer.GoToJail();
  updatePlayerTokens();

  std::wstring jailMessage = L"Вы отправлены в тюрьму!";
  if (consecutiveDoubles == 3) {
    jailMessage = L"3 дубля подряд! Вы отправлены в тюрьму!";
  }

  diceResultText.setString(jailMessage);

  amountDueForPayment = 50;
  currentPaymentContext = PaymentContext::JailFee;

  actionRequired = false;
  turnInProgress = false;

  showRollDiceButton = false;
  showBuyButton = false;
  showEndTurnButton = false;
  showPayButton = false;

  consecutiveDoubles = 0;
  rolledDoubleCurrentMove = false;

  showMessage(jailMessage, false);
}

void Game::processTurn(int diceRoll, bool isDouble) {
  if (players.empty() || currentPlayerIndex >= players.size())
    return;

  rolledDoubleCurrentMove = false;
  showRollDiceButton = false;

  Players::Players &currentPlayer = players[currentPlayerIndex];

  std::wstring turnLog = diceResultText.getString();

  if (isDouble) {
    consecutiveDoubles++;
    if (consecutiveDoubles == 3) {
      handleJail();
      return;
    }
    rolledDoubleCurrentMove = true;
  } else {
    consecutiveDoubles = 0;
    rolledDoubleCurrentMove = false;
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
      std::string color = currentCell.getColor();
      bool hasAllColorStreets = currentPlayer.HasAllStreetsOfColor(
          color, gameBoard.board, currentPlayerIndex);
      if (hasAllColorStreets && currentCell.getLVL() < 5) {
        showBuildHouseButton = true;
        turnLog += L"\nНажмите 'Построить дом'";
        if (currentCell.getLVL() > 0) {
          showSellHouseButton = true;
          turnLog += L"\nили 'Продать дом'";
        }
      }
      showSellButton = true;
      turnLog += L"\nили 'Продать улицу'";
    } else {
      amountDueForPayment = rent;
      currentPaymentContext = PaymentContext::Rent;
      rentRecipientPlayerIndex = ownerIndex - 1;

      turnLog += L"\nСобственность Игрока " + std::to_wstring(ownerIndex) +
                 L". \nРента: $" + std::to_wstring(rent) +
                 L"\nНажмите 'Оплатить'.";

      payAmountText.setString(L"К оплате: $" + std::to_wstring(rent));
      showPayButton = true;
      actionIsImmediatelyPending = true;
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
    amountDueForPayment = taxAmount;
    currentPaymentContext = PaymentContext::Tax;

    turnLog += L"\nНалог! Заплатите $" + std::to_wstring(taxAmount) +
               L"\nНажмите 'Оплатить'.";

    payAmountText.setString(L"К оплате: $" + std::to_wstring(taxAmount));
    showPayButton = true;
    actionIsImmediatelyPending = true;
  } else if (cellType == "тюрьма" && cellNameStr == "Отправляйся в тюрьму") {
    handleJail();
    return;
  } else if (cellType == "тюрьма" && cellNameStr == "Тюрьма") {
    turnLog += L"\nВы просто на посещении\n тюрьмы.";
  } else if (cellType == "старт") {
    turnLog += L"\nВы на клетке Старт.";
  } else if (cellType == "бесплатная парковка") {
    turnLog += L"\nБесплатная парковка. Отдыхайте!";
  } else {
    turnLog += L"\n ";
  }

  diceResultText.setString(turnLog);

  if (showPayButton) {
    actionRequired = true;
    showRollDiceButton = false;
    showBuyButton = false;
    showEndTurnButton = false;
  } else if (actionIsImmediatelyPending && showBuyButton) {
    actionRequired = true;
    showEndTurnButton = true;
  } else if (rolledDoubleCurrentMove && !currentPlayer.IsInJail()) {
    diceResultText.setString(diceResultText.getString() +
                             L"\nДубль! Бросайте снова.");
    showRollDiceButton = true;
    rollDiceButton.setFillColor(sf::Color::Green);
    actionRequired = false;
    turnInProgress = true;
  } else {
    showRollDiceButton = false;
    if (currentState != State::DisplayingMessage && !actionRequired) {
      showEndTurnButton = true;
      actionRequired = true;
    }
  }
}

void Game::playerAction_PayFee() {
  if (!showPayButton || (amountDueForPayment <= 0 &&
                         currentPaymentContext != PaymentContext::JailFee)) {
    if (currentPaymentContext == PaymentContext::JailFee &&
        amountDueForPayment <= 0) {
      amountDueForPayment = 50;
    } else {
      return;
    }
  }

  Players::Players &currentPlayer = players[currentPlayerIndex];
  std::wstring messageToDisplay;

  if (currentPlayer.GetMoney() >= amountDueForPayment) {
    currentPlayer.PayTax(amountDueForPayment);
    bool paymentProcessedSuccessfully = true;

    switch (currentPaymentContext) {
    case PaymentContext::JailFee:
      currentPlayer.LeaveJail();
      messageToDisplay =
          L"Вы заплатили $" + std::to_wstring(amountDueForPayment) +
          L" и вышли из тюрьмы.\nТеперь бросайте кости для хода.";

      showRollDiceButton = true;
      rollDiceButton.setFillColor(sf::Color::Green);
      turnInProgress = true;
      actionRequired = false;
      break;

    case PaymentContext::Rent:
      if (rentRecipientPlayerIndex >= 0 &&
          rentRecipientPlayerIndex < static_cast<int>(players.size())) {
        players[rentRecipientPlayerIndex].EarnMoney(amountDueForPayment);
        messageToDisplay = L"Вы заплатили ренту $" +
                           std::to_wstring(amountDueForPayment) + L" Игроку " +
                           std::to_wstring(rentRecipientPlayerIndex + 1) + L".";
      } else {
        messageToDisplay = L"Ошибка: Получатель ренты не найден.";
        paymentProcessedSuccessfully = false;
      }

      if (paymentProcessedSuccessfully) {
        actionRequired = false;
        if (rolledDoubleCurrentMove && !currentPlayer.IsInJail()) {
          messageToDisplay += L"\nДубль! Бросайте снова.";
          showRollDiceButton = true;
          rollDiceButton.setFillColor(sf::Color::Green);
          turnInProgress = true;

        } else {
          rolledDoubleCurrentMove = false;
          showEndTurnButton = false;
          actionRequired = true;
          turnInProgress = false;
        }
      }
      break;

    case PaymentContext::Tax:
      messageToDisplay =
          L"Вы заплатили налог $" + std::to_wstring(amountDueForPayment) + L".";

      actionRequired = false;
      if (rolledDoubleCurrentMove && !currentPlayer.IsInJail()) {
        messageToDisplay += L"\nДубль! Бросайте снова.";
        showRollDiceButton = true;
        rollDiceButton.setFillColor(sf::Color::Green);
        turnInProgress = true;
      } else {
        rolledDoubleCurrentMove = false;
        showEndTurnButton = true;
        actionRequired = true;
        turnInProgress = false;
      }
      break;

    case PaymentContext::None:
    default:
      messageToDisplay = L"Ошибка: Неизвестный контекст для оплаты.";
      paymentProcessedSuccessfully = false;
      break;
    }

    if (paymentProcessedSuccessfully) {
      showPayButton = false;
      payAmountText.setString(L"");
      int paidAmount = amountDueForPayment;
      amountDueForPayment = 0;
      PaymentContext paidContext = currentPaymentContext;
      currentPaymentContext = PaymentContext::None;

      if (paidContext != PaymentContext::JailFee) {
        actionRequired = false;
        if (rolledDoubleCurrentMove && !currentPlayer.IsInJail()) {
          showRollDiceButton = true;
          rollDiceButton.setFillColor(sf::Color::Green);
          turnInProgress = true;
        } else {
          showEndTurnButton = true;
          actionRequired = true;
          turnInProgress = false;
        }
      }
      showEndTurnButton = false;
      showMessage(messageToDisplay, true);

    } else {
      showMessage(messageToDisplay, true);
    }

  } else {
    messageToDisplay = L"Недостаточно средств для оплаты $" +
                       std::to_wstring(amountDueForPayment) + L"!";

    showMessage(messageToDisplay, false);

    currentPlayer.SetBankrupt(true);
    playerAction_EndTurn();
  }
  updateUI();
  updatePlayerTokens();
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
  actionRequired = false;

  if (rolledDoubleCurrentMove && !currentPlayer.IsInJail()) {
    diceResultText.setString(L"Покупка совершена. Дубль! \nБросайте снова.");
    showRollDiceButton = true;
    turnInProgress = true;
    rollDiceButton.setFillColor(sf::Color::Green);
    showEndTurnButton = false;
  } else {
    showEndTurnButton = true;
    actionRequired = true;
    turnInProgress = false;
  }
}

void Game::playerAction_SellProperty() {
  if (!actionRequired || !showSellButton)
    return;

  Players::Players &currentPlayer = players[currentPlayerIndex];
  int pos = currentPlayer.GetPosition();
  if (!IsPositionValid(pos))
    return;

  Streets::Streets &currentCell = gameBoard.board[pos];
  std::string cellNameStr = currentCell.getName();
  sf::String safeCellName =
      sf::String::fromUtf8(cellNameStr.begin(), cellNameStr.end());

  if (currentCell.getOwnerIndex() != (currentPlayerIndex + 1)) {
    showMessage(L"Эта улица не ваша!", false);
    return;
  }

  if (currentCell.getLVL() > 0) {
    showMessage(L"Сначала продайте дома на этой улице!", false);
    return;
  }

  currentPlayer.SellStreet(gameBoard.board, currentPlayerIndex + 1);
  std::wstring message = L"Вы продали " + safeCellName.toWideString() +
                         L" за $" + std::to_wstring(currentCell.getPrice() / 2);
  showMessage(message, true);

  showSellButton = false;
  actionRequired = false;
  if (rolledDoubleCurrentMove && !currentPlayer.IsInJail()) {
    diceResultText.setString(L"Продажа совершена. Дубль! Бросайте снова.");
    showRollDiceButton = true;
    turnInProgress = true;
    rollDiceButton.setFillColor(sf::Color::Green);
    showEndTurnButton = false;
  } else {
    showEndTurnButton = true;
    actionRequired = true;
    turnInProgress = false;
  }
}

void Game::playerAction_BuildHouse() {
  if (!showBuildHouseButton)
    return;

  Players::Players &currentPlayer = players[currentPlayerIndex];
  int pos = currentPlayer.GetPosition();
  if (!IsPositionValid(pos))
    return;

  Streets::Streets &currentCell = gameBoard.board[pos];
  std::string cellNameStr = currentCell.getName();
  sf::String safeCellName =
      sf::String::fromUtf8(cellNameStr.begin(), cellNameStr.end());

  if (currentCell.getOwnerIndex() != (currentPlayerIndex + 1)) {
    showMessage(L"Эта улица не ваша!", false);
    return;
  }

  std::string color = currentCell.getColor();
  bool hasAllColorStreets = currentPlayer.HasAllStreetsOfColor(
      color, gameBoard.board, currentPlayerIndex);
  if (!hasAllColorStreets) {
    showMessage(L"Вы не владеете всеми улицами цвета " +
                    std::wstring(color.begin(), color.end()) + L"!",
                false);
    return;
  }

  int currentHouses = currentCell.getLVL();
  if (currentHouses == 4) {
    showMessage(L"На этой улице уже максимальное количество домов!", false);
    return;
  }

  int houseCost = currentCell.getlvlcost();
  if (currentPlayer.GetMoney() < houseCost) {
    showMessage(L"Недостаточно средств для постройки дома!", false);
    return;
  }

  currentPlayer.UpgradeStreet(gameBoard.board, currentPlayerIndex + 1);

  std::wstring message = L"Вы построили дом на " + safeCellName.toWideString() +
                         L". Теперь здесь " +
                         std::to_wstring(currentCell.getLVL()) + L" дом(а).";
  showMessage(message, true);

  updateUI();
  showBuildHouseButton = false;
}

void Game::playerAction_SellHouse() {
  if (!showSellHouseButton)
    return;

  Players::Players &currentPlayer = players[currentPlayerIndex];
  int pos = currentPlayer.GetPosition();
  if (!IsPositionValid(pos))
    return;

  Streets::Streets &currentCell = gameBoard.board[pos];
  std::string cellNameStr = currentCell.getName();
  sf::String safeCellName =
      sf::String::fromUtf8(cellNameStr.begin(), cellNameStr.end());

  if (currentCell.getOwnerIndex() != (currentPlayerIndex + 1)) {
    showMessage(L"Эта улица не ваша!", false);
    return;
  }

  if (currentCell.getLVL() == 0) {
    showMessage(L"На этой улице нет домов!", false);
    return;
  }

  std::string color = currentCell.getColor();
  bool hasAllColorStreets = currentPlayer.HasAllStreetsOfColor(
      color, gameBoard.board, currentPlayerIndex);
  if (!hasAllColorStreets) {
    showMessage(L"Вы не владеете всеми улицами цвета " +
                    std::wstring(color.begin(), color.end()) + L"!",
                false);
    return;
  }

  currentPlayer.DegradeStreet(gameBoard.board, currentPlayerIndex + 1);
  std::wstring message = L"Вы продали дом на " + safeCellName.toWideString() +
                         L". Теперь здесь " +
                         std::to_wstring(currentCell.getLVL()) + L" дом(а).";
  showMessage(message, true);

  showSellHouseButton = false;
  updateUI();
}

void Game::playerAction_EndTurn() {
  std::cout << "Игрок " << currentPlayerIndex + 1 << " завершил действие/ход."
            << std::endl;

  showBuildHouseButton = false;
  showRollDiceButton = false;
  showBuyButton = false;
  showEndTurnButton = false;
  actionRequired = false;

  if (rolledDoubleCurrentMove && !players[currentPlayerIndex].IsInJail()) {
    diceResultText.setString(L"Действие завершено. Дубль! \nБросайте снова.");
    showRollDiceButton = true;
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
  while (players[currentPlayerIndex].GetBankrupt()) {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
  }
  consecutiveDoubles = 0;
  rolledDoubleCurrentMove = false;

  showBuyButton = false;
  showEndTurnButton = false;
  showPayButton = false;
  showBuildHouseButton = false;
  showSellButton = false;
  showSellHouseButton = false;
  payAmountText.setString(L"");
  amountDueForPayment = 0;
  currentPaymentContext = PaymentContext::None;

  Players::Players &nextPlayer = players[currentPlayerIndex];

  if (nextPlayer.IsInJail()) {
    diceResultText.setString(
        L"Вы в тюрьме! Заплатите $" + std::to_wstring(50) +
        L", \nчтобы выйти, или бросайте \nкости на дубль.");
    amountDueForPayment = 50;
    currentPaymentContext = PaymentContext::JailFee;
    payAmountText.setString(L"Залог: $" + std::to_wstring(50));
    showPayButton = true;
    showRollDiceButton = true;
    rollDiceButton.setFillColor(sf::Color::Green);
    actionRequired = true;
    turnInProgress = false;
  } else {
    diceResultText.setString(L"Ваш ход! Бросайте кости.");
    showRollDiceButton = true;
    rollDiceButton.setFillColor(sf::Color::Green);
    actionRequired = false;
    turnInProgress = true;
  }

  updateUI();
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

      if (!players[i].GetBankrupt()) {
        sf::Vector2f screenPos = getPositionOnScreen(pos);
        float offsetX = baseOffsetX + playersOnCell[pos] * incrementX;
        float offsetY = baseOffsetY + playersOnCell[pos] * incrementY;
        playerTokens[i].setPosition(screenPos.x + offsetX,
                                    screenPos.y + offsetY);
      } else {
        playerTokens[i].setPosition(-1000, -1000);
      }
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

      piSs << L"Игрок " << (currentPlayerIndex + 1) << L" ("
           << colors[currentPlayerIndex] << L")" << L"\nБаланс: $"
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

  if (showPayButton && amountDueForPayment > 0) {
    if (currentPaymentContext == PaymentContext::JailFee) {
      payAmountText.setString(L"Залог: $" +
                              std::to_wstring(amountDueForPayment));
    } else {
      payAmountText.setString(L"К оплате: $" +
                              std::to_wstring(amountDueForPayment));
    }
  } else {
    payAmountText.setString(L"");
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
  for (int i = 0; i < gameBoard.board.size(); ++i) {
    auto &cell = gameBoard.board[i];
    if (cell.getLVL() > 0) {
      int x = cell.getPosX();
      int y = cell.getPosY();
      if (i > 0 && i < 10) {
        markerSprite.setPosition(x + 1, y - 28);
        markerText.setString(std::to_wstring(cell.getLVL()));
        markerText.setPosition(x - 10, y - 27);
      } else if (i > 10 && i < 20) {
        markerSprite.setPosition(x + 14, y - 31);
        markerText.setString(std::to_wstring(cell.getLVL()));
        markerText.setPosition(x + 3, y - 30);
      } else if (i > 20 && i < 30) {
        markerSprite.setPosition(x + 2, y + 7);
        markerText.setString(std::to_wstring(cell.getLVL()));
        markerText.setPosition(x - 9, y + 8);
      } else if (i > 30 && i < 40) {
        markerSprite.setPosition(x - 14, y + 2);
        markerText.setString(std::to_wstring(cell.getLVL()));
        markerText.setPosition(x - 25, y + 3);
      }
      gameWindow.draw(markerSprite);
      gameWindow.draw(markerText);
    }
  }

  std::vector<sf::Color> colors = {sf::Color::Red, sf::Color::Blue,
                                   sf::Color::Green, sf::Color::Yellow};

  for (int i = 0; i < gameBoard.board.size(); ++i) {
    auto &cell = gameBoard.board[i];
    if (cell.getOwnerIndex() != -1) {
      sf::RectangleShape rectangle(sf::Vector2f(15.f, 15.f));
      rectangle.setFillColor(colors[cell.getOwnerIndex() - 1]);
      int x = cell.getPosX();
      int y = cell.getPosY();
      if (i > 0 && i < 10) {
        rectangle.setPosition(x, y);
      } else if (i > 10 && i < 20) {
        rectangle.setPosition(x, y);

      } else if (i > 20 && i < 30) {
        rectangle.setPosition(x, y);

      } else if (i > 30 && i < 40) {
        rectangle.setPosition(x, y);
      }
      gameWindow.draw(rectangle);
    }
  }

  for (const auto &token : playerTokens) {
    gameWindow.draw(token);
  }

  if (showRollDiceButton) {
    gameWindow.draw(rollDiceButton);
    gameWindow.draw(rollDiceText);
  }

  if (showBuyButton) {
    gameWindow.draw(buyButton);
    gameWindow.draw(buyText);
  }

  if (showSellButton) {
    gameWindow.draw(sellButton);
    gameWindow.draw(sellText);
  }

  if (showEndTurnButton) {
    gameWindow.draw(endTurnButton);
    gameWindow.draw(endTurnText);
  }

  if (showPayButton) {
    gameWindow.draw(payButton);
    gameWindow.draw(payButtonText);
    gameWindow.draw(payAmountText);
  }

  if (showBuildHouseButton) {
    gameWindow.draw(buildHouseButton);
    gameWindow.draw(buildHouseButtonText);
  }

  if (showSellHouseButton) {
    gameWindow.draw(sellHouseButton);
    gameWindow.draw(sellHouseButtonText);
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
