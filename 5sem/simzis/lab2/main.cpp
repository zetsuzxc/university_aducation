#include <iostream>
#include <string>
#include <cctype>

std::string vigenereEncrypt(const std::string& text, const std::string& key) {
    std::string result;
    int keyIndex = 0;
    int keyLen = key.length();

    for (char c : text) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            bool isUpper = std::isupper(static_cast<unsigned char>(c));
            char base = isUpper ? 'A' : 'a';

            char keyChar = std::tolower(static_cast<unsigned char>(key[keyIndex % keyLen]));
            int shift = keyChar - 'a';

            int pos = (c - base + shift) % 26;
            result += static_cast<char>(base + pos);

            keyIndex++;
        } else {
            result += c;
        }
    }
    return result;
}

std::string vigenereDecrypt(const std::string& text, const std::string& key) {
    std::string result;
    int keyIndex = 0;
    int keyLen = key.length();

    for (char c : text) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            bool isUpper = std::isupper(static_cast<unsigned char>(c));
            char base = isUpper ? 'A' : 'a';

            char keyChar = std::tolower(static_cast<unsigned char>(key[keyIndex % keyLen]));
            int shift = keyChar - 'a';

            int pos = (c - base - shift + 26) % 26;
            result += static_cast<char>(base + pos);

            keyIndex++;
        } else {
            result += c;
        }
    }
    return result;
}

int main() {
    std::string text, key;

    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    std::cout << "Enter key: ";
    std::getline(std::cin, key);

    if (key.empty()) {
        std::cout << "Key cannot be empty.\n";
        return 1;
    }

    std::string encrypted = vigenereEncrypt(text, key);
    std::string decrypted = vigenereDecrypt(encrypted, key);

    std::cout << "\nOriginal:  " << text << "\n";
    std::cout << "Encrypted: " << encrypted << "\n";
    std::cout << "Decrypted: " << decrypted << "\n";

    return 0;
}