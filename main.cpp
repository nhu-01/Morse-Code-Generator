#include <iostream>
#include <string>
#include "morse_tree.h"
using namespace std;

int main() {
    MorseTree<char> tree("morse_table.txt"); // Load Morse table
    string input;

    cout << "Morse Code Generator — type 'exit' to quit\n";

    while (true) {
        cout << "\nEnter text or Morse code:\n> ";
        getline(cin, input);

        if (input == "exit") break;

        // Detect if input is Morse code
        bool isMorse = true;
        for (char ch : input) {
            if (ch != '.' && ch != '-' && ch != ' ' && ch != '/') {
                isMorse = false;
                break;
            }
        }

        if (isMorse) {
            string decoded = tree.decodeText(input);
            cout << "Decoded text: " << decoded << endl;
        } else {
            string encoded = tree.encodeText(input);
            cout << "Morse Code: " << encoded << endl;
        }
    }

    cout << "Goodbye!\n";
    return 0;
}

