#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SYMBOL_EMPTY '.'

struct Cell {
    size_t row;
    size_t col;
};

bool hasNeighboringSymbol(const std::vector<std::string>& input, size_t row, size_t col) {

    size_t numRows = input.size();
    size_t numColumns = input[row].length();

    Cell topLeft = { row - 1, col - 1 };
    Cell top = { row - 1, col };
    Cell topRight = { row - 1, col + 1 };
    Cell left = { row, col - 1 };
    Cell right = { row, col + 1 };
    Cell botLeft = { row + 1, col - 1 };
    Cell bot = { row + 1, col };
    Cell botRight = { row + 1, col + 1 };

    std::vector<Cell> neighbors = {
        {topLeft},
        {top},
        {topRight},
        {left},
        {right},
        {botLeft},
        {bot},
        {botRight}
    };

    for (const Cell cell : neighbors) {
        if (cell.row >= 0 && cell.col >= 0 && cell.row < numRows && cell.col < numColumns) {
            const char ch = input[cell.row][cell.col];
            if (ch != SYMBOL_EMPTY && !std::isdigit(ch)) {
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    std::ifstream file("Schematic");

    std::vector<std::string> text;
    std::string line;

    while (std::getline(file, line)) {
        text.push_back(line);
    }
    file.close();
    
    int sum = 0;
    std::string partNumStr = "";
    bool isPartNum = false;

    for (size_t i = 0; i < text.size(); i++) {
        std::string line = text[i];

        for (size_t j = 0; j < line.length(); j++) {
            const char ch = line[j];

            if (std::isdigit(ch)) {
                partNumStr += ch;

                if (!isPartNum && hasNeighboringSymbol(text, i, j)) {
                    isPartNum = true;
                }
            }
            else {
                if (isPartNum && partNumStr.size()) {
                    int partNum = std::stoi(partNumStr);
                    sum += partNum;
                }
                isPartNum = false;
                partNumStr = "";
            }
        }
    }
    std::cout << sum << std::endl;
    return 0;
}