#include "mainRPG.h"
#include <fstream>
#include <sstream>

//Le o arquivo e guarda o texto de todas as tags <tag>...</tag>
//Ex.: readXML("names.xml", "player") -> {"Arthur", "Ragnar", ...}
std::vector<std::string> readXML(std::string fileName, std::string tag){
    std::vector<std::string> values;

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "Aviso: nao foi possivel abrir " << fileName << "\n";
        return values;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    std::string open = "<" + tag + ">";
    std::string close = "</" + tag ">";

    size_t start = text.find(open);
    while (start != std::string::npos) {
        start += open.size();
        size_t end = text.find(close, start);
        if (end == std::string::npos) break;
        values.push_back(text.substr(start, end - start));
        start = text.find(open, end);
    }
    return values;
    
}

// Sorteia um valor da lista e o remove (para nao repetir nomes)
std::string drawName(std::vector<std::string>& names, Dice& dice, std::string fallback){
    if (names.empty()) return fallback;
    int i = dice.roll((int)names.size()) - 1;
    std::string chosen = names[i];
    names.erase(names.begin() + i);
    return chosen;
}