#include "Player.hpp"
namespace Players{
Players::Players():bankrupt(0),money(15000),position(0){}
Players::Players(int bankrupt, int money, int position):bankrupt(bankrupt),money(money),position(position){}
void Players::Move(int steps){
    position=(position+steps);
}

void Players::BuyStreet(std::vector<Streets::Streets>& board,int index){
    if(board[position].getOwnerIndex()==index){
        std::cout<<"Уже куплена вами";
        return;
    }
    if(board[position].getOwnerIndex()==-1){
        if(board[position].getPrice()<money){
           board[position].setOwnerIndex(index);
           money=money-board[position].getPrice();
        }else{
            std::cout<<"Недостаточно денег";

        }
    }else{
        std::cout<<"Улица куплена";
    }

}
void Players::Print(){
    std::cout<<bankrupt<<" "<<money<<" "<<position<<std::endl;
}
void Players::DeletePlayers(Players*& players){
    if(players){
        delete[] players;
        players=nullptr;
    }
}

}
