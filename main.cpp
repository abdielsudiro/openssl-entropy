#include <openssl/rand.h>
#include <fstream>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <cstring>  // Include cstring for memcpy

int main() {
    const int keySize = 32;  // 32 bytes (256 bits) for a Bitcoin private key
    unsigned char buffer[keySize];

    // Hard-coded entropy sources
    struct timeval tv;
    gettimeofday(&tv, nullptr);  // Get the current time
    double timestamp = tv.tv_sec + (tv.tv_usec / 1000000.0);  // Convert to seconds with microseconds as decimal

    pid_t pid = getpid();       // Get the current process ID
    int mouseMovement = 12345;  // Example hard-coded mouse movement value

    // Combine entropy sources into a single buffer for RAND_add
    unsigned char entropy[16];  // Example size; adjust as needed
    memcpy(entropy, &timestamp, sizeof(timestamp));
    memcpy(entropy + sizeof(timestamp), &pid, sizeof(pid));
    memcpy(entropy + sizeof(timestamp) + sizeof(pid), &mouseMovement, sizeof(mouseMovement));

    // Add entropy to OpenSSL's randomness pool
    RAND_add(entropy, sizeof(entropy), 1.5);  // Entropy estimate of 8.0, adjust as needed

    // Generate 32 random bytes
    if (RAND_bytes(buffer, keySize) != 1) {
        std::cerr << "Failed to generate random bytes." << std::endl;
        return 1;
    }

    // Open a file in binary mode
    std::ofstream outFile("random_byte.bin", std::ios::binary);
    if (!outFile) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }

    // Write the binary data to the file
    outFile.write(reinterpret_cast<const char*>(buffer), keySize);

    // Close the file
    outFile.close();

    std::cout << "Random byte saved to random_byte.bin" << std::endl;
    return 0;
}
