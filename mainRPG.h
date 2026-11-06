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
    virtual void act(int currentTurn) = 0;
    bool operator<(const Entity& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Entity& entity);
    void rollInitiative(Dice& dice);
    int getTurnIniative() const;
};

class Player: public Entity{
private:
    std::string characterClass_;
    int xp_;
    int equipamentsLimit_;
    std::vector<std::string> equipaments_;
    bool bonusReceived_;
public:
    Player(std::string name, std::string characterClass, int hp, int initiative);

    std::string getCharacterClass() const;    
    int getXP() const;   
    bool equipItens(std::string itemName);
    void gainXP(int quantity);
    void act(int currentTurn)override;
    
};
int main(

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
    void act(int currentTurn) override;
};

class Minion: public Monster {
public:
    Minion(std::string name, std::string loot,int hp, int initiative, int quantity,int concedXP);
    void act(int currentTurn) override;
};

class Assistant: public Entity{
private:
    int appearanceTurn;
    bool alreadyAppeared;
public:
    Assistant(std::string name, int hp,int initiative, int appearanceTurn);

    bool canAct(int currentTurn) const;

    void act(int currentTurn) override;
};
class Turn {
private:
    int turnNumber;

public:
    Turn(int turnNumber);
    void  registerTurn();
    void  showResume() const;
};

#endif //MAINRPG_H