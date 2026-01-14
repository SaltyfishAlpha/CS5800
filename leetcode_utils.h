#ifndef LEETCODE_UTILS_H
#define LEETCODE_UTILS_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

namespace leetcode {
    // Base class for input processing
    // Each problem can inherit and override processInput() and solve()
    class Problem {
    public:
        virtual ~Problem() = default;
        
        // Reads input from file and processes it
        // Override this method for each problem to parse inputs differently
        virtual void processInput(const std::string& inputFile) {
            std::ifstream file(inputFile);
            if (!file.is_open()) {
                std::cerr << "Error: Cannot open input file: " << inputFile << std::endl;
                return;
            }
            
            // Default implementation reads all lines
            std::string line;
            while (std::getline(file, line)) {
                // Override this method to customize input parsing
                parseLine(line);
            }
            file.close();
        }
        
        // Override this method to parse each line of input
        virtual void parseLine(const std::string& line) {
            // Default implementation does nothing
            // Override in derived classes
        }
        
        // Override this method to implement the solution
        virtual void solve() = 0;
        
        // Prints the result
        virtual void printResult() = 0;
    };
    
    // Utility functions for common input parsing
    
    // Split a string by delimiter
    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
    
    // Parse string to integer vector (e.g., "[1,2,3]" or "1 2 3")
    std::vector<int> parseIntVector(const std::string& s) {
        std::vector<int> result;
        std::string cleaned = s;
        
        // Remove brackets if present
        if (cleaned.front() == '[' || cleaned.front() == '(') {
            cleaned = cleaned.substr(1);
        }
        if (cleaned.back() == ']' || cleaned.back() == ')') {
            cleaned.pop_back();
        }
        
        std::istringstream iss(cleaned);
        std::string token;
        while (std::getline(iss, token, ',')) {
            // Remove whitespace
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            if (!token.empty()) {
                result.push_back(std::stoi(token));
            }
        }
        return result;
    }
    
    // Parse string to 2D integer vector
    std::vector<std::vector<int>> parseInt2DVector(const std::string& s) {
        std::vector<std::vector<int>> result;
        std::string cleaned = s;
        
        // Remove outer brackets
        if (cleaned.front() == '[') cleaned = cleaned.substr(1);
        if (cleaned.back() == ']') cleaned.pop_back();
        
        // Split by "],[" or "], [" pattern
        std::vector<std::string> rows = split(cleaned, ']');
        for (auto& row : rows) {
            if (row.front() == '[' || row.front() == ',') {
                row = row.substr(1);
            }
            if (row.front() == ' ') {
                row = row.substr(1);
            }
            row = '[' + row + ']';
            result.push_back(parseIntVector(row));
        }
        return result;
    }
}

#endif // LEETCODE_UTILS_H

