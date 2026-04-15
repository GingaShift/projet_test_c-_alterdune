#include "systems/ActCatalog.h"
#include <iostream>
#include <stdexcept>

// Constructeur : définit toutes les actions ACT du jeu
// Format : ActId, texte humoristique, impact sur la jauge mercy
ActCatalog::ActCatalog() {
    catalog.emplace(ActId::CHECK,
        Act(ActId::CHECK,
            "Tu inspectes le monstre. Il a l'air mal a l'aise.",
            0));   // CHECK n'affecte pas la mercy

    catalog.emplace(ActId::TALK,
        Act(ActId::TALK,
            "Tu engages la conversation. C'est plutot agreable.",
            20));  // +20 mercy

    catalog.emplace(ActId::FLIRT,
        Act(ActId::FLIRT,
            "Tu fais les yeux doux. Le monstre rougit etrangement.",
            15));  // +15 mercy

    catalog.emplace(ActId::THREATEN,
        Act(ActId::THREATEN,
            "Tu brandis un poing menaçant. Pas tres diplomate.",
            -10)); // -10 mercy

    catalog.emplace(ActId::SINGG,
        Act(ActId::SINGG,
            "Tu entonnes une melodie. Le monstre se balance doucement.",
            25));  // +25 mercy

    catalog.emplace(ActId::JOKE,
        Act(ActId::JOKE,
            "Tu racontes une blague. Le monstre ne rit pas. Awkward.",
            10));  // +10 mercy

    catalog.emplace(ActId::SPARE,
        Act(ActId::SPARE,
            "Tu proposes d'epargner le monstre.",
            0));   // SPARE est géré séparément par CombatSystem

    catalog.emplace(ActId::TAUNT,
        Act(ActId::TAUNT,
            "Tu provoques le monstre. Il n'apprecie pas du tout.",
            -15)); // -15 mercy

    catalog.emplace(ActId::COMPLIMENT,
        Act(ActId::COMPLIMENT,
            "Tu complimentes le monstre. Il semble touche.",
            20));  // +20 mercy

    catalog.emplace(ActId::INSULT,
        Act(ActId::INSULT,
            "Tu insultes le monstre. Vraiment pas malin.",
            -20)); // -20 mercy
}

// Retourne un Act par son identifiant
const Act& ActCatalog::getAct(ActId id) const {
    auto it = catalog.find(id);
    if (it == catalog.end()) {
        throw std::runtime_error("ActId introuvable dans le catalogue.");
    }
    return it->second;
}

// Retourne les actions disponibles selon la catégorie
// NORMAL   → CHECK, TALK
// MINIBOSS → CHECK, TALK, FLIRT
// BOSS     → CHECK, TALK, FLIRT, CHANT
std::vector<ActId> ActCatalog::getAvailableActs(MonsterCategory category) const {
    std::vector<ActId> acts;
    acts.push_back(ActId::CHECK);
    acts.push_back(ActId::TALK);

    if (category == MonsterCategory::MINIBOSS ||
        category == MonsterCategory::BOSS) {
        acts.push_back(ActId::FLIRT);
    }
    if (category == MonsterCategory::BOSS) {
        acts.push_back(ActId::SINGG);
    }
    return acts;
}

// Affiche les actions disponibles numérotées
void ActCatalog::displayAvailableActs(MonsterCategory category) const {
    std::vector<ActId> acts = getAvailableActs(category);
    for (int i = 0; i < (int)acts.size(); i++) {
        const Act& act = getAct(acts[i]);
        std::cout << "[" << i + 1 << "] " << act.getDescription() << std::endl;
    }
}

// Vérifie si un ActId existe dans le catalogue
bool ActCatalog::exists(ActId id) const {
    return catalog.find(id) != catalog.end();
}