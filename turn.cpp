#include "mainRPG.h"

Turn::Turn() : turnNumber_(0) {}

int Turn::getNumber() const { return turnNumber_; }

void Turn::registerTurn() {
    turnNumber_++;
    std::cout << "\n========== Turno " << turnNumber_ << " ==========\n";    
}

void Turn::showResume(const std::vector<Entity*>& all) const {
    std::cout << "--- Resumo do turno " << turnNumber_ << "---\n";
    for (Entity* e : all) {
        if (!e->isDead()) std::cout << "  " << *e << "\n";
    }
}

