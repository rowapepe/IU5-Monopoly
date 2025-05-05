#include <iostream>
#include "Players/Dice.hpp"
#include "Players/GameLogic.hpp"
#include "Players/Player.hpp"
#include "Board/Board.hpp"
#include "Board/Cards.hpp"
#include "Board/Cells.hpp"

int main () {
    std::vector<Players::Players> players(3);

    Board::Board test;

    for(int i=0;i<players.size();++i){
        players[i].Print();
    }

    players[0].Move(Dice::RollDice());
    players[0].Print();
    players[0].BuyStreet(test.board,0);
    players[0].Print();
    test.printBoard();

    std::cout<<Dice::RollDice()<<std::endl;
    
    return 0;
}
