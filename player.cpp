#include "mainRPG.h"

// Linha da ficha com nome e numero:  "| Strength            15 |"
static std::string cardLine(std::string label, int value) {
    std::string v = std::to_string(value);
    if (v.size() < 2) v = "0" + v;
    std::string s = "| " + label;
    while (s.size() + v.size() < 24) s += " ";
    return s + v + " |";
}

// Linha da ficha so com texto:  "| Arthur (Human)         |"
static std::string cardText(std::string text) {
    std::string s = "| " + text;
    while (s.size() < 24) s += " ";
    return s + " |";
}

Player::Player(std::string name, std::string characterClass, std::string race, int hp, int initiative)
    : Entity(name, hp, initiative), characterClass_(characterClass), race_(race),
    xp_(0), equipamentsLimit_(3), bonusReceived_(false)
{
    // Valores base da classe
    if (characterClass_ == "Crusader") {
        strength_ = 14; dexterity_ = 10; constitution_ = 14;
        wisdom_ = 12; intelligence_ = 8; charisma_ = 14;
        equipamentsLimit_ = 7;
    } else if (characterClass_ == "Barbarian") {
        strength_ = 16; dexterity_ = 12; constitution_ = 15;
        wisdom_ = 10; intelligence_ = 8; charisma_ = 8;
        equipamentsLimit_ = 5;
    } else { // Necromancer
        strength_ = 8; dexterity_ = 12; constitution_ = 10;
        wisdom_ = 13; intelligence_ = 16; charisma_ = 10;
        equipamentsLimit_ = 3;
    }

    // Bonus da raca
    if (race_ == "Human") {
        strength_++; dexterity_++; constitution_++;
        wisdom_++; intelligence_++; charisma_++;
    } else if (race_ == "Dwarf") {
        constitution_ += 2; strength_ += 1;
    } else if (race_ == "Elf") {
        dexterity_ += 2; intelligence_ += 1;
    }

    equipaments_.push_back("Healing_potion");
    std::cout << "Personagem " << getName() << " criado como " << characterClass_ << " (" << race_ << ")\n";
}

std::string Player::getCharacterClass() const { return characterClass_; }
std::string Player::getRace() const { return race_; }
int Player::getXP() const { return xp_; }

bool Player::equipItens(std::string itemName) {
    if ((int)equipaments_.size() >= equipamentsLimit_) return false;
    equipaments_.push_back(itemName);
    return true;
}

void Player::gainXP(int quantity) {
    if (quantity < 0) return;
    xp_ += quantity;
}

void Player::act(int currentTurn, std::vector<Entity*>& all, Dice& dice) {
    if (isDead()) return;

    if (currentTurn == 1 && !bonusReceived_) {
        gainXP(100);
        bonusReceived_ = true;
    }

    std::string who = "Char: " + getName() + " (" + characterClass_ + ")";

    Monster* target = randomAliveMonster(all, dice);
    if (target == nullptr) return;

    // ATAQUE: d20 menor que 6 erra
    if (dice.roll(20) < 6) {
        std::cout << who << " ataca " << target->getName() << " mas falha.\n";
        return;
    }

    int bonus = (strength_ - 10) / 2;
    if (characterClass_ == "Necromancer") bonus = (intelligence_ - 10) / 2;
    int damage = dice.roll(8) + bonus;
    if (damage < 1) damage = 1;

    // HABILIDADE DA CLASSE: 25% de chance
    if (dice.roll(100) <= 25) {
        if (characterClass_ == "Crusader") {
            damage += 4;
            std::cout << who << " usa 'Golpe Sagrado' em " << target->getName()
                    << " e causa " << damage << " de dano.\n";
        } else if (characterClass_ == "Barbarian") {
            damage *= 2;
            std::cout << who << " usa 'Furia' em " << target->getName()
                    << " e causa " << damage << " de dano.\n";
        } else {
            damage += 5;
            std::cout << who << " usa 'Maldicao' em " << target->getName()
                    << " e causa " << damage << " de dano.\n";
        }
    } else {
        std::cout << who << " ataca " << target->getName() << " e causa " << damage << " de dano.\n";
    }

    target->takeDamage(damage);

    if (target->isDead()) {
        std::cout << "Foe: " << target->getName() << " foi eliminado.\n";
        gainXP(target->getConcedXP());
        distributeLoot(target, this, all);
    }
}

std::vector<std::string> Player::card() const {
    std::string border = "+------------------------+";
    std::vector<std::string> c;
    c.push_back(border);
    c.push_back(cardText(getName() + " (" + race_ + ")"));
    c.push_back(cardText(characterClass_));
    c.push_back(border);
    c.push_back(cardLine("Strength", strength_));
    c.push_back(cardLine("Dexterity", dexterity_));
    c.push_back(cardLine("Constitution", constitution_));
    c.push_back(cardLine("Wisdom", wisdom_));
    c.push_back(cardLine("Intelligence", intelligence_));
    c.push_back(cardLine("Charisma", charisma_));
    c.push_back(cardText(""));
    c.push_back(cardLine("XP", xp_));
    c.push_back(cardLine("HP", getHP()));
    c.push_back(cardText("Equipment: " + std::to_string(equipaments_.size()) + "/" + std::to_string(equipamentsLimit_)));
    c.push_back(border);
    return c;
}
