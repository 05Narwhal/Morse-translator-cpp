#ifndef MORSE_DECODER_HPP
#define MORSE_DECODER_HPP

#include <iostream>
#include <vector>

std::string decodeMorse(std::string morse);
std::string decryptMorse(std::string input, char dot = '.', char dash = '=');
std::string textToMorse(const std::string& text);
void copyToClipboard(const std::string& text);
std::string getTextFromClipboard();
bool isMorseCode(const std::string& text);
bool containsMorseCode(const std::string& text);

#endif // MORSE_DECODER_HPP
