#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

std::string getRandomStr(int range) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result = "";
    for (int i = 0; i < range; i++) {
        int index = rand() % alphabet.length();
        result += alphabet[index];
    }
    return result;
}

std::map<char, int> countChars(const std::string& text) {
    std::map<char, int> counts;
    for (char c : text) {
        counts[c]++;
    }
    return counts;
}

void printCounts(const std::map<char, int>& counts) {
    int maxCount = 0;
    for (auto& [letter, count] : counts) {
        if (count > maxCount) maxCount = count;
    }

    int scale = maxCount / 50;
    if (scale < 1) scale = 1;

    for (auto& [letter, count] : counts) {
        std::cout << letter << " | ";
        for (int j = 0; j < count / scale; ++j) {
            std::cout << "█";
        }
        std::cout << " " << count << "\n";
    }
}

std::string formatTime(double seconds) {
    if (seconds < 60.0) return std::to_string(seconds) + " sec";
    if (seconds < 3600.0) return std::to_string(seconds / 60.0) + " min";
    if (seconds < 86400.0) return std::to_string(seconds / 3600.0) + " hours";
    if (seconds < 31536000.0) return std::to_string(seconds / 86400.0) + " days";
    return std::to_string(seconds / 31536000.0) + " years";
}

void printCrackTime(int passwordLength, int alphabetSize, double speed) {
    double keyspace = std::pow(alphabetSize, passwordLength);
    double averageAttempts = keyspace / 2.0;
    double seconds = averageAttempts / speed;

    std::cout << "\n--- Password crack time ---\n";
    std::cout << "Alphabet size:   " << alphabetSize << "\n";
    std::cout << "Password length: " << passwordLength << "\n";
    std::cout << "Keyspace:        " << keyspace << "\n";
    std::cout << "Speed:           " << speed << " passwords/sec\n";
    std::cout << "Average time:    " << formatTime(seconds) << "\n";
}

void printCrackTimeGraph(int maxLength, int alphabetSize, double speed) {
    std::cout << "\n--- Crack time vs password length ---\n";
    std::cout << "Alphabet: " << alphabetSize
              << ", speed: " << speed << " passwords/sec\n\n";

    std::vector<double> times(maxLength + 1);
    double maxLog = 0;

    for (int len = 1; len <= maxLength; ++len) {
        double keyspace = std::pow(alphabetSize, len);
        double seconds = keyspace / 2.0 / speed;
        times[len] = seconds;

        double logVal = std::log10(seconds + 1);
        if (logVal > maxLog) maxLog = logVal;
    }

    std::cout << "Length | Time               | Graph\n";
    std::cout << "-------|--------------------|";
    for (int i = 0; i < 50; ++i) std::cout << "-";
    std::cout << "\n";

    for (int len = 1; len <= maxLength; ++len) {
        double seconds = times[len];
        std::string timeStr = formatTime(seconds);

        double logVal = std::log10(seconds + 1);
        int bars = static_cast<int>(50.0 * logVal / maxLog);
        if (bars < 1 && seconds > 0) bars = 1;

        std::cout << "  " << len;
        if (len < 10) std::cout << "    ";
        else std::cout << "   ";
        std::cout << "| ";

        std::cout << timeStr;
        for (std::size_t i = timeStr.size(); i < 18; ++i) std::cout << " ";
        std::cout << " | ";

        for (int j = 0; j < bars; ++j) std::cout << "█";
        std::cout << "\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int string_range = 0;
    std::cout << "Enter your string range: ";
    std::cin >> string_range;

    std::string text = getRandomStr(string_range);
    std::cout << "Result: " << text << std::endl;

    std::cout << "\nFrequencies:\n";
    std::map<char, int> counts = countChars(text);
    printCounts(counts);

    printCrackTime(string_range, 52, 1e6);
    printCrackTimeGraph(12, 52, 1e6);

    return 0;
}