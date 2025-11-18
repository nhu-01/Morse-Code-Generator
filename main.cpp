#include <iostream>
#include <string>
#include "morse_tree.h"

int main() {
    MorseTree<char> tree("morse_table.txt");

    std::string input;

    std::cout << "Morse Code Translator (type 'exit' to quit)\n";

    while (true) {
        std::cout << "\nEnter text: ";
        std::getline(std::cin, input);

        if (input == "exit") break; // type 'exit' to quit

        std::string encoded = tree.encodeText(input);
        std::cout << "Morse Code: " << encoded << std::endl;

        std::string decoded = tree.decodeText(encoded);
        std::cout << "Decoded text: " << decoded << std::endl;
    }

    std::cout << "Goodbye!\n";
    return 0;
}


