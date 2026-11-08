#include "mainRPG.h"

// Entrega o loot do monstro: primeiro para quem matou, senao para quem tiver espaco
void distributeLoot(Monster* monster, Player* killer, std::vector<Entity*>& all) {
    std::string item = monster->getLoot();

    for (int i = 0; i < monster->getQuantity(); i++) {
        Player* receiver = nullptr;

        if (killer != nullptr && !killer->isDead() && killer->equipItens(item)) {
            receiver = killer;
        } else {
            for (Entity* e : all) {
                Player* p = dynamic_cast<Player*>(e);
                if (p != nullptr && !p->isDead() && p->equipItens(item)) {
                    receiver = p;
                    break;
                }
            }
        }

        if (receiver != nullptr)
            std::cout << "Loot: " << receiver->getTitle() << " recebe " << item << ".\n";
        else
            std::cout << "Loot: ninguem tem espaco para " << item << ", o item foi perdido.\n";
    }
}