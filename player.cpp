#include "mainRPG.h"


Player::Player(std::string name, std::string characterClass, int hp, int initiative)
    : Entity(name, hp, initiative), characterClass_(characterClass), xp_(0), equipamentsLimit_(3), bonusReceived_(false)
{
    if (name_ == "Diablo")
    if(characterClass_ == "Crusader" )
        equipamentsLimit_ = 7;
    else if (characterClass_ == "Barbarian")
        equipamentsLimit_ = 5;
    /* Redundancia : else if (characterClass_ == "Necromancer")
        equipamentsLimit_  = 3; */

    equipaments_.push_back("Healing_potion");

    std::cout << "Personagem " << getName() << " criado como " << characterClass_ << "\n";
}
std::string Player::getCharacterClass() const {return characterClass_; }
int Player::getXP() const{return xp_;}

bool Player::equipItens(std::string itemName) {
    if ((int)equipaments_.size() >= (int)equipamentsLimit_) return false; 
    equipaments_.push_back(itemName);
    return true;
}

void Player::gainXP(int quantity) {
    if(quantity < 0) return;
    xp_ += quantity; 
}

void Player::act(int currentTurn){
    if(isDead()) return;
    if (currentTurn == 1 && !bonusReceived_){
        gainXP(100);
        bonusReceived_ = true;
    }
}







