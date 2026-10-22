#ifndef  MAINRPG_H
#define  MAINRPG_H
#include <vector>
#include <string>
#include <iostream>

class Entity{
private:
    std::string name_;
    int hp_; // hp_ é um atributo
    bool dead_;
    int initiative_;
public:
    Entity(std::string name, int hp,int initiative);

    virtual ~Entity() {}

    std::string getName() const;
    int getHP() const;
    bool isDead() const;
    int getInitiative() const;

    void takeDamage(int quantity);
    virtual void act(int currentTurn) = 0;
    bool operator<(const Entity& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Entity& entity);

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

class Monster: public Entity{
private:
    std::string loot_;
    int quantity_;
    int concedXP_;
public:
    Monster(std::string name,std::string loot, int hp, int initiative, int quantity, int concedXP);

    std::string getLoot() const;
    int getConcedXP() const;
};

class Boss: public Monster {
public:
    Boss(std::string name, std::string loot, int hp,int initiative, int quantity, int concedXP);
    void act(int currentTurn) override;
};

class Minion: public Monster {
public:
    Minion(std::string name, std::string loot,int initiative, int hp, int quantity,int concedXP);
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