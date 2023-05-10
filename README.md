# SHA256-Hashing

![SHA256 Logo](sha256_logo.png)

Welcome to the SHA256-Hashing repository! This project provides a C++ implementation of the SHA-256 cryptographic hash function. SHA-256 is a widely used cryptographic hash algorithm that generates a 256-bit hash value.

## Features

- **Secure Hash Function**: The project includes a robust implementation of the SHA-256 algorithm, which takes an input message and produces a 256-bit hash value. It provides a strong cryptographic hash function that ensures data integrity and security.

- **Simple Integration**: The project consists of a `sha256.h` header file and a `sha256.cpp` source file that can be easily integrated into your C++ projects. The `sha256.h` file contains the necessary function declarations, while the `sha256.cpp` file contains the implementation of the SHA-256 algorithm.

- **Test Suite**: The project also includes a `test.cpp` file that contains a test suite to verify the correctness of the SHA-256 implementation. The test suite exercises various input cases and compares the computed hash values with expected values.

## Installation

To use the SHA256-Hashing library in your project, follow these steps:

1. Clone the repository: `git clone https://github.com/your-username/SHA256-Hashing.git`
2. Copy the `sha256.h` and `sha256.cpp` files into your project directory.
3. Include the `sha256.h` header file in your code: `#include "sha256.h"`
4. Compile your project, linking the `sha256.cpp` source file.

## Usage

To compute the SHA-256 hash of a message, follow these steps:

1. Include the `sha256.h` header file in your code: `#include "sha256.h"`
2. Call the `SHA256::hash` function, passing the message as a `std::string` parameter.
3. The function will return the computed SHA-256 hash value as a `std::string`.

Example usage:

```cpp
#include "sha256.h"
#include <iostream>

int main() {
    std::string message = "This is a test message.";
    std::string hash = SHA256::hash(message);

    std::cout << "SHA-256 Hash: " << hash << std::endl;

    return 0;
}


For more details on the usage of the SHA256-Hashing library, please refer to the documentation within the `sha256.h` file.

## Testing

The project includes a test suite in the `test.cpp` file to verify the correctness of the SHA-256 implementation. To run the tests, compile the `test.cpp` file and execute the resulting binary.

```shell
$ g++ -o test test.cpp
$ ./test

The test suite will validate the computed hash values against expected hash values for various input cases.

## Contributing

Contributions to the SHA256-Hashing project are welcome! If you have any improvements, bug fixes, or new features to add, please follow these steps:

1. Fork the repository.
2. Create a new branch: `git checkout -b feature/your-feature`
3. Commit your changes: `git commit -m 'Add your feature'`
4. Push to the branch: `git push origin feature/your-feature`
5. Submit a pull request.

## License

This project is licensed under the MIT License.

