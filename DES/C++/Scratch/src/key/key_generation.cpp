#include <iostream>
#include <random>
#include <bitset>
#include <string>

using namespace std; 

std::bitset<64> genKey() {
   const int keySize = 64;
    std::bitset<64> key;

    // Use a random device as a source of entropy
    std::random_device rd;

    // Use a random engine with the random device as a seed
    std::default_random_engine eng(rd());

    // Use a uniform distribution to generate random integers (bits) in the range [0, 1]
    std::uniform_int_distribution<int> dist(0, 1);

    // Generate and store random bits in the key
    for (int i = 0; i < keySize; ++i) {
        key[i] = dist(eng);
    }

    // Display the generated key in binary form
    std::cout << "Generated Key (Binary): " << key << std::endl;

    return key;
}


void generateSubkeys(const std::string& key, std::string subkeys[16]) {
    // Permutation choice 1 (PC-1)
    const int pc1[56] = { 56, 48, 40, 32, 24, 16, 8,
                          0, 57, 49, 41, 33, 25, 17,
                          9, 1, 58, 50, 42, 34, 26,
                          18, 10, 2, 59, 51, 43, 35,
                          62, 54, 46, 38, 30, 22, 14,
                          6, 61, 53, 45, 37, 29, 21,
                          13, 5, 60, 52, 44, 36, 28,
                          20, 12, 4, 27, 19, 11, 3 };

    // Permutation choice 2 (PC-2)
    const int pc2[48] = { 13, 16, 10, 23, 0, 4,
                          2, 27, 14, 5, 20, 9,
                          22, 18, 11, 3, 25, 7,
                          15, 6, 26, 19, 12, 1,
                          40, 51, 30, 36, 46, 54,
                          29, 39, 50, 44, 32, 47,
                          43, 48, 38, 55, 33, 52,
                          45, 41, 49, 35, 28, 31 };

    // Apply PC-1
    std::string permutedKey(56, '0');  // Initialize with 56 '0' characters
    for (int i = 0; i < 56; ++i) {
        permutedKey[i] = key[pc1[i]];
    }

    std::cout << "Permuted Key (After PC-1): " << permutedKey << std::endl;

    // Split the permuted key into two halves
    std::string leftHalf = permutedKey.substr(0, 28);
    std::string rightHalf = permutedKey.substr(28);
  std::cout << leftHalf << std::endl;
  std::cout << rightHalf << std::endl;

    // Generate subkeys
    for (int round = 0; round < 16; ++round) {
        // Perform circular left shift
        leftHalf = leftHalf.substr(1) + leftHalf[0];
        rightHalf = rightHalf.substr(1) + rightHalf[0];

        // Combine halves
        std::string roundKey = leftHalf + rightHalf;

        // Apply PC-2 to generate the subkey
        subkeys[round].resize(48); // Resize to match the size of the subkey
        for (int i = 0; i < 48; ++i) {
            subkeys[round][i] = roundKey[pc2[i]];
        }
    }
}

int main() {
    // Manually define a 64-bit key for testing
    std::string key = "0001001100110100010101110111100110011011101111001101111111110001";

    // Array to store 16 subkeys, each as a string
    std::string subkeys[16];

    // Generate subkeys
    generateSubkeys(key, subkeys);

    // Display the generated subkeys
    for (int i = 0; i < 16; ++i) {
        std::cout << "K" << i + 1 << " = " << subkeys[i] << std::endl;
    }

    return 0;
}
