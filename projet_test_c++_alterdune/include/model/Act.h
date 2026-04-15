#pragma once
#include "model/enums.h"
#include <string>

class Act {
public:
    // Constructeur
    Act(ActId id, const std::string& description, int mercyImpact);

    // Getters
    ActId getId() const;
    std::string getDescription() const;
    int getMercyImpact() const;

    // Affiche l'action dans la console
    void display() const;

private:
    ActId id;               // Identifiant de l'action (CHECK, TALK, FLIRT...)
    std::string description; // Texte humoristique affiché en combat
    int mercyImpact;        // Valeur ajoutée à la jauge mercy du monstre
};
