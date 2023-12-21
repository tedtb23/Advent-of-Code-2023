#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

struct Cell {
	int rowPos;
	int colPos;

	bool operator==(const Cell& c) const {
		return rowPos == c.rowPos && colPos == c.colPos;
	}
};

class CellHash {
public:
	size_t operator()(const Cell& c) const {
		return (size_t) 0.5 * (c.rowPos + c.colPos) * (c.rowPos + c.colPos + 1) + c.colPos;
	}
};

Cell findStarPos(const std::vector<std::string> text, int row, int col) {
	size_t rows = text.size();
	size_t cols = text[row].length();

	std::vector<Cell> neighbors = {
		{row - 1, col - 1}, //topLeft
		{row - 1, col}, //top
		{row - 1, col + 1}, //topRight
		{row, col - 1}, //left
		{row, col + 1}, //right
		{row + 1, col - 1}, //botLeft
		{row + 1, col}, //bot
		{row + 1, col + 1} //botRight
	};

	for (int i = 0; i < neighbors.size(); i++) {
		const Cell currCell = neighbors[i];

		if (currCell.rowPos >= 0 && currCell.colPos >= 0 && currCell.rowPos < rows && currCell.colPos < cols) {
			const char currChar = text[currCell.rowPos][currCell.colPos];
			if (currChar == '*') {
				return currCell;
			}
		}
	}
	return {-1, -1};
}

int main() {
	std::ifstream file("Schematic");
	std::string line;
	std::vector<std::string> text;
	std::unordered_multimap<Cell, int, CellHash> stars;

	while (std::getline(file, line)) {
		text.push_back(line);
	}

	std::string currNumStr = "";
	Cell currStarPos;
	bool isStarAdjacent = false;

	for (int i = 0; i < text.size(); i++) {
		const std::string currLine = text[i];

		for (int j = 0; j < currLine.size(); j++) {
			const char currChar = currLine[j];

			if (std::isdigit(currChar)) {
				currNumStr += currChar;
				if (!isStarAdjacent) {
					currStarPos = findStarPos(text, i, j);
					if (currStarPos.rowPos != -1) isStarAdjacent = true;
				}
			}
			else {
				if (currNumStr.size() && isStarAdjacent) {
					int currNum = std::stoi(currNumStr);
					stars.insert(std::make_pair(currStarPos, currNum));
				}
				currNumStr = "";
				currStarPos = { -1, -1 };
				isStarAdjacent = false;
			}
		}
	}

	int sum = 0;
	for (auto i : stars) {
		if (stars.count(i.first) == 2) {
			auto range = stars.equal_range(i.first);
			int mult = 1;
			for (auto itr = range.first; itr != range.second; itr++) {
				mult *= itr->second;
				itr->second = 1;
			}
			if(mult > 1) sum += mult;
		}
	}

	std::cout << "Sum of Gear Ratios is: " << sum << std::endl;
	file.close();
}