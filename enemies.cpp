#include "mainRPG.h"
Monster::Monster(std::string name,std::string loot, int hp, int initiative, int quantity, int concedXP)
   : Entity(name,hp,initiative),loot_(loot),quantity_(quantity),concedXP_(concedXP)
{
    
    if (quantity_ < 0) quantity_ = 1; //O loot tem que ser ao menos 1
    if (conced_xp < 0) concedXP_ = 0; //XP não pode ser negativo
}



std::string Monster::getLoot() const {return loot_;}
int Monster::getConcedXP() const {return xp_;}



