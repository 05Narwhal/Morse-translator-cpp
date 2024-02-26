#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include <regex>
#include <algorithm>
#include <cctype>

const std::vector<std::string> morseLib = {
    ".=",   // A
    "=...", // B
    "=.=.", // C
    "=..",  // D
    ".",    // E
    "..=.", // F
    "==.",  // G
    "....", // H
    "..",   // I
    ".===", // J
    "=.=",  // K
    ".=..", // L
    "==",   // M
    "=.",   // N
    "===",  // O
    ".==.", // P
    "==.=", // Q
    ".=.",  // R
    "...",  // S
    "=",    // T
    "..=",  // U
    "...=", // V
    ".==",  // W
    "=..=", // X
    "=.==", // Y 
    "==..", // Z  
    ".====",// 1
    "..===",// 2
    "...==",// 3
    "....=",// 4
    ".....",// 5 
    "=....",// 6
    "==...",// 7
    "===..",// 8
    "====.",// 9
    "=====" // 0   
};

const std::vector<std::string> morseABCLib = {
    "A",   // A
    "B",   // B
    "C",   // C
    "D",   // D
    "E",   // E
    "F",   // F
    "G",   // G
    "H",   // H
    "I",   // I
    "J",   // J
    "K",   // K
    "L",   // L
    "M",   // M
    "N",   // N
    "O",   // O
    "P",   // P
    "Q",   // Q
    "R",   // R
    "S",   // S
    "T",   // T
    "U",   // U
    "V",   // V
    "W",   // W
    "X",   // X
    "Y",   // Y 
    "Z",   // Z 
    "1",   // 1
    "2",   // 2
    "3",   // 3
    "4",   // 4
    "5",   // 5 
    "6",   // 6
    "7",   // 7
    "8",   // 8
    "9",   // 9
    "0"    // 0
};

std::string textToMorse(const std::string& text) {
    std::string morseCode;
    
    for (char c : text) {
        if (std::isalpha(c)) {
            char upperC = std::toupper(c);
            int index = upperC - 'A';
            if (index >= 0 && index < morseLib.size()) {
                morseCode += morseLib[index] + " ";
            } else {
                morseCode += "/ "; // For characters not in the Morse code library, add a slash
            }
        } else if (c == ' ') {
            morseCode += "/ "; // For spaces, add a slash
        }
    }
    
    return morseCode;
}

std::string decodeMorse(std::string morse) {
    for (int h{}; h < morseLib.size();h++) {
        if (morse == morseLib[h]) {
            return morseABCLib[h];
        }
    }
    return "";
}

void replaceChars(std::string& str, char target, char replacement) {
    for (char& c : str) {
        if (c == target) {
            c = replacement;
        }
    }
}

std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> substrings;
    std::istringstream iss(str);
    std::string token;
    
    while (std::getline(iss, token, delimiter)) {
        substrings.push_back(token);
    }
    
    return substrings;
}

std::string decryptMorse(std::string input, char dot = '.', char dash = '=') {
    if (dot != '.') {
        replaceChars(input, dot, '.');
    }
    if (dash != '=') {
        replaceChars(input, dash, '=');
    }

    std::vector<std::string> words = splitString(input, '/');
    std::vector<std::vector<std::string>> letters = {};

    std::vector<std::string> wordsNew = {};
    std::string wordsNewInner = "";

    for (auto &elem : words) {
        letters.push_back(splitString(elem , ' '));
    }

    for (auto &outer : letters) {
        wordsNewInner = "";
        for (auto &inner : outer) {
            wordsNewInner += decodeMorse(inner);
        }
        wordsNew.push_back(wordsNewInner);
    }

    std::string result = "";

    for (auto &words : wordsNew) {
        result += " " + words;
    }

    return result;
}

void copyToClipboard(const std::string& text) {
    std::string command = "echo \"" + text + "\" | pbcopy";
    int result = system(command.c_str());
    if (result == 0) {
        std::cout << "Text copied to clipboard successfully." << std::endl;
    } else {
        std::cerr << "Failed to copy text to clipboard." << std::endl;
    }
}

std::string getTextFromClipboard() {
    std::string text;
    FILE* pipe = popen("pbpaste", "r");
    if (!pipe) {
        std::cerr << "Error: Failed to open pipe for reading." << std::endl;
        return "";
    }

    char buffer[128];
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            text += buffer;
        }
    }

    pclose(pipe);
    return text;
}

bool isMorseCode(const std::string& text) {
    // Regular expression to match Morse code pattern
    std::regex morseRegex("^[.=\\-/\\s]+$");
    return std::regex_match(text, morseRegex);
}

bool containsMorseCode(const std::string& text) {
    // Regular expression to match Morse code pattern
    std::regex morseRegex("[.=\\-/\\s]+");
    return std::regex_search(text, morseRegex);
}
