#include "mainRPG.h"

Dice::Dice() :generator_(std::random_device{}()) {} // semente aleatória, criada uma única vez

int Dice::roll(int faces){
    std::uniform_int_distribution<int> distribution(1, faces);
    return distribution(generator_);
}

int Dice::roll(int quantity, int faces){
    int total = 0;
    for (int i = 0; i < quantity; i++) total += roll(faces);
    return total;
}