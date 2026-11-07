#include "mainRPG.h"
//Monster
Monster::Monster(std::string name,std::string loot, int hp, int initiative, int quantity, int concedXP)
    : Entity(name,hp,initiative),loot_(loot),quantity_(quantity),concedXP_(concedXP)
{
    if (quantity_ <= 0) quantity_ = 1; //O loot tem que ser ao menos 1
    if (concedXP_ < 0) concedXP_ = 0; //XP não pode ser negativo
}

std::string Monster::getLoot() const {return loot_;}
int Monster::getQuantity() const {return quantity_;}
int Monster::getConcedXP() const {return concedXP_;}

//Boss
Boss::Boss(std::string name, std::string loot, int hp,int initiative, int quantity, int concedXP)
    : Monster(name, loot, hp, initiative, quantity, concedXP){

}

void Boss::act(int currentTurn, std::vector<Entity*>& all, Dice& dice){
    if(isDead()) return;

    // ESPECIAL: a cada 3 turnos ataca todos os herois
    if (currentTurn % 3 == 0) {
        std::cout << "Foe: " << getName() << " (Boss) usa 'Chuva de Pecado' em todos os herois!\n";
        for (Entity* e : all) {
            Player* p = dynamic_cast<Player*>(e);
            if (p != nullptr && !p->isDead()) {
                int damage = dice.roll(6);
                p->takeDamage(damage);
                std::cout << "     " << p->getName() << " sofre " << damage << " de dano.\n";
                if (p->isDead()) std::cout << "Char: " << p->getName() << " foi eliminado.\n";
            }
        }
        return;
    }

    Player* target = randomAlivePlayer(all, dice);
    if (target == nullptr) return;

    if (dice.roll(20) < 6) {
        std::cout << "Foe: " << getName() << " (Boss) ataca " << target->getName() << " mas falha.\n";
        return;
    }

    int damage = dice.roll(10);
    target->takeDamage(damage);
    std::cout << "Foe: " << getName() << " (Boss) ataca " << target->getName()
            << " e causa " << damage << " de dano.\n";
    if (target->isDead()) std::cout << "Char: " << target->getName() << " foi eliminado.\n";
    
}

//Minion 
Minion::Minion(std::string name, std::string loot,int hp, int initiative, int quantity,int concedXP)
    :Monster(name, loot, hp, initiative, quantity, concedXP){
    
}

void Minion::act(int, std::vector<Entity*>& all, Dice& dice) {
    if (isDead()) return;

    Player* target = randomAlivePlayer(all, dice);
    if (target == nullptr) return;

    if (dice.roll(20) < 6) {
        std::cout << "Foe: " << getName() << " ataca " << target->getName() << " mas falha.\n";
        return;
    }

    int damage = dice.roll(6);

    // HABILIDADE: 20% de chance de usar 'Raiva' (+3 de dano)
    if (dice.roll(100) <= 20) {
        damage += 3;
        std::cout << "Foe: " << getName() << " usa 'Raiva' e ataca " << target->getName()
                << " causando " << damage << " de dano.\n";
    } else {
        std::cout << "Foe: " << getName() << " ataca " << target->getName()
                << " e causa " << damage << " de dano.\n";
    }

    target->takeDamage(damage);
    if (target->isDead()) std::cout << "Char: " << target->getName() << " foi eliminado.\n";
}
