# Capital Cities Game

Project for "PROGRAMMING (programs INFO ETE15E, SYI ETE56E, TF ETE28E)"
Miriam

## Description:
This program implements a Capital Cities guessing game. It loads country-capital pairs from a file and allows users to play various game modes where they guess either the capital or the country. The game supports multiple variations of country and capital names.

Features:
- Load data from a text file
- Multiple game modes: guess capital, guess country, mixed mode
- Play by continent option
- Score tracking and timing
- Non-interactive mode for testing

## Main Variables and Data Structures:
- `data`: Vector of `CityCountryPair` structures containing country-capital information
- `rng`: Random number generator for shuffling questions
- `CityCountryPair`: Structure containing country, capital, continent, and name variations

## Conceptual Program Description:
1. The program loads data from a file
2. It displays a menu and waits for user input
3. Based on the chosen mode, it selects questions randomly
4. For each question, it compares the user's answer with the correct answer and variations
5. It keeps track of the score and time
6. At the end, it displays the final score, success rate, and time played

## Input Limitations and Potential Issues:
- Assumes the input file is correctly formatted
- Case-insensitive and punctuation-insensitive answer checking
- Doesn't handle word breaks at end of lines in the input file
- Empty input file is permissible
- File size is limited only by system resources

## Compilation and Execution:
```
g++ -std=c++17 -o capital_cities_game.exe capital_cities_game.cpp
./capital_cities_game.exe
```
For non-interactive mode: `./capital_cities_game.exe --non-interactive`

## File Structure:
- `capital_cities_game.cpp`: Main source code
- `capital_cities.txt`: Input file with country-capital pairs
- `capital_cities_game.exe`: Compiled executable
