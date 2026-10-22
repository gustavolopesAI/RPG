#include "mainRPG.h"
#include <iostream>

Entity::Entity(std::string name, int hp, int initiative)
    : name_(name), hp_(hp), dead_(false), initiative_(initiative) {} 

    /* hp_(hp) hp_ é um atributo e hp é um parâmetro
ou seja, "Inicialize um atributo hp_ 
com o valor do parâmetro hp" */ 

std::string Entity::getName() const { return name_; }
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

bool Entity::operator<(const Entity& other) const {return initiative_ < other.initiative_;}

   /* operator< (o nome especial que define o comportamento de <)
   
   const Entity& other (o objeto do lado direito de <.
   Ele é passado por referência & para não fazer cópia,
   e é const para não ser alterado)
   
   const no final (Diz que a função não altera o objeto do lado esquerdo (this))

   initiative_  <  other.initiative_ (Uma entidade é menor que outra se tiver
   iniciativa menor)
   */

std::ostream& operator<<(std::ostream& out, const Entity& entity) {
    out << entity.name_ << " (HP: " << entity.hp_
        << ", Iniciativa: " << entity.initiative_ << ")";
    return out;
}
