#include "Player.hpp"
namespace Players{
Players::Players():index(0),money(15000),position(0){}
Players::Players(int index, int money, int position):index(index),money(money),position(position){}
void Players::Move(int steps){
    position=(position+steps);
}
void Players::SetPos(int ind){
    index=ind;
}
void Players::Print(){
    std::cout<<index<<" "<<money<<" "<<position<<std::endl;
}
void Players::DeletePlayers(Players*& players){
    if(players){
        delete[] players;
        players=nullptr;
    }
}

}
