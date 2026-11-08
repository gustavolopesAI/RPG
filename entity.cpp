#include "mainRPG.h"
#include <iostream>

Entity::Entity(std::string name, int hp, int initiative)
    : name_(name), hp_(hp), dead_(false), initiative_(initiative), turnInitiative_(initiative) {} 

    /* hp_(hp) hp_ é um atributo e hp é um parâmetro
ou seja, "Inicialize um atributo hp_ 
com o valor do parâmetro hp" */ 

std::string Entity::getName() const { return name_; }
std::string Entity::getTitle() const { return name_; }
int Entity::getHP() const { return hp_; } 
bool Entity::isDead() const { return dead_; }
int Entity::getInitiative() const { return initiative_; }

void Entity::takeDamage(int quantity) {
    if(quantity < 0) return;
    hp_ -= quantity;
    if (hp_ <= 0) {
        hp_ = 0;
        dead_ = true;
    }
}

void Entity::rollInitiative(Dice& dice){turnInitiative_ = initiative_ + dice.roll(20); }
int Entity::getTurnInitiative() const {return turnInitiative_; }
bool Entity::operator<(const Entity& other) const {return turnInitiative_ < other.turnInitiative_;}

/* operator< (o nome especial que define o comportamento de <)

const Entity& other (o objeto do lado direito de <.
Ele é passado por referência & para não fazer cópia,
e é const para não ser alterado)

const no final (Diz que a função não altera o objeto do lado esquerdo (this))

*/

std::ostream& operator<<(std::ostream& out, const Entity& entity) {
    out << entity.getTitle() << " (HP: " << entity.hp_
        << ", Iniciativa: " << entity.turnInitiative_ << ")";
    return out;
}

//Sorteia um jogador vivo da lista
Player* randomAlivePlayer(std::vector<Entity*>& all, Dice& dice){
    std::vector<Player*> alive;
    for (Entity* e : all) {
        Player* p = dynamic_cast<Player*>(e); // vira nullptr se 'e' nao for Player
        if (p != nullptr && !p->isDead()) alive.push_back(p);
    }
    if (alive.empty()) return nullptr;
    return alive[dice.roll((int)alive.size()) - 1];
}

//Sorteia um monstro vivo da lista 
Monster* randomAliveMonster(std::vector<Entity*>& all, Dice& dice) {
    std::vector<Monster*> alive;
    for (Entity* e : all) {
        Monster* m = dynamic_cast<Monster*>(e);
        if (m != nullptr && !m->isDead()) alive.push_back(m);
    }
    if (alive.empty()) return nullptr;
    return alive[dice.roll((int)alive.size()) - 1];
}