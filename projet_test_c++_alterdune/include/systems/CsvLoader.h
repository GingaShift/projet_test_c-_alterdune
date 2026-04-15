#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

// Représente une ligne du CSV : nom_colonne → valeur
using CsvRow = std::map<std::string, std::string>;

class CsvLoader {
public:
    // Charge un fichier CSV et retourne toutes ses lignes
    // Lève une exception si le fichier est introuvable ou mal formé
    static std::vector<CsvRow> load(const std::string& filepath);

private:
    // Découpe une ligne en colonnes selon le séparateur
    static std::vector<std::string> splitLine(const std::string& line, char separator);

    // Supprime les espaces en début et fin de chaîne
    static std::string trim(const std::string& str);
};