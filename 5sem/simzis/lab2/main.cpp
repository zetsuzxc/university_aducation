#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>

std::string generateKey(int length) {
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::string key = "";
    for (int i = 0; i < length; i++) {
        key += alphabet[rand() % alphabet.size()];
    }
    return key;
}

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
    srand(static_cast<unsigned int>(time(0)));

    std::string text;
    std::cout << "Enter text: ";
    std::getline(std::cin, text);

    int keyLength;
    std::cout << "Enter key length (recommended 16+): ";
    std::cin >> keyLength;

    if (keyLength < 1) {
        std::cout << "Key length must be at least 1.\n";
        return 1;
    }

    std::string key = generateKey(keyLength);
    std::cout << "Generated key: " << key << "\n";

    std::string encrypted = vigenereEncrypt(text, key);
    std::string decrypted = vigenereDecrypt(encrypted, key);

    std::cout << "\nOriginal:  " << text << "\n";
    std::cout << "Encrypted: " << encrypted << "\n";
    std::cout << "Decrypted: " << decrypted << "\n";

    return 0;
}