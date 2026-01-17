#ifndef LEETCODE_UTILS_H
#define LEETCODE_UTILS_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

namespace leetcode {
    // Path helper: always points to the SOURCE tree `problems/<problemName>/<filename>`
    inline std::string getInputPath(const std::string& problemName,
                                    const std::string& filename) {
        #ifdef SOURCE_DIR
        return std::string(SOURCE_DIR) + "/problems/" + problemName + "/" + filename;
        #else
        return "../../problems/" + problemName + "/" + filename;
        #endif
    }
    // ---- small string helpers ----
    inline std::string trim(const std::string& s) {
        auto l = s.find_first_not_of(" \t\r\n");
        if (l == std::string::npos) return "";
        auto r = s.find_last_not_of(" \t\r\n");
        return s.substr(l, r - l + 1);
    }

    // Parses a LeetCode-style string line:
    // - abc              -> "abc"
    // - "abc"            -> "abc"
    // - "a b"            -> "a b"
    // - "a\\\"b"         -> a"b
    inline std::string parseString(const std::string& s) {
        std::string t = trim(s);
        if (t.size() >= 2 && ((t.front() == '"' && t.back() == '"') || (t.front() == '\'' && t.back() == '\''))) {
            t = t.substr(1, t.size() - 2);
        }

        // minimal unescape (enough for common LeetCode examples)
        std::string out;
        out.reserve(t.size());
        for (size_t i = 0; i < t.size(); ++i) {
            if (t[i] == '\\' && i + 1 < t.size()) {
                char n = t[i + 1];
                if (n == 'n') { out.push_back('\n'); i++; continue; }
                if (n == 't') { out.push_back('\t'); i++; continue; }
                if (n == 'r') { out.push_back('\r'); i++; continue; }
                if (n == '\\') { out.push_back('\\'); i++; continue; }
                if (n == '"') { out.push_back('"'); i++; continue; }
                if (n == '\'') { out.push_back('\''); i++; continue; }
                // unknown escape: keep the next char
                out.push_back(n);
                i++;
                continue;
            }
            out.push_back(t[i]);
        }
        return out;
    }

    // Parses: [1,2,3]  (spaces allowed)
    inline std::vector<int> parseIntVector(const std::string& s) {
        std::vector<int> result;
        std::string cleaned = s;

        // trim leading/trailing whitespace
        auto l = cleaned.find_first_not_of(" \t\r\n");
        auto r = cleaned.find_last_not_of(" \t\r\n");
        if (l == std::string::npos) return result;
        cleaned = cleaned.substr(l, r - l + 1);

        // remove optional outer brackets
        if (!cleaned.empty() && (cleaned.front() == '[' || cleaned.front() == '(')) cleaned.erase(cleaned.begin());
        if (!cleaned.empty() && (cleaned.back() == ']' || cleaned.back() == ')')) cleaned.pop_back();

        std::istringstream iss(cleaned);
        std::string token;
        while (std::getline(iss, token, ',')) {
            auto tl = token.find_first_not_of(" \t\r\n");
            auto tr = token.find_last_not_of(" \t\r\n");
            if (tl == std::string::npos) continue;
            token = token.substr(tl, tr - tl + 1);
            result.push_back(std::stoi(token));
        }
        return result;
    }

    // Parses: [[0,0,1],[2,2,1]] (spaces allowed)
    inline std::vector<std::vector<int>> parseInt2DVector(const std::string& s) {
        std::vector<std::vector<int>> result;

        // trim
        auto l = s.find_first_not_of(" \t\r\n");
        auto r = s.find_last_not_of(" \t\r\n");
        if (l == std::string::npos) return result;
        std::string cleaned = s.substr(l, r - l + 1);

        // must start/end with '[' ']'
        if (cleaned.size() < 2 || cleaned.front() != '[' || cleaned.back() != ']') return result;

        // remove outer []
        cleaned = cleaned.substr(1, cleaned.size() - 2);

        // scan and extract each inner [ ... ] at depth 1
        int depth = 0;
        size_t start = std::string::npos;
        for (size_t i = 0; i < cleaned.size(); ++i) {
            char c = cleaned[i];
            if (c == '[') {
                if (depth == 0) start = i;
                depth++;
            } else if (c == ']') {
                depth--;
                if (depth == 0 && start != std::string::npos) {
                    std::string row = cleaned.substr(start, i - start + 1);
                    result.push_back(parseIntVector(row));
                    start = std::string::npos;
                }
            }
        }
        return result;
    }

    inline void printVector(const std::vector<int>& v) {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); i++) {
            std::cout << v[i];
            if (i < v.size() - 1) std::cout << ",";
        }
        std::cout << "]";
    }

    // Parses: ["a","b","c"] (quotes required for multi-token strings; spaces allowed)
    inline std::vector<std::string> parseStringVector(const std::string& s) {
        std::vector<std::string> res;
        std::string cleaned = trim(s);
        if (cleaned.size() < 2 || cleaned.front() != '[' || cleaned.back() != ']') return res;
        cleaned = cleaned.substr(1, cleaned.size() - 2);

        std::string cur;
        bool in_quote = false;
        char quote_char = '"';
        bool escape = false;

        for (size_t i = 0; i < cleaned.size(); ++i) {
            char c = cleaned[i];
            if (escape) {
                cur.push_back('\\');
                cur.push_back(c);
                escape = false;
                continue;
            }
            if (in_quote && c == '\\') { escape = true; continue; }
            if (c == '"' || c == '\'') {
                if (!in_quote) { in_quote = true; quote_char = c; cur.push_back(c); continue; }
                if (c == quote_char) { in_quote = false; cur.push_back(c); continue; }
            }
            if (!in_quote && c == ',') {
                auto item = trim(cur);
                if (!item.empty()) res.push_back(parseString(item));
                cur.clear();
                continue;
            }
            cur.push_back(c);
        }
        auto item = trim(cur);
        if (!item.empty()) res.push_back(parseString(item));
        return res;
    }

    inline void printVector(const std::vector<std::string>& v) {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); i++) {
            std::cout << "\"";
            for (char c : v[i]) {
                if (c == '\\' || c == '"') std::cout << '\\';
                std::cout << c;
            }
            std::cout << "\"";
            if (i < v.size() - 1) std::cout << ",";
        }
        std::cout << "]";
    }

    inline void print2DVector(const std::vector<std::vector<int>>& v) {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); i++) {
            printVector(v[i]);
            if (i < v.size() - 1) std::cout << ",";
        }
        std::cout << "]";
    }

    // ---- testcase generation helpers ----

    // Serialize common types back to LeetCode-style strings
    inline std::string toString(const std::vector<int>& v) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            oss << v[i];
            if (i + 1 < v.size()) oss << ",";
        }
        oss << "]";
        return oss.str();
    }

    inline std::string toString(const std::vector<std::vector<int>>& v) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            oss << toString(v[i]);
            if (i + 1 < v.size()) oss << ",";
        }
        oss << "]";
        return oss.str();
    }

    inline std::string toString(const std::vector<std::string>& v) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            oss << "\"";
            for (char c : v[i]) {
                if (c == '\\' || c == '"') oss << '\\';
                oss << c;
            }
            oss << "\"";
            if (i + 1 < v.size()) oss << ",";
        }
        oss << "]";
        return oss.str();
    }

    // Write a testcase file (each string is one line)
    // Writes into the source tree, next to other input files:
    //   problems/<problemName>/<filename>
    inline bool writeTestcaseFile(const std::string& problemName,
                                  const std::string& filename,
                                  const std::vector<std::string>& lines) {
        std::ofstream out(getInputPath(problemName, filename));
        if (!out.is_open()) return false;
        for (const auto& line : lines) {
            out << line << '\n';
        }
        return true;
    }

    // ---- timing helpers ----

    class ScopedTimer {
    public:
        explicit ScopedTimer(const std::string& label = "elapsed")
            : label_(label),
              start_(std::chrono::high_resolution_clock::now()) {}

        ~ScopedTimer() {
            auto end = std::chrono::high_resolution_clock::now();
            auto ms =
                std::chrono::duration_cast<std::chrono::microseconds>(end - start_)
                    .count() / 1000.0;
            std::cerr << label_ << ": " << ms << " ms" << std::endl;
        }

    private:
        std::string label_;
        std::chrono::high_resolution_clock::time_point start_;
    };
}

#endif // LEETCODE_UTILS_H

