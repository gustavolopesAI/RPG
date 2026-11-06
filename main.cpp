#include "mainRPG.h"

int main(){
    Dice dice;
    std::vector<Entity*> characters = createCharacters("names.xml", dice); // inicialize vetor de personagens
    printStats(characters);                                                // print stats dos personagens
    Turn turn;                                                             // inicialize contador de turno  
    
    do{
        turn.registerTurn();                                  // conta turno
        addNewCharacters(turn.getNumber(), characters, dice); // monstros a cada 2 turnos / assistente no 5
        sortByInitiative(characters, dice);                   // ordene por iniciativa

        for (Entity* c : characters) {                  // for each personagem
            c->act(turn.getNumber(), characters, dice); // print acao + atualizar personagens
            if (playerEliminated(characters)) break;
        }
        turn.showResume(characters);             // estado de cada personagem no fim do turno
    } while (!playerEliminated(characters));     // while nao condicao

    std::cout << "\n===== FIM DA SIMULACAO NO TURNO " << turn.getNumber() << " =====\n";
    printStats(characters);
    for (Entity* c : characters) delete c;
    return 0;
}




