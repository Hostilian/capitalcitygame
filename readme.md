# Capital Cities Game

This is an enhanced version of the Capital Cities guessing game. Test your knowledge of world capitals and countries!

## Prerequisites

- C++17 compatible compiler (e.g., GCC, MinGW, or MSVC)
- CMake (optional, for easier building)

## Building the Game

### Using g++ (MinGW on Windows or GCC on Linux/macOS)

1. Open a terminal in the project directory.
2. Run the following command:

```
g++ -std=c++17 -o capital_cities_game.exe capital_cities_game.cpp
```

### Using CMake

1. Create a `CMakeLists.txt` file in the project directory with the following content:

```cmake
cmake_minimum_required(VERSION 3.10)
project(CapitalCitiesGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(capital_cities_game capital_cities_game.cpp)
```

2. Create a build directory and navigate to it:

```
mkdir build
cd build
```

3. Generate the build files and compile:

```
cmake ..
cmake --build .
```

## Running the Game

1. Ensure that `capital_cities_game.exe` (or `capital_cities_game` on Linux/macOS) and `capital_cities.txt` are in the same directory.
2. Run the executable:
   - On Windows: `.\capital_cities_game.exe`
   - On Linux/macOS: `./capital_cities_game`

## How to Play

1. Choose from the following game modes:
   - Guess the capital
   - Guess the country
   - Mixed mode
   - Play by continent
2. Answer the questions by typing the name of the capital or country.
3. Type 'stop' at any time to end the current game.
4. View your high scores by continent.

## Features

- Expanded database with numerous countries and capitals
- Continent-based gameplay
- Mixed mode for added challenge
- High score tracking by continent
- Time tracking for each game session

## Contributing

1. Fork the repository
2. Create a new branch for your feature
3. Commit your changes
4. Push to your branch
5. Create a new Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Enjoy testing your geography knowledge!
