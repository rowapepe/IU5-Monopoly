#include "Player.hpp"
namespace{
const int tax=200;
}
namespace Players{
Players::Players():bankrupt(0),money(15000),position(0){}
Players::Players(int bankrupt, int money, int position):bankrupt(bankrupt),money(money),position(position){}
void Players::Move(int steps){
    position=(position+steps);
}
void Players::SellStreet( std::vector<Streets::Streets>& board,int index){
    if(board[position].getType()!="улица"){
        std::cout<<"Это не улица, нельзя купить";
        return;

    }
    if(board[position].getOwnerIndex()==-1){
        std::cout<<"Некуплена никем";
        return;
    }
    if(board[position].getOwnerIndex()==index){

        board[position].setOwnerIndex(-1);
        money=money+board[position].getPrice()*0.8;
        return;



    }else{
        std::cout<<"Улица куплена не вами";
        return;
    }

}
void Players::BuyStreet(std::vector<Streets::Streets>& board,int index){
    if(board[position].getType()!="улица"){
        std::cout<<"Это не улица, нельзя купить";
        return;

    }
    if(board[position].getOwnerIndex()==index){
        std::cout<<"Уже куплена вами";
        return;
    }
    if(board[position].getOwnerIndex()==-1){
        if(board[position].getPrice()<money){
           board[position].setOwnerIndex(index);
           money=money-board[position].getPrice();
           return;
        }else{
            std::cout<<"Недостаточно денег";
            return;

        }
    }else{
        std::cout<<"Улица куплена";
        return;
    }

}
void Players::Print(){
    std::cout<<bankrupt<<" "<<money<<" "<<position<<std::endl;
}
void Players::UpgradeStreet(std::vector<Streets::Streets>& board,int index){
    if(board[position].getType()!="улица"){
        std::cout<<"Это не улица, нельзя прокачать";
        return;

    }
    if(board[position].getLVL()==5){
        std::cout<<"Максимальный уровень";
        return;
    }
    if(board[position].getOwnerIndex()==index){
        if(board[position].getlvlcost()<money){
            board[position].setLVL(board[position].getLVL()+1);
            money=money-board[position].getlvlcost();
            return;
         }else{
             std::cout<<"Недостаточно денег";
             return;

         }
    }else{
        std::cout<<"Не ваша улица";
        return;
    }



}
void Players::DegradeStreet(std::vector<Streets::Streets>& board,int index){
    if(board[position].getType()!="улица"){
        std::cout<<"Это не улица";
        return;

    }
    if(board[position].getLVL()==0){
        std::cout<<"Минимальный уровень";
        return;
    }
    if(board[position].getOwnerIndex()==index){

        board[position].setLVL(board[position].getLVL()-1);
        money=money+board[position].getlvlcost();
        return;

    }else{
        std::cout<<"Не ваша улица";
        return;
    }
}
void Players::SetMoney(int m){
    money = m;
}
int Players::GetMoney(){
    return money;
}

void Players::PayRent(std::vector<Streets::Streets>& board,std::vector<Players> players,int index){
    if(board[position].getOwnerIndex()==-1){
        std::cout<<"Улица никому не принадлежит, не надо нчиего платить";
        return;
    }
    if(board[position].getRent()<money){
        players[board[position].getOwnerIndex()].money=players[board[position].getOwnerIndex()].money+board[position].getRent();
        money=money-board[position].getRent();
        return;

    }else{
        std::cout<<"Недостаточно средств";
        return;
    }

}
void Players::PayTax(){
    if(money<tax){
        std::cout<<"Недостаточно денег";
        return;
    }
    money=money-tax;
}
bool Players::IsEnd(std::vector<Players> players){
    int k=0;
    for(int i=0;i<players.size();++i){
        if(players[i].bankrupt==false){
            k+=1;
        }

    }
    if (k==1){
        return true
    }
    return false;

}

}
