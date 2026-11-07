#include "mainRPG.h"

Assistant::Assistant(std::string name, int hp, int initiative)
    : Entity(name, hp, initiative), alreadyAppeared_(false) {}

void Assistant::act(int currentTurn, std::vector<Entity*>& all, Dice& dice) {
    if (isDead()) return;

    // Primeira vez que age: habilidade fixa de entrada (10 de dano em todos os monstros)
    if (!alreadyAppeared_) {
        alreadyAppeared_ = true;
        std::cout << "Assistant: " << getName() << " aparece no turno " << currentTurn
                << " e usa 'Luz Celestial', causando 10 de dano em todos os monstros.\n";
        for (Entity* e : all) {
            Monster* m = dynamic_cast<Monster*>(e);
            if (m != nullptr && !m->isDead()) {
                m->takeDamage(10);
                if (m->isDead()) {
                    std::cout << "Foe: " << m->getName() << " foi eliminado.\n";
                    distributeLoot(m, nullptr, all);
                }
            }
        }
        return;
    }

    // Depois: habilidade aleatoria (1 = ataca, 2 = nao faz nada)
    if (dice.roll(2) == 1) {
        Monster* target = randomAliveMonster(all, dice);
        if (target == nullptr) return;
        int damage = dice.roll(2, 8);
        target->takeDamage(damage);
        std::cout << "Assistant: " << getName() << " usa 'Espada do Julgamento' em "
                << target->getName() << " e causa " << damage << " de dano.\n";
        if (target->isDead()) {
            std::cout << "Foe: " << target->getName() << " foi eliminado.\n";
            distributeLoot(target, nullptr, all);
        }
    } else {
        std::cout << "Assistant: " << getName() << " observa a batalha.\n";
    }
}
