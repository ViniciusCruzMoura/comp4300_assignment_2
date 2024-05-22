// #include "raylib.h"
// #include <string>
// #include <map>
// #include <memory>
// #include "raymath.h"

// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <vector>
// #include <algorithm>

#include "Game.h"

// std::vector<std::string> split(const std::string& s, char delimiter) {
//     std::vector<std::string> tokens;
//     std::string token;
//     std::istringstream tokenStream(s);
//     while (std::getline(tokenStream, token, delimiter)) {
//         tokens.push_back(token);
//     }
//     return tokens;
// }

// std::vector<std::vector<std::string>> load_csv(const std::string path)
// {
//     // Open the .csv file
//     std::ifstream file(path);
//     if (!file.is_open()) {
//         std::cerr << "Error opening file." << std::endl;
//         std::vector<std::vector<std::string>> err;
//         return err;
//     }

//     // Read the .csv file line by line
//     std::vector<std::vector<std::string>> data;
//     std::string line;
//     while (std::getline(file, line)) {
//         // Split each line by comma and store it in the 2D vector
//         std::vector<std::string> row = split(line, ',');
//         data.push_back(row);
//     }

//     // Display the data (optional)
//     // std::cout << "CSV Data." << std::endl;
//     // for (const auto& row : data) {
//     //     for (const auto& value : row) {
//     //         std::cout << value << " ";
//     //     }
//     //     std::cout << std::endl;
//     // }

//     // Close the file
//     file.close();

//     return data;
// }

// load_csv(../assets/map/map1.csv);

int main(void) {
    Game g("config.txt");
    g.run();
    return 0;
}