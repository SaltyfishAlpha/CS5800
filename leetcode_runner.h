#ifndef LEETCODE_RUNNER_H
#define LEETCODE_RUNNER_H

#include <string>
#include <iostream>
#include <cstdio>

#include "leetcode_utils.h"

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
