#include <iostream>
#include "Players/Dice.hpp"
#include "Players/GameLogic.hpp"
#include "Players/Player.hpp"

int main () {
    Players::Players* players=new Players::Players[3];
    int size=3;
    for(int i=0;i<size;++i){
        players[i].SetPos(i);
    }
    for(int i=0;i<size;++i){
        players[i].Print();
    }

    players[0].Move(Dice::RollDice());
    players[0].Print();
    std::cout<<Dice::RollDice()<<std::endl;
    Players::Players::DeletePlayers(players);
    return 0;
}
