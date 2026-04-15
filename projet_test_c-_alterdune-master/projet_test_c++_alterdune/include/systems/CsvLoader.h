#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

using CsvRow = std::map<std::string, std::string>;

class CsvLoader {
public:
    static std::vector<CsvRow> load(const std::string& filepath);

private:
    static std::vector<std::string> splitLine(const std::string& line, char separator);

    static std::string trim(const std::string& str);
};