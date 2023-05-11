#include<iostream>
#include<cstring>
#include<cassert>
using namespace std;

// Function to rotate bits of a 32-bit integer to the right
uint32_t RotateRight(uint32_t x, size_t numOfBitsToBeShifted)
{
    return (x >> numOfBitsToBeShifted) | (x << (32 - numOfBitsToBeShifted));
}

// Function to shift bits of a 32-bit integer to the right
uint32_t ShiftRight(uint32_t x, size_t numOfBitsToBeShifted)
{
    return x >> numOfBitsToBeShifted;
}

// Function implementing the "choice" operation
uint32_t Choice(uint32_t x, uint32_t y, uint32_t z)
{
    // If a bit in x has a value of "1", the resulting bit will have the value y has at that position,
    // else if the value is "0", the result will take the value of z at that place
    return (x & y) ^ (~x & z);
}

// Function implementing the "majority" operation
uint32_t Majority(uint32_t x, uint32_t y, uint32_t z)
{
    // The result takes the bit which occurs more frequently among x, y, z.
    // For example: [x0=1, y0=1, z0=0] => [res0=0]
    return (x & y) ^ (x & z) ^ (y & z);
}

// Function implementing the epsilon0 operation
uint32_t Epsilon0(uint32_t x)
{
    return RotateRight(x, 2) ^ RotateRight(x, 13) ^ RotateRight(x, 22);
}

// Function implementing the epsilon1 operation
uint32_t Epsilon1(uint32_t x)
{
    return RotateRight(x, 6) ^ RotateRight(x, 11) ^ RotateRight(x, 25);
}

// Function implementing the sigma0 operation
uint32_t Sigma0(uint32_t x)
{
    return RotateRight(x, 7) ^ RotateRight(x, 18) ^ ShiftRight(x, 3);
}

// Function implementing the sigma1 operation
uint32_t Sigma1(uint32_t x)
{
    return RotateRight(x, 17) ^ RotateRight(x, 19) ^ ShiftRight(x, 10);
}

// Function to swap endianness of a 32-bit value
uint32_t swapE32(uint32_t value)
{
    uint32_t x = value;
    x = (x & 0xffff0000) >> 16 | (x & 0x0000ffff) << 16;
    x = (x & 0xff00ff00) >> 8 | (x & 0x00ff00ff) << 8;
    return x;
}

// Function to swap endianness of a 64-bit value
uint64_t swapE64(uint64_t value)
{
    uint64_t x = value;
    x = (x & 0xffffffff00000000) >> 32 | (x & 0x00000000ffffffff) << 32;
    x = (x & 0xffff0000ffff0000) >> 16 | (x & 0x0000ffff0000ffff) << 16;
    x = (x & 0xff00ff00ff00ff00) >> 8 | (x & 0x00ff00ff00ff00ff) << 8;
    return x;
}


// Function to convert binary data to hexadecimal string
string hexOutput(void* buffer, size_t len)
 {
    string hexString;

    for(size_t i = 0; i < len; i++) 
    {
        char buf[3];
        sprintf(buf, "%02x", ((char*)buffer)[i] & 0xff);
        hexString += buf;
    }

    return hexString;
}


// Hash function implementation
string Hash(string input)
{   
    const char* cstr = input.c_str();
    size_t inpLength = input.length();

    char* msg =  new char[inpLength+1];
    memcpy(msg , cstr , inpLength+1);

        uint32_t K[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    }; // Constants 

    
    uint32_t H[] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };//initial Hash values
    
    // Calculate the length of the input message
    size_t len = strlen(msg);

    // Calculate the total length of the padded message
    uint64_t l = len * sizeof(char) * 8;
    size_t k = (448 - l - 1) % 512;
    if(k < 0) k += 512;
    assert((l+1+k) % 512 == 448);
    size_t msgSize = l + 1 + k + 64;

    // Allocate memory for the padded message
    char* msgPad = (char*)calloc((msgSize / 8), sizeof(char));
    
    // Copy the original message into the padded message
    memcpy(msgPad, msg, len);
    
    // Append the '1' bit to the end of the padded message
    msgPad[len] = 0x80;
    
    // Convert the length to big-endian and append it to the padded message
    l = swapE64(l);
    memcpy(msgPad+(msgSize/8)-8, &l, 8);
 

    // Calculate the number of 512-bit blocks in the padded message
    size_t N = msgSize / 512;

    
    uint32_t v[8];
    uint32_t W[64];
    uint32_t* M = (uint32_t*)msgPad;
    uint32_t T1, T2;
    
    // Convert the words in each 512-bit block to big-endian
    for(size_t i = 0; i < N * 16; i++) {
        M[i] = swapE32(M[i]);
    }
  
  
    for(size_t i = 0; i < N; i++) {
        
        // 1. Prepare the message schedule
        for(size_t t = 0; t < 16; t++) {
            W[t] = M[i*16 + t];
           
        }
        for(size_t t = 16; t < 64; t++) {
            W[t] = Sigma1(W[t-2]) + W[t-7] + Sigma0(W[t-15]) + W[t-16];
        }

        // 2. Initialize the working variables
        for(size_t t = 0; t < 8; t++) {
            v[t] = H[t];
        }

        // 3. Perform the main hash computation
        for(size_t t = 0; t < 64; t++) {
            // a=0 b=1 c=2 d=3 e=4 f=5 g=6 h=7
            T1 = v[7] + Epsilon1(v[4]) + Choice(v[4], v[5], v[6]) + K[t] + W[t];
            T2 = Epsilon0(v[0]) + Majority(v[0], v[1], v[2]);

            v[7] = v[6];
            v[6] = v[5];
            v[5] = v[4];
            v[4] = v[3] + T1;
            v[3] = v[2];
            v[2] = v[1];
            v[1] = v[0];
            v[0] = T1 + T2;
        }
        
        // 4. Update the hash values
        for(size_t t = 0; t < 8; t++) {
            H[t] += v[t];
        }


    }
    
    // Initialize an empty string to store the final hash value
    string hash="";
        
    // Convert each 32-bit word in the hash array to big-endian and append its hexadecimal representation to the hash string
    for(size_t i = 0; i < 8; i++) {
        H[i] = swapE32(H[i]);
        hash += hexOutput(&H[i], 4);
    }

return hash;

}