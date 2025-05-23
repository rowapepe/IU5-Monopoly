#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../Board/Board.hpp"
#include "../Players/Dice.hpp"
#include "../Players/Player.hpp"

class Game {
public:
  enum class GameAction { Continue, ReturnToMenu, WindowClosed };
  Game();
  GameAction run();

private:
  sf::RenderWindow gameWindow;
  sf::Texture gameBackgroundTexture;
  sf::Sprite gameBackgroundSprite;
  sf::Font gameFont;

  enum class State { Running, ConfirmingExit, DisplayingMessage, GameOver };
  State currentState;
  State previousState;

  bool IsPositionValid(int position) const;
  bool rolledDoubleCurrentMove;

  sf::Text confirmationText;
  sf::RectangleShape confirmationBackground;
  sf::RectangleShape yesButton, noButton;
  sf::Text yesText, noText;

  Board::Board gameBoard;
  std::vector<Players::Players> players;
  std::vector<sf::CircleShape> playerTokens;
  int currentPlayerIndex = 0;
  bool turnInProgress = false;
  bool actionRequired = false;
  int consecutiveDoubles = 0;

  sf::RectangleShape rollDiceButton;
  sf::Text rollDiceText;
  sf::RectangleShape buyButton;
  sf::Text buyText;
  sf::RectangleShape sellButton;
  sf::Text sellText;
  sf::RectangleShape endTurnButton;
  sf::Text endTurnText;
  sf::RectangleShape payButton;
  sf::Text payButtonText;
  sf::RectangleShape buildHouseButton;
  sf::Text buildHouseButtonText;
  sf::RectangleShape sellHouseButton;
  sf::Text sellHouseButtonText;

  sf::Text diceResultText;
  sf::Text playerInfoText;
  sf::Text turnIndicatorText;
  sf::Text payAmountText;

  bool showPayButton = false;
  bool showRollDiceButton = false;
  bool showBuyButton = false;
  bool showSellButton = false;
  bool showEndTurnButton = false;
  bool showBuildHouseButton = false;
  bool showSellHouseButton = false;

  sf::RectangleShape messageBoxBackground;
  sf::Text messageBoxText;
  sf::RectangleShape messageBoxOkButton;
  sf::Text messageBoxOkText;

  std::vector<std::wstring> colors = {L"Красный", L"Синий", L"Зеленый",
                                      L"Желтый"};

  Cards::Deck chanceDeck;
  Cards::Deck communityChestDeck;
  void handleChanceCard();
  void handleCommunityChestCard();

  int amountDueForPayment;
  int rentRecipientPlayerIndex;
  enum class PaymentContext { None, Rent, Tax, JailFee };
  PaymentContext currentPaymentContext;

  void loadResources();
  void setupUI();
  void setupConfirmationUI();
  void setupGameUI();
  void setupMessageBoxUI();
  void setupPlayers(int numberOfPlayers = 2);

  void updateGameBackground();
  void updatePlayerTokens();
  void updateUI();
  sf::Vector2f getPositionOnScreen(int boardPosition);
  void render();
  void renderGame();
  void renderConfirmationUI();
  void renderMessageBoxUI();

  void handleEvents();
  void handleGameInput(sf::Event event);
  void handleConfirmationInput(sf::Event event);
  void handleMessageBoxInput(sf::Event event);

  void handleJail();

  void processTurn(int diceRoll, bool isDouble);
  void startNextTurn();
  void playerAction_PayFee();
  void playerAction_BuyProperty();
  void playerAction_SellProperty();
  void playerAction_BuildHouse();
  void playerAction_SellHouse();
  void playerAction_BeBankrupt();
  void playerAction_EndTurn();
  void showMessage(const std::wstring &message, bool endTurnAfter = true);
};
