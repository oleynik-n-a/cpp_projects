#include "caesar_cipher.h"

std::string Decipher(const std::string& cipher, size_t shift) {
        std::string decipher;
        for (int i = 0; i < static_cast<int>(cipher.length()); ++i) {
            decipher.push_back(cipher[i] - static_cast<int>(shift) >= 'A' ?
                               static_cast<char>(cipher[i] - static_cast<int>(shift)) :
                               static_cast<char>('Z' - 'A' + cipher[i] + 1 - static_cast<int>(shift)));
        }
        return decipher;
}
