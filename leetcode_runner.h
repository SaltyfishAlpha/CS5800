#ifndef LEETCODE_RUNNER_H
#define LEETCODE_RUNNER_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <cstdio>

namespace leetcode {
    // Parse string to integer vector (e.g., "[1,2,3]")
    inline std::vector<int> parseIntVector(const std::string& s) {
        std::vector<int> result;
        std::string cleaned = s;
        
        if (!cleaned.empty() && (cleaned.front() == '[' || cleaned.front() == '(')) {
            cleaned = cleaned.substr(1);
        }
        if (!cleaned.empty() && (cleaned.back() == ']' || cleaned.back() == ')')) {
            cleaned.pop_back();
        }
        
        std::istringstream iss(cleaned);
        std::string token;
        while (std::getline(iss, token, ',')) {
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            if (!token.empty()) {
                result.push_back(std::stoi(token));
            }
        }
        return result;
    }
    
    // Output formatting
    inline void printVector(const std::vector<int>& v) {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); i++) {
            std::cout << v[i];
            if (i < v.size() - 1) std::cout << ",";
        }
        std::cout << "]" << std::endl;
    }
    
    // Get input file path helper
    inline std::string getInputPath(const std::string& problemName, const std::string& filename) {
        #ifdef SOURCE_DIR
        return std::string(SOURCE_DIR) + "/problems/" + problemName + "/" + filename;
        #else
        return "../../problems/" + problemName + "/" + filename;
        #endif
    }
}

// Helper macros for optional parameter handling
#define LEETCODE_MAIN_BEGIN_1(PROBLEM_NAME) \
    LEETCODE_MAIN_BEGIN_2(PROBLEM_NAME, "input.txt")

#define LEETCODE_MAIN_BEGIN_2(PROBLEM_NAME, INPUT_FILE) \
    int main(int argc, char* argv[]) { \
        std::string inputFile = INPUT_FILE; \
        std::string inputPath = leetcode::getInputPath(PROBLEM_NAME, inputFile); \
        FILE* input_fp = freopen(inputPath.c_str(), "r", stdin); \
        if (!input_fp) { \
            std::cerr << "Error: Cannot open " << inputPath << std::endl; \
            return 1; \
        } \
        Solution solution;

// Macro to create main function boilerplate
// Parameters: PROBLEM_NAME - name of the problem directory (required)
//             INPUT_FILE - input filename (optional, defaults to "input.txt")
// Usage: LEETCODE_MAIN_BEGIN("problem-name") or LEETCODE_MAIN_BEGIN("problem-name", "input2.txt")
#define LEETCODE_MAIN_BEGIN(...) \
    LEETCODE_GET_MACRO(__VA_ARGS__, LEETCODE_MAIN_BEGIN_2, LEETCODE_MAIN_BEGIN_1)(__VA_ARGS__)

// Helper macro to select the right overload based on argument count
#define LEETCODE_GET_MACRO(_1, _2, NAME, ...) NAME

#define LEETCODE_MAIN_END \
        return 0; \
    }

#endif // LEETCODE_RUNNER_H
