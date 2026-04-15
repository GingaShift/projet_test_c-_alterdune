#pragma once
#include "model/Act.h"
#include "model/enums.h"
#include <map>
#include <vector>

class ActCatalog {
public:
    // Constructeur : remplit automatiquement le catalogue
    ActCatalog();

    // Retourne un Act par son identifiant
    const Act& getAct(ActId id) const;

    // Retourne la liste des ActId disponibles selon la catégorie du monstre
    // NORMAL = 2 actions, MINIBOSS = 3 actions, BOSS = 4 actions
    std::vector<ActId> getAvailableActs(MonsterCategory category) const;

    // Affiche toutes les actions disponibles pour une catégorie
    void displayAvailableActs(MonsterCategory category) const;

    // Vérifie si un ActId existe dans le catalogue
    bool exists(ActId id) const;

private:
    std::map<ActId, Act> catalog; // Dictionnaire ActId → Act
};