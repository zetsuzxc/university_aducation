// 2) Латиница строчные и прописные.
#include <iostream>
#include <string>
#include <map>
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

    return 0;
}