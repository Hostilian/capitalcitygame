#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <map>
#include <chrono>
#include <iomanip>
#include <filesystem>

struct CityCountryPair {
    std::string country;
    std::string capital;
    std::string continent;
};

class CapitalCitiesGame {
private:
    std::vector<CityCountryPair> data;
    std::mt19937 rng;
    std::map<std::string, int> continentScores;

    void loadData() {
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        std::ifstream file("capital_cities.txt");
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open capital_cities.txt" << std::endl;
            std::cerr << "Attempting to open from parent directory..." << std::endl;
            file.open("../capital_cities.txt");
            if (!file.is_open()) {
                std::cerr << "Error: Unable to open ../capital_cities.txt" << std::endl;
                std::cerr << "Please ensure the file exists and is accessible." << std::endl;
                exit(1);
            }
        }

        std::string line;
        while (std::getline(file, line)) {
            size_t pos1 = line.find(';');
            size_t pos2 = line.find(';', pos1 + 1);
            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                CityCountryPair pair;
                pair.country = line.substr(0, pos1);
                pair.capital = line.substr(pos1 + 1, pos2 - pos1 - 1);
                pair.continent = line.substr(pos2 + 1);
                data.push_back(pair);
            }
        }
        file.close();
        std::cout << "Loaded " << data.size() << " city-country pairs." << std::endl;
    }

    void playGame(int mode, const std::string& selectedContinent = "") {
        int score = 0;
        int total = 0;
        std::vector<int> indices;

        for (int i = 0; i < data.size(); ++i) {
            if (selectedContinent.empty() || data[i].continent == selectedContinent) {
                indices.push_back(i);
            }
        }

        auto startTime = std::chrono::high_resolution_clock::now();

        while (true) {
            if (indices.empty()) {
                std::cout << "You've answered all questions for this continent!" << std::endl;
                break;
            }

            std::uniform_int_distribution<int> dist(0, indices.size() - 1);
            int index = dist(rng);
            int dataIndex = indices[index];
            indices.erase(indices.begin() + index);

            const auto& pair = data[dataIndex];
            std::string question, answer;

            if (mode == 1 || (mode == 3 && dist(rng) % 2 == 0)) {
                question = pair.country;
                answer = pair.capital;
                std::cout << "\nWhat is the capital of " << question << "?" << std::endl;
            } else {
                question = pair.capital;
                answer = pair.country;
                std::cout << "\nWhat is the country for " << question << "?" << std::endl;
            }

            std::string userAnswer;
            std::cout << "Your answer (or 'stop' to end the game): ";
            std::getline(std::cin, userAnswer);

            if (userAnswer == "stop") {
                break;
            }

            total++;
            if (userAnswer == answer) {
                std::cout << "Correct!" << std::endl;
                score++;
                continentScores[pair.continent]++;
            } else {
                std::cout << "Wrong. The correct answer is " << answer << "." << std::endl;
            }

            std::cout << "Current score: " << score << "/" << total << std::endl;
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);

        std::cout << "\nGame Over!" << std::endl;
        std::cout << "Final score: " << score << "/" << total << std::endl;
        if (total > 0) {
            double successRate = (static_cast<double>(score) / total) * 100;
            std::cout << "Success rate: " << std::fixed << std::setprecision(2) << successRate << "%" << std::endl;
        }
        std::cout << "Time played: " << duration.count() << " seconds" << std::endl;

        std::cout << "\nContinent Scores:" << std::endl;
        for (const auto& pair : continentScores) {
            std::cout << pair.first << ": " << pair.second << std::endl;
        }
    }

public:
    CapitalCitiesGame() : rng(std::time(0)) {
        loadData();
    }

    void run() {
        while (true) {
            std::cout << "\nCapital City Guessing Game" << std::endl;
            std::cout << "1. Guess the capital" << std::endl;
            std::cout << "2. Guess the country" << std::endl;
            std::cout << "3. Mixed mode" << std::endl;
            std::cout << "4. Play by continent" << std::endl;
            std::cout << "5. View high scores" << std::endl;
            std::cout << "6. Quit" << std::endl;

            std::string choice;
            std::cout << "Enter your choice (1-6): ";
            std::getline(std::cin, choice);

            if (choice == "1" || choice == "2" || choice == "3") {
                playGame(std::stoi(choice));
            } else if (choice == "4") {
                std::cout << "Enter continent name: ";
                std::string continent;
                std::getline(std::cin, continent);
                playGame(3, continent);
            } else if (choice == "5") {
                std::cout << "\nHigh Scores by Continent:" << std::endl;
                for (const auto& pair : continentScores) {
                    std::cout << pair.first << ": " << pair.second << std::endl;
                }
            } else if (choice == "6") {
                std::cout << "Thanks for playing!" << std::endl;
                break;
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
};

int main() {
    try {
        CapitalCitiesGame game;
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
