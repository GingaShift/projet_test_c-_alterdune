#include "systems/CsvLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Charge un fichier CSV complet
std::vector<CsvRow> CsvLoader::load(const std::string& filepath) {
    std::vector<CsvRow> rows;

    // Ouverture du fichier
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier : " + filepath);
    }

    std::string line;
    std::vector<std::string> headers;

    // Lecture de la première ligne = les en-têtes (noms des colonnes)
    if (std::getline(file, line)) {
        headers = splitLine(line, ';');
        for (auto& h : headers) h = trim(h);
    }
    else {
        throw std::runtime_error("Fichier CSV vide : " + filepath);
    }

    // Lecture des lignes suivantes = les données
    int lineNumber = 1;
    while (std::getline(file, line)) {
        lineNumber++;

        // Ignore les lignes vides
        if (trim(line).empty()) continue;

        std::vector<std::string> values = splitLine(line, ';');

        // Vérifie que le nombre de colonnes correspond aux en-têtes
        if (values.size() != headers.size()) {
            throw std::runtime_error(
                "Ligne " + std::to_string(lineNumber) +
                " mal formee dans : " + filepath
            );
        }

        // Construit la map colonne → valeur pour cette ligne
        CsvRow row;
        for (int i = 0; i < (int)headers.size(); i++) {
            row[headers[i]] = trim(values[i]);
        }
        rows.push_back(row);
    }

    file.close();
    return rows;
}

// Découpe une ligne selon le séparateur
std::vector<std::string> CsvLoader::splitLine(const std::string& line, char separator) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, separator)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Supprime les espaces en début et fin de chaîne
std::string CsvLoader::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");

    if (start == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}