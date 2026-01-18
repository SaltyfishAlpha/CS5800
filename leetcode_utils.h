#ifndef LEETCODE_UTILS_H
#define LEETCODE_UTILS_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>

namespace leetcode {
    // Path helper
    inline std::string getInputPath(const std::string& problemName,
                                    const std::string& filename) {
        #ifdef SOURCE_DIR
        return std::string(SOURCE_DIR) + "/problems/" + problemName + "/" + filename;
        #else
        return "../../problems/" + problemName + "/" + filename;
        #endif
    }

    // ---- String helpers ----
    inline std::string trim(const std::string& s) {
        auto l = s.find_first_not_of(" \t\r\n");
        if (l == std::string::npos) return "";
        auto r = s.find_last_not_of(" \t\r\n");
        return s.substr(l, r - l + 1);
    }

    inline std::string parseString(const std::string& s) {
        std::string t = trim(s);
        if (t.size() >= 2 && ((t.front() == '"' && t.back() == '"') ||
                              (t.front() == '\'' && t.back() == '\''))) {
            t = t.substr(1, t.size() - 2);
        }

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
                out.push_back(n);
                i++;
                continue;
            }
            out.push_back(t[i]);
        }
        return out;
    }

    // ===== Generic Tokenizer =====

    inline std::vector<std::string> parseTokens1D(const std::string& s) {
        std::vector<std::string> result;
        std::string cleaned = trim(s);

        if (!cleaned.empty() && (cleaned.front() == '[' || cleaned.front() == '('))
            cleaned.erase(cleaned.begin());
        if (!cleaned.empty() && (cleaned.back() == ']' || cleaned.back() == ')'))
            cleaned.pop_back();

        std::string cur;
        bool in_quote = false;
        char quote_char = '"';
        bool escape = false;

        for (size_t i = 0; i < cleaned.size(); ++i) {
            char c = cleaned[i];
            if (escape) {
                cur.push_back(c);
                escape = false;
                continue;
            }
            if (in_quote && c == '\\') { escape = true; cur.push_back(c); continue; }
            if (c == '"' || c == '\'') {
                if (!in_quote) { in_quote = true; quote_char = c; }
                else if (c == quote_char) { in_quote = false; }
                cur.push_back(c);
                continue;
            }
            if (!in_quote && c == ',') {
                auto token = trim(cur);
                if (!token.empty()) result.push_back(token);
                cur.clear();
                continue;
            }
            cur.push_back(c);
        }
        auto token = trim(cur);
        if (!token.empty()) result.push_back(token);

        return result;
    }

    inline std::vector<std::vector<std::string>> parseTokens2D(const std::string& s) {
        std::vector<std::vector<std::string>> result;
        std::string cleaned = trim(s);

        if (cleaned.size() < 2 || cleaned.front() != '[' || cleaned.back() != ']')
            return result;
        cleaned = cleaned.substr(1, cleaned.size() - 2);

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
                    std::string row_str = cleaned.substr(start, i - start + 1);
                    result.push_back(parseTokens1D(row_str));
                    start = std::string::npos;
                }
            }
        }
        return result;
    }

    // ===== Type Conversion System (Extensible) =====

    // Core converter: specialize this for new types
    template<typename T>
    inline T parseValue(const std::string& token);

    // Built-in type converters
    template<>
    inline int parseValue<int>(const std::string& token) {
        return std::stoi(trim(token));
    }

    template<>
    inline long parseValue<long>(const std::string& token) {
        return std::stol(trim(token));
    }

    template<>
    inline long long parseValue<long long>(const std::string& token) {
        return std::stoll(trim(token));
    }

    template<>
    inline double parseValue<double>(const std::string& token) {
        return std::stod(trim(token));
    }

    template<>
    inline char parseValue<char>(const std::string& token) {
        std::string t = parseString(token);
        return t.empty() ? '\0' : t[0];
    }

    template<>
    inline std::string parseValue<std::string>(const std::string& token) {
        return parseString(token);
    }

    // Generic 1D parser
    template<typename T>
    inline std::vector<T> parse1DVector(const std::string& s) {
        auto tokens = parseTokens1D(s);
        std::vector<T> result;
        result.reserve(tokens.size());
        for (const auto& tok : tokens) {
            result.push_back(parseValue<T>(tok));
        }
        return result;
    }

    // Generic 2D parser
    template<typename T>
    inline std::vector<std::vector<T>> parse2DVector(const std::string& s) {
        auto token_rows = parseTokens2D(s);
        std::vector<std::vector<T>> result;
        result.reserve(token_rows.size());
        for (const auto& row : token_rows) {
            std::vector<T> row_typed;
            row_typed.reserve(row.size());
            for (const auto& tok : row) {
                row_typed.push_back(parseValue<T>(tok));
            }
            result.push_back(row_typed);
        }
        return result;
    }

    // Backward compatibility aliases (optional)
    inline std::vector<int> parseIntVector(const std::string& s) {
        return parse1DVector<int>(s);
    }

    inline std::vector<std::vector<int>> parseInt2DVector(const std::string& s) {
        return parse2DVector<int>(s);
    }

    inline std::vector<std::vector<char>> parseChar2DVector(const std::string& s) {
        return parse2DVector<char>(s);
    }

    inline std::vector<std::string> parseStringVector(const std::string& s) {
        return parse1DVector<std::string>(s);
    }

    // ===== Print System (Extensible) =====

    // Core printer: specialize for custom types
    template<typename T>
    inline void printValue(const T& val) {
        std::cout << val;
    }

    // String specialization (with escaping)
    template<>
    inline void printValue<std::string>(const std::string& val) {
        std::cout << "\"";
        for (char c : val) {
            if (c == '\\' || c == '"') std::cout << '\\';
            std::cout << c;
        }
        std::cout << "\"";
    }

    // Char specialization (with quotes)
    template<>
    inline void printValue<char>(const char& val) {
        std::cout << "\"" << val << "\"";
    }

    // Generic 1D printer
    template<typename T>
    inline void printVector(const std::vector<T>& v) {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); i++) {
            printValue(v[i]);
            if (i < v.size() - 1) std::cout << ",";
        }
        std::cout << "]";
    }

    // Generic 2D printer
    template<typename T>
    inline void print2DVector(const std::vector<std::vector<T>>& v) {
        std::cout << "[";
        for (size_t i = 0; i < v.size(); i++) {
            printVector(v[i]);
            if (i < v.size() - 1) std::cout << ",";
        }
        std::cout << "]";
    }

    // ===== Serialization System (Extensible) =====

    template<typename T>
    inline std::string toValueString(const T& val) {
        std::ostringstream oss;
        oss << val;
        return oss.str();
    }

    template<>
    inline std::string toValueString<std::string>(const std::string& val) {
        std::ostringstream oss;
        oss << "\"";
        for (char c : val) {
            if (c == '\\' || c == '"') oss << '\\';
            oss << c;
        }
        oss << "\"";
        return oss.str();
    }

    template<typename T>
    inline std::string toString(const std::vector<T>& v) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            oss << toValueString(v[i]);
            if (i + 1 < v.size()) oss << ",";
        }
        oss << "]";
        return oss.str();
    }

    template<typename T>
    inline std::string toString(const std::vector<std::vector<T>>& v) {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < v.size(); ++i) {
            oss << toString(v[i]);
            if (i + 1 < v.size()) oss << ",";
        }
        oss << "]";
        return oss.str();
    }

    // ---- File I/O ----

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

    // ---- Timing ----

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