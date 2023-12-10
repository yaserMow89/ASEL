// Including dependancies
#include <iostream>
#include <string>
#include <random>
#include <bitset>
using namespace std;


// Function to do a circular left shift by 1
string shift_left_once(string key_chunk){ 
    string shifted="";  
        for(int i = 1; i < 28; i++){ 
            shifted += key_chunk[i]; 
        } 
        shifted += key_chunk[0];   
    return shifted; 
} 
// Function to do a circular left shift by 2
string shift_left_twice(string key_chunk){ 
    string shifted=""; 
    for(int i = 0; i < 2; i++){ 
        for(int j = 1; j < 28; j++){ 
            shifted += key_chunk[j]; 
        } 
        shifted += key_chunk[0]; 
        key_chunk= shifted; 
        shifted =""; 
    } 
    return key_chunk; 
}
void generateSubkeys(string key){
  // Array to hold the 16 keys
  string round_keys[16];
	// The PC1 table 
	int pc1[56] = {
	57,49,41,33,25,17,9, 
	1,58,50,42,34,26,18, 
	10,2,59,51,43,35,27, 
	19,11,3,60,52,44,36,		 
	63,55,47,39,31,23,15, 
	7,62,54,46,38,30,22, 
	14,6,61,53,45,37,29, 
	21,13,5,28,20,12,4 
	};
	// The PC2 table
	int pc2[48] = { 
	14,17,11,24,1,5, 
	3,28,15,6,21,10, 
	23,19,12,4,26,8, 
	16,7,27,20,13,2, 
	41,52,31,37,47,55, 
	30,40,51,45,33,48, 
	44,49,39,56,34,53, 
	46,42,50,36,29,32 
	}; 
	// 1. Compressing the key using the PC1 table
	string perm_key =""; 
	for(int i = 0; i < 56; i++){ 
		perm_key+= key[pc1[i]-1]; 
	} 
  cout << perm_key << endl;
	// 2. Dividing the result into two equal halves
	string left= perm_key.substr(0, 28); 
	string right= perm_key.substr(28, 28); 
	// Generating 16 keys
	for(int i=0; i<16; i++){ 
		// 3.1. For rounds 1, 2, 9, 16 the key_chunks
		// are shifted by one.
		if(i == 0 || i == 1 || i==8 || i==15 ){
			left= shift_left_once(left); 
			right= shift_left_once(right);
		} 
		// 3.2. For other rounds, the key_chunks
		// are shifted by two
		else{
			left= shift_left_twice(left); 
			right= shift_left_twice(right);
		}
	// 4. The chunks are combined
	string combined_key = left + right;
	string round_key = ""; 
	// 5. Finally, the PC2 table is used to transpose
	// the key bits
	for(int i = 0; i < 48; i++){ 
		round_key += combined_key[pc2[i]-1]; 
	}   
	round_keys[i] = round_key;
		cout<<"Key "<<i+1<<": "<<round_keys[i]<<endl; 
	} 

}

std::string genKey() {
    const int keySize = 64;
    std::bitset<keySize> keyBits;

    // Use a random device as a source of entropy
    std::random_device rd;

    // Use a random engine with the random device as a seed
    std::default_random_engine eng(rd());

    // Use a uniform distribution to generate random integers (bits) in the range [0, 1]
    std::uniform_int_distribution<int> dist(0, 1);

    // Generate and store random bits in the bitset
    for (int i = 0; i < keySize; ++i) {
        keyBits[i] = dist(eng);
    }

    // Convert the bitset to a string
    return keyBits.to_string();
}


// int main(){  
  
// // string key = "0001001100110100010101110111100110011011101111001101111111110001";
// // The Above key is for debugging: and it should come out with the following subkeys: 
// // The Initial permuted key is: 11110000110011001010101011110101010101100110011110001111
// // Key 1: 000110110000001011101111111111000111000001110010
// // Key 2: 011110011010111011011001110110111100100111100101
// // Key 3: 010101011111110010001010010000101100111110011001
// // Key 4: 011100101010110111010110110110110011010100011101
// // Key 5: 011111001110110000000111111010110101001110101000
// // Key 6: 011000111010010100111110010100000111101100101111
// // Key 7: 111011001000010010110111111101100001100010111100
// // Key 8: 111101111000101000111010110000010011101111111011
// // Key 9: 111000001101101111101011111011011110011110000001
// // Key 10: 101100011111001101000111101110100100011001001111
// // Key 11: 001000010101111111010011110111101101001110000110
// // Key 12: 011101010111000111110101100101000110011111101001
// // Key 13: 100101111100010111010001111110101011101001000001
// // Key 14: 010111110100001110110111111100101110011100111010
// // Key 15: 101111111001000110001101001111010011111100001010
// // Key 16: 110010110011110110001011000011100001011111110101
  
//   std::string key = genKey(); 
//   generateSubkeys(key);
// } 