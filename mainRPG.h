#ifndef  MAINRPG_H
#define  MAINRPG_H
#include <vector>
#include <string>
#include <iostream>
#include <random>

class Dice{
private:
    std::mt19937 generator_;
public:
    Dice();
    int roll(int faces);               // 1 dado: roll(20) = 1d20
    int roll(int quantity, int faces); // sobrecarga: roll(2, 6) = 2d6
};

class Entity{
private:
    std::string name_;
    int hp_; // hp_ é um atributo
    bool dead_;
    int initiative_;
    int turnInitiative_; //iniciativa sorteada no turno atual 
public:
    Entity(std::string name, int hp,int initiative);
    virtual ~Entity() {}

    std::string getName() const;
    int getHP() const;
    bool isDead() const;
    int getInitiative() const;
    int getTurnInitiative() const;

    void takeDamage(int quantity);
    void rollInitiative(Dice& dice);
    virtual void act(int currentTurn, std::vector<Entity*>* all, Dice& dice) = 0;
    
    bool operator<(const Entity* other) const;
    friend std::ostream& operator<<(std::ostream& out, const Entity& entity);
};

class Player: public Entity{
private:
    std::string characterClass_;
    std::string race_;
    int xp_;
    int equipamentsLimit_;
    std::vector<std::string> equipaments_;
    bool bonusReceived_;
    int strength_;
    int dexterity_;
    int constitution_;
    int wisdows_;
    int intelligence_;
    int charisma_;
public:
    Player(std::string name, std::string characterClass, std::string race, int hp, int initiative);

    std::string getCharacterClass() const;  
    std::string getRace() const;  
    int getXP() const;   
    bool equipItens(std::string itemName);
    void gainXP(int quantity);
    std::vector<std::string> card() const;
    void act(int currentTurn, std::vector<Entity*>& all, Dice& dice) override;   
};

class Monster: public Entity{
private:
    std::string loot_;
    int quantity_;
    int concedXP_;
public:
    Monster(std::string name,std::string loot, int hp, int initiative, int quantity, int concedXP);

    std::string getLoot() const;
    int getQuantity() const;
    int getConcedXP() const;
};

class Boss: public Monster {
public:
    Boss(std::string name, std::string loot, int hp,int initiative, int quantity, int concedXP);
    void act(int currentTurn, std::vector<Entity*>& all, Dice& dice) override;
};

class Minion: public Monster {
public:
    Minion(std::string name, std::string loot,int hp, int initiative, int quantity,int concedXP);
    void act(int currentTurn, std::vector<Entity*>& all, Dice& dice) override;
};

class Assistant: public Entity{
private:
    bool alreadyAppeared_;
public:
    Assistant(std::string name, int hp,int initiative);
    void act(int currentTurn, std::vector<Entity*>& all, Dice& dice) override;
};

class Turn {
private:
    int turnNumber_;
public:
    Turn();
    int getNumber() const;
    void  registerTurn();
    void  showResume(const std::vector<Entity*>& all) const;
};

// Sorteio de alvos(entity.cpp) e loot(loot.cpp)
Player* randomAlivePlayer(std::vector<Entity*>& all, Dice& dice);
Monster* randomAliveMonster(std::vector<Entity*>& all, Dice& dice);
void distributeLoot(Monster* monster, Player* killer, std::vector<Entity*>& all);


// Leitura do XML (xmlreader.cpp)
std::vector<std::string> readXML(std::string fileName, std::string tag);
std::string drawName(std::vector<std::string>& names, Dice& dice, std::string fallback);



// Funcoes usadas pelo (game.cpp)
std::vector<Entity*> createCharacters(std::string xmlFile, Dice& dice);
void printStats(const std::vector<Entity*>& characters);
void addNewCharacters(int currentTurn, std::vector<Entity*>& characters, Dice& dice);
void sortByInitiative(std::vector<Entity*>& characters, Dice& dice);
bool playerEliminated(const std::vector<Entity*>& characters);


#endif //MAINRPG_H