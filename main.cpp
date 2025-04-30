#include <iostream>
#include "Players/Dice.hpp"
#include "Players/GameLogic.hpp"
#include "Players/Player.hpp"
#include "Board/Board.hpp"
#include "Board/Cards.hpp"
#include "Board/Cells.hpp"

int main () {
    Players::Players* players=new Players::Players[3];
    Board::Board test;
    int size=3;
    for(int i=0;i<size;++i){
        players[i].Print();
    }

    players[0].Move(Dice::RollDice());
    players[0].Print();
    players[0].BuyStreet(test.board,0);
    players[0].Print();
    test.printBoard();

    std::cout<<Dice::RollDice()<<std::endl;
    Players::Players::DeletePlayers(players);
    return 0;
}
