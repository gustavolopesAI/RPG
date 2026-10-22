#include "mainRPG.h"
Monster::Monster(std::string name,std::string loot, int hp, int initiative, int quantity, int concedXP)
   : Entity(name,hp,initiative),loot_(loot),quantity_(quantity),concedXP_(concedXP)


std::string Monster::getLoot() const; {return loot_;}
int Monster::getConcedXP() const; {return xp_}


