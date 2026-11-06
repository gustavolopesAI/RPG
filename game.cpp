#include "mainRPG.h"
#include <algorithm>

// FABRICA (padrao de criacao): monta um jogador com nome e raca sorteados
static Player* createPlayer (int classIndex, std::vector<std::string>& names, Dice& dice){
    std::string classes[3] = {"Crusader", "Barbarian", "Necromancer"};
    std::string races[3] = {"Human", "Dwarf" , "Elf" };
    int hps[3] = {100, 120, 70};
    int initiatives[3] = {15, 10, 12};

    std::string name = drawName(names , dice, "Heroi");
    std::string race = races[dice.roll(3) - 1];
    Player* p = new Player(name, classes[classIndex], race, hps[classIndex], initiatives[classIndex]);

    // Equipamento inicial de cada classe
    if (classIndex == 0) { p->equipItens("Sword"); p->equipItens("Shield"); }
    else if (classIndex == 1) p->equipItens("Battle_axe");
    else p->equipItens("Staff");

    return p;
}

// FABRICA: monta um minion de tipo sorteado 
static Minion* createRandomMinion(Dice& dice){
    static int count = 0; // numera os lacaios: Goblin 1, Esqueleto 2..
    std::string names[3] = {"Goblin", "Esqueleto", "Demonio"};
    std::string loot[3] = {"Dagger", "Bone_shield", "Demon_horn"};
    int hps[3] = {20, 25, 35};
    int initiatives[3] = {12, 8, 10};
    int xps[3] = {30, 40, 60};

    int t = dice.roll(3) - 1;
    count++;
    return new Minion(names[t] + " " + std::to_string(count), loots[t], hps[t], initiatives[t], 1, xps[t]);
}

// "inicialize vetor de personagens": jogadores, Boss e minios aleatorios
std::vector<Entity*> createCharacters(std::string xmlFile, Dice& dice){
    std::vector<Entity*> characters;
    std::vector<std::string> playerNames = readXML(xmlFile, "player");
    std::vector<std::string> bossNames = readXML(xmlFile, "boss");

    // 3 ou 4 jogadores, com pelo menos duas classes diferentes
    int playerCount = 2 + dice.roll(2);
    int firstClass = dice.roll(3) - 1;
    for (int i = 0; i < playerCount; i++){
        int c = dice.roll(3) - 1;
        if (i == 0) c = firstClass;
        if (i == 1) c = (firstClass + 1) % 3;
        characters.push_back(createPlayer(c, playerNames, dice));        
    }

    // 1 Boss (unico) + 2 ou 3 minions
    characters.push_back(new Boss(drawName(bossNames, dice, "Boss"), "Crown_of_sins", 150, 14, 1, 300));
    int minions = 1 + dice.roll(2);
    for (int i = 0; i < minions; i++) characters.push_back(createRandomMinion(dice));

    return characters;
}

// "print stats dos personagens": fichas dos jogadores lado a lado 
void printStats(const std::vector<Entity*>& characters) {
    std::vector<std::vector<std::string>> cards;
    for (Entity* e : characters) {
        Player* p = dynamic_cast<Player*>(e);
        if (p != nullptr) cards.push_back(p->card());
    }

    std::cout << "\n";
    for (int line = 0; line < (int)cards[0].size(); line++) {
        for (int i = 0; i < (int)cards.size(); i++) std::cout << cards[i][line] << " ";
        std::cout << "\n";
    }
}

// Regras do Cenario 6: monstros a cada 2 turnos e assistente no turno 5
void addNewCharacters(int currentTurn, std::vector<Entity*>& characters, Dice& dice) {
    if (currentTurn % 2 == 0){
        int wave = 1 + dice.roll(2);
        for (int i = 0; i < wave; i++){
            Minion* m = createRandomMinion(dice);
            characters.push_back(m);
            std::cout << "Um novo monstro surge: " << m->getName() << "\n";    
        }
    }

    if (currentTurn == 5) {
        std::vector<std::string> names = readXML("names.xml", "assistant");
        characters.push_back(new Assistant(drawName(names, dice, "Assistente"), 999, 20));
    }
}

// "ordene por iniciativa": sorteia a iniciativa do turno e ordena (maior primeiro)
void sortByInitiative(std::vector<Entity*>& characters, Dice& dice) {
    for (Entity* e : characters) e->rollInitiative(dice);
    std::sort(characters.begin(), characters.end(), [](Entity* a, Entity* b) { return *b < *a; });
}

// "while nao condicao": Cenario 6 termina quando um  jogador e eliminado
bool playerEliminated(const std::vector<Entity*>& characters) {
    for (Entity* e : characters) {
        Player* p = dynamic_cast<Player*>(e);
        if (p != nullptr && p->isDead()) return true;
    }
    return false;
}