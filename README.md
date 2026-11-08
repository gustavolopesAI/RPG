# RPG por turnos - POO

Trabalho da disciplina de Programacao Orientada a Objetos (UEL).
Simulador de RPG no terminal feito em C++, seguindo o Cenario 6.

## Como funciona

- O jogo cria 3 ou 4 jogadores (Crusader, Barbarian ou Necromancer, raca Human, Dwarf ou Elf), 1 Boss e alguns minions.
- Os nomes vem do arquivo `names.xml`.
- A cada turno todo mundo rola iniciativa e age na ordem.
- A cada 2 turnos aparecem novos monstros.
- No turno 5 aparece o assistente.
- Quando um monstro morre o jogador ganha XP e o loot.
- A simulacao acaba quando algum jogador morre.

## Classes

- `Entity` (classe base abstrata)
- `Player`, `Monster` e `Assistant` herdam de `Entity`
- `Boss` e `Minion` herdam de `Monster`
- `Dice` para os dados e `Turn` para contar os turnos

## Arquivos

- `mainRPG.h` - declaracao das classes
- `main.cpp` - loop principal
- `game.cpp` - criacao dos personagens e funcoes do jogo
- `entity.cpp`, `player.cpp`, `enemies.cpp`, `assistant.cpp` - classes
- `dice.cpp`, `turn.cpp`, `loot.cpp`, `xmlreader.cpp`
- `names.xml` - nomes dos personagens

## Como compilar

```
g++ *.cpp -o rpg
./rpg
```

## Autor

Gustavo Lopes Silva
