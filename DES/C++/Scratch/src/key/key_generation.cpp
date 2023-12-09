#include <iostream>
#include <random>
#include <bitset>

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


void generateSubkeys(const std::bitset<64>& key, std::bitset<48> subkeys[16]) {
        // Permutation choice 1 (PC-1)
    const int pc1[56] = { 57, 49, 41, 33, 25, 17, 9,
                          1, 58, 50, 42, 34, 26, 18,
                          10, 2, 59, 51, 43, 35, 27,
                          19, 11, 3, 60, 52, 44, 36,
                          63, 55, 47, 39, 31, 23, 15,
                          7, 62, 54, 46, 38, 30, 22,
                          14, 6, 61, 53, 45, 37, 29,
                          21, 13, 5, 28, 20, 12, 4 };

    // Permutation choice 2 (PC-2)
    const int pc2[48] = { 14, 17, 11, 24, 1, 5,
                          3, 28, 15, 6, 21, 10,
                          23, 19, 12, 4, 26, 8,
                          16, 7, 27, 20, 13, 2,
                          41, 52, 31, 37, 47, 55,
                          30, 40, 51, 45, 33, 48,
                          44, 49, 39, 56, 34, 53,
                          46, 42, 50, 36, 29, 32 };

    // Apply PC-1
    std::bitset<56> permutedKey;
    for (int i = 0; i < 56; ++i) {
        permutedKey[i] = key[pc1[i] - 1];
    }

    // Split the permuted key into two halves
    std::bitset<28> leftHalf, rightHalf;
    for (int i = 0; i < 28; ++i) {
        leftHalf[i] = permutedKey[i];
        rightHalf[i] = permutedKey[i + 28];
    }

    // Generate subkeys
    for (int round = 0; round < 16; ++round) {
        // Perform circular left shift
        leftHalf = (leftHalf << 1) | (leftHalf >> 27);
        rightHalf = (rightHalf << 1) | (rightHalf >> 27);

        // Combine halves
        std::bitset<56> roundKey;
        for (int i = 0; i < 28; ++i) {
            roundKey[i] = leftHalf[i];
            roundKey[i + 28] = rightHalf[i];
        }

        // Apply PC-2 to generate the subkey
        for (int i = 0; i < 48; ++i) {
            subkeys[round][i] = roundKey[pc2[i] - 1];
        }
    }
}

int main() {
    // Generate a 64-bit key
    std::bitset<64> key = genKey();

    // Array to store 16 subkeys, each 48 bits long
    std::bitset<48> subkeys[16];

    // Generate subkeys
    generateSubkeys(key, subkeys);

    // Display the generated subkeys
    for (int i = 0; i < 16; ++i) {
        std::cout << "Subkey " << i + 1 << ": " << subkeys[i] << std::endl;
    }

    return 0;
}

