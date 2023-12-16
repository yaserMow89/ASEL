#include <iostream>
#include <string>
#include <random>
#include <bitset>
using namespace std;

// Suplementry files
#include "key_gen.cpp"
// #include "enc.cpp"
// #include "dec.cpp"


int main () {
  std::string my_key = genKey(); 
  // std::string my_key = "0001001100110100010101110111100110011011101111001101111111110001";

  generate_keys(my_key);

  // Access the generated keys using get_key function
    for (int i = 0; i < 16; ++i) {
        std::string subkey = get_key(i);
        std::cout << "Subkey " << i + 1 << ": " << subkey << std::endl;
    }
  
  return 0;

}


