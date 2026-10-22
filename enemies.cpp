#include "mainRPG.h"
//Monster
Monster::Monster(std::string name,std::string loot, int hp, int initiative, int quantity, int concedXP)
   : Entity(name,hp,initiative),loot_(loot),quantity_(quantity),concedXP_(concedXP)
{
    if (quantity_ < 0) quantity_ = 1; //O loot tem que ser ao menos 1
    if (conced_xp < 0) concedXP_ = 0; //XP não pode ser negativo
}

std::string Monster::getLoot() const {return loot_;}
int Monster::getQuantity() const {return quantity_;}
int Monster::getConcedXP() const {return concedXP_;}

//Boss
Boss::Boss(std::string name, std::string loot, int hp,int initiative, int quantity, int concedXP)
   : Monster(name, loot, hp, initiative, quantity, concedXP){

   }

void Boss::act(int currentTurn){
    if(isDead()) return;
    if (currentTurn >= 1 ){
        do something?
    }
}

//Minion 
Minion::Minion Minion(std::string name, std::string loot,int hp, int initiative, int quantity,int concedXP)
    :Monster(std::string name,std::string loot, int hp, int initiative, int quantity, int concedXP){
    
}

void Minion::act(int currentTurn){
    if(isDead()) return;
    if (currentTurn >= 1 ){
        do something?
    }
}