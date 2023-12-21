#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <sstream>


int main() {
	std::ifstream file("ScratchCards.txt");
	std::string line;
	std::vector<std::unordered_map<int, int>> cards;
	std::vector<std::vector<int>> givenNums;

	while (std::getline(file, line)) {
		size_t i = 0;
		while (i < line.length()) {
			char c = line[i];
			
			if (c == '|') {
				std::vector<int> currNums;
				std::string currNumStr = "";
				while (i < line.length()) {
					if (std::isdigit(c)) {
						currNumStr += c;
					}
					else if(currNumStr.length()){
						currNums.push_back(std::stoi(currNumStr));
						currNumStr = "";
					}
					i++;
					if (i < line.length()) c = line[i];
				}
				if (currNumStr.length()) {
					currNums.push_back(std::stoi(currNumStr));
					currNumStr = "";
				}
				givenNums.push_back(currNums);
			}
			else if (c == ':') {
				std::unordered_map<int, int> umap;
				std::string currNumStr = "";
				while (c != '|') {
					if (std::isdigit(c)) {
						currNumStr += c;
					}
					else if (currNumStr.length()) {
						umap[std::stoi(currNumStr)] = 0;
						currNumStr = "";
					}
					i++;
					c = line[i];
				}
				cards.push_back(umap);
			}
			else {
				i++;
			}
			
		}
	}

	int sum = 0;
	for (size_t i = 0; i < givenNums.size(); i++) {
		std::vector<int> currNums = givenNums[i];
		std::unordered_map<int, int> currCard = cards[i];
		int points = 0;
		for (size_t j = 0; j < currNums.size(); j++) {
			if (currCard.count(currNums[j]) >= 1) {
				if (points == 0) {
					points = 1;
				}
				else {
					points *= 2;
				}
			}
		}
		sum += points;
	}

	std::cout << "The total points from all scratchcards is: " << sum << std::endl;

};