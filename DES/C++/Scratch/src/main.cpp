#include <iostream>

#include "key_generation.cpp"   // Include the implementation directly
#include "enc.cpp"

int main() {
    std::string key = genKey();
    std::string subkeys[16];
    generateSubkeys(key, subkeys);

    // std::cout << "Generated Subkeys:\n";
    // for (int i = 0; i < 16; ++i) {
    //     std::cout << "Subkey " << i + 1 << ": " << subkeys[i] << '\n';
    // }

    // Get input from the user
    std::cout << "Enter your message:\n";
    std::string userMessage;
    std::getline(std::cin, userMessage);



    return 0;
}
