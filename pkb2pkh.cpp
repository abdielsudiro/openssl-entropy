#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <fstream>
#include <iostream>
#include <iomanip>

int main() {
    const int keySize = 32;  // Bitcoin private keys are 32 bytes (256 bits)
    unsigned char buffer[keySize];

    // Open the private key file in binary mode
    std::ifstream inFile("random_byte.bin", std::ios::binary);
    if (!inFile) {
        std::cerr << "Failed to open random_byte.bin for reading." << std::endl;
        return 1;
    }

    // Read the binary data from the file
    inFile.read(reinterpret_cast<char*>(buffer), keySize);
    inFile.close();

    if (inFile.gcount() != keySize) {
        std::cerr << "Error: random_byte.bin does not contain a valid 32-byte random byte." << std::endl;
        return 1;
    }

    // Convert the buffer to a BIGNUM (big integer) for use as a private key
    BIGNUM* privKeyBN = BN_bin2bn(buffer, keySize, nullptr);
    if (!privKeyBN) {
        std::cerr << "Failed to convert buffer to BIGNUM." << std::endl;
        return 1;
    }

    // Create an EC_KEY structure to hold the private key for the secp256k1 curve
    EC_KEY* ecKey = EC_KEY_new_by_curve_name(NID_secp256k1);
    if (!ecKey) {
        std::cerr << "Failed to create EC_KEY object." << std::endl;
        BN_free(privKeyBN);
        return 1;
    }

    // Set the private key
    if (EC_KEY_set_private_key(ecKey, privKeyBN) != 1) {
        std::cerr << "Failed to set private key." << std::endl;
        EC_KEY_free(ecKey);
        BN_free(privKeyBN);
        return 1;
    }

    // Print the private key in hexadecimal format
    std::cout << "Bitcoin Private Key (Hex): ";
    for (int i = 0; i < keySize; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)buffer[i];
    }
    std::cout << std::endl;

    // Clean up
    EC_KEY_free(ecKey);
    BN_free(privKeyBN);

    return 0;
}
