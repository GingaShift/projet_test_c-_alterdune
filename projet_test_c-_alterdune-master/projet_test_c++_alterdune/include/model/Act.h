#pragma once
#include "model/enums.h"
#include <string>

class Act {
public:
    Act(ActId id, const std::string& description, int mercyImpact);

    ActId getId() const;
    std::string getDescription() const;
    int getMercyImpact() const;

    void display() const;

private:
    ActId id;               // Identifiant de l'action (CHECK, TALK, FLIRT...)
    std::string description; // Texte humoristique affiché en combat
    int mercyImpact;        // Valeur ajoutée à la jauge mercy du monstre
};
