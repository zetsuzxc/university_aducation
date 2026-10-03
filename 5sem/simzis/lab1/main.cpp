// 2) Латиница строчные и прописные.
#include<iostream>
#include<string>
#include<cctype>

std::string getRandomStr(int range){
    std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result = "";
    for (int i = 0; i < range; i++){
        int index = rand() % alphabet.length();
        result += alphabet[index];
    }
    return result;
}

std::string toLowerString(std::string str){
    for (char &c : str){
        c = std::tolower(c);
    }
    return str;
}

std::string toUpperString(std::string str){
    for (char &c : str){
        c = std::toupper(c);
    }
    return str;
}

int main() {
    srand(time(0));
    int string_range = 0;
    std::cout << "Enter your string range: " << std::endl;
    std::cin >> string_range;
    std::cout << "Result: " << getRandomStr(string_range) << std::endl;
}
 