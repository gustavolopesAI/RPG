#include "mainRPG.h"
#include <vector>

int main(){

    std::vector<Entity*> encounter;

    encounter.push_back(new Player("Arthur", "Crusader", 100, 15));
    encounter.push_back(new Player("Ragnar", "Barbarian", 120, 10));
    encounter.push_back(new Player("Morgana", "Necromancer", 70, 12));
    
    // Impressao dos atributos
    for (Entity * e : encounter){
        std::cout << *e << "\n";
    }

    // Liberar a memoria
    for (Entity * e : encounter) delete e;
    return 0;

}

