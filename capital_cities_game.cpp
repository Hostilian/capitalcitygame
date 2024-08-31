#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <sstream>
#include <stdexcept>
#include <filesystem>

// Data structure to hold country-capital pairs and their variations
struct CityCountryPair {
    std::string country, capital, continent;
    std::vector<std::string> countryVariations, capitalVariations;
};

class CapitalCitiesGame {
    std::vector<CityCountryPair> data;
    std::mt19937 rng;

    // Load data from file, handling potential file access issues
    void loadData() {
        std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
        std::ifstream file("capital_cities.txt");
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file capital_cities.txt" << std::endl;
            std::cerr << "Trying to open from parent directory..." << std::endl;
            file.open("../capital_cities.txt");
            if (!file.is_open()) {
                throw std::runtime_error("Error: Unable to open capital_cities.txt");
            }
        }

        std::string line;
        while (std::getline(file, line)) {
            auto pair = parseLine(line);
            if (!pair.country.empty()) data.push_back(pair);
        }
        std::cout << "Loaded " << data.size() << " city-country pairs." << std::endl;
    }

    // Parse a single line of input data
    CityCountryPair parseLine(const std::string& line) {
        CityCountryPair pair;
        std::istringstream iss(line);
        std::string part;

        if (std::getline(iss, part, ';')) {
            std::istringstream countryStream(part);
            std::getline(countryStream, pair.country, ',');
            while (std::getline(countryStream, part, ',')) pair.countryVariations.push_back(part);
        }

        if (std::getline(iss, part, ';')) {
            std::istringstream capitalStream(part);
            std::getline(capitalStream, pair.capital, ',');
            while (std::getline(capitalStream, part, ',')) pair.capitalVariations.push_back(part);
        }

        std::getline(iss, pair.continent);
        return pair;
    }

    // Check if user's answer matches the correct answer or its variations
    bool isCorrectAnswer(const std::string& userAnswer, const std::string& correctAnswer, const std::vector<std::string>& variations) {
        auto normalize = [](std::string s) {
            s.erase(remove_if(s.begin(), s.end(), ispunct), s.end());
            transform(s.begin(), s.end(), s.begin(), ::tolower);
            return s;
        };
        auto normalizedUser = normalize(userAnswer);
        if (normalizedUser == normalize(correctAnswer)) return true;
        return std::any_of(variations.begin(), variations.end(), [&](const std::string& var) { return normalizedUser == normalize(var); });
    }

    // Main game loop
    void playGame(int mode, const std::string& selectedContinent = "") {
        std::vector<int> indices;
        for (int i = 0; i < data.size(); ++i)
            if (selectedContinent.empty() || data[i].continent == selectedContinent)
                indices.push_back(i);

        int score = 0, total = 0;
        auto startTime = std::chrono::high_resolution_clock::now();

        while (!indices.empty()) {
            std::uniform_int_distribution<> dist(0, indices.size() - 1);
            int index = indices[dist(rng)];
            indices.erase(indices.begin() + index);

            const auto& pair = data[index];
            std::string question = (mode == 1 || (mode == 3 && dist(rng) % 2 == 0)) ? pair.country : pair.capital;
            std::string answer = (question == pair.country) ? pair.capital : pair.country;
            const auto& variations = (question == pair.country) ? pair.capitalVariations : pair.countryVariations;

            std::cout << "\nWhat is the " << (question == pair.country ? "capital" : "country") << " of " << question << "? ";
            std::string userAnswer;
            std::getline(std::cin, userAnswer);

            if (userAnswer == "stop") break;

            total++;
            if (isCorrectAnswer(userAnswer, answer, variations)) {
                std::cout << "Correct!\n";
                score++;
            } else {
                std::cout << "Wrong. The correct answer is " << answer << ".\n";
            }
            std::cout << "Current score: " << score << "/" << total << "\n";
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        std::cout << "\nGame Over! Final score: " << score << "/" << total
                  << "\nSuccess rate: " << (total > 0 ? (score * 100.0 / total) : 0) << "%"
                  << "\nTime played: " << duration.count() << " seconds\n";
    }

public:
    CapitalCitiesGame() : rng(std::chrono::steady_clock::now().time_since_epoch().count()) { loadData(); }

    // Main game entry point
    void run(bool interactive = true) {
        if (!interactive) {
            std::cout << "Running in non-interactive mode..." << std::endl;
            playGame(1);
            return;
        }

        while (true) {
            std::cout << "\nCapital City Guessing Game\n1. Guess the capital\n2. Guess the country\n"
                      << "3. Mixed mode\n4. Play by continent\n5. Quit\nEnter your choice (1-5): ";
            std::string choice;
            std::getline(std::cin, choice);

            if (choice == "5") break;
            if (choice == "4") {
                std::cout << "Enter continent name: ";
                std::string continent;
                std::getline(std::cin, continent);
                playGame(3, continent);
            } else if (choice >= "1" && choice <= "3") {
                playGame(std::stoi(choice));
            } else {
                std::cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main(int argc, char* argv[]) {
    try {
        CapitalCitiesGame game;
        game.run(argc < 2 || std::string(argv[1]) != "--non-interactive");
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
