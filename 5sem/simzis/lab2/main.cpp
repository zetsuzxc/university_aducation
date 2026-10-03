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

    std::string encrypted = vigenereEncrypt(text, key);
    std::cout << "\nOriginal:  " << text << "\n";
    std::cout << "Encrypted: " << encrypted << "\n";

    // --- Атака полным перебором ---
    std::cout << "\n--- Brute force (key length 3) ---\n";

    long long attempts = 0;
    std::string foundKey = "";
    bool found = false;

    for (char c1 = 'a'; c1 <= 'z' && !found; ++c1) {
        for (char c2 = 'a'; c2 <= 'z' && !found; ++c2) {
            for (char c3 = 'a'; c3 <= 'z' && !found; ++c3) {
                std::string tryKey;
                tryKey += c1;
                tryKey += c2;
                tryKey += c3;

                attempts++;

                std::string decrypted = vigenereDecrypt(encrypted, tryKey);
                if (decrypted == text) {
                    foundKey = tryKey;
                    found = true;
                }
            }
        }
    }

    if (found) {
        std::cout << "Key found: " << foundKey << "\n";
        std::cout << "Attempts:  " << attempts << "\n";
        std::cout << "Decrypted: " << vigenereDecrypt(encrypted, foundKey) << "\n";
    } else {
        std::cout << "Key not found (tried " << attempts << " variants)\n";
    }

    return 0;
}