#include "model/Act.h"
#include <iostream>

// Constructeur
Act::Act(ActId id, const std::string& description, int mercyImpact)
    : id(id), description(description), mercyImpact(mercyImpact) {
}

// Getters
ActId Act::getId() const { return id; }
std::string Act::getDescription() const { return description; }
int Act::getMercyImpact() const { return mercyImpact; }

// Affiche l'action dans la console
void Act::display() const {
    std::cout << "* " << description << std::endl;
}