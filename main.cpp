#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>

#include "lib/functions.hpp"

using namespace std;

int main() {
    std::string clipboardText = getTextFromClipboard();
    bool morseCheck = false;

    if (isMorseCode(clipboardText)) {
        std::cout << "Input is Morse code." << std::endl;
        morseCheck = true;
        
    } else {
        std::cout << "Input is normal writing." << std::endl;
        morseCheck = false;
    }

    if (morseCheck == true) {
        std::string decrypted = decryptMorse(clipboardText, '.', '-');

        std::cout << decrypted << std::endl;
        copyToClipboard(decrypted);
    }
    else {
        std::string encrypted = textToMorse(clipboardText);

        std::cout << encrypted << std::endl;
        copyToClipboard(encrypted);
    }

    return 0;
}