#include <iostream>
#include <string>
#include "morse_tree.h"

int main() {
    // Load Morse codes from your CSV file
    MorseTree<char> tree("morse_table.txt");

    std::string input;
    std::cout << "Type text to encode to Morse (letters A-Z, digits 0-9, spaces allowed): ";
    std::getline(std::cin, input);

    std::string encoded = tree.encodeText(input);
    std::cout << "Morse Code: " << encoded << std::endl;

    // Optional: decode back to text
    std::string decoded = tree.decodeText(encoded);
    std::cout << "Decoded text: " << decoded << std::endl;

    return 0;
}
