#include <iostream>

#include <iomanip>

#include <vector>

#include <cstring>

using namespace std;

const uint8_t sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

const uint8_t rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};


class AES256 {
    public: AES256(const uint8_t * key) {
        KeyExpansion(key);
    }

    void EncryptBlock(uint8_t * block) {
        AddRoundKey(block, roundKeys);

        for (int i = 1; i < 14; ++i) {
            SubBytes(block);
            ShiftRows(block);
            MixColumns(block);
            AddRoundKey(block, roundKeys + i * 16);
        }

        SubBytes(block);
        ShiftRows(block);
        AddRoundKey(block, roundKeys + 14 * 16);
    }

    void DecryptBlock(uint8_t * block) {
        AddRoundKey(block, roundKeys + 14 * 16);

        for (int i = 13; i > 0; --i) {
            InvShiftRows(block);
            InvSubBytes(block);
            AddRoundKey(block, roundKeys + i * 16);
            InvMixColumns(block);
        }

        InvShiftRows(block);
        InvSubBytes(block);
        AddRoundKey(block, roundKeys);
    }

    private: uint8_t roundKeys[240];

    void KeyExpansion(const uint8_t * key) {
        memcpy(roundKeys, key, 32);

        uint8_t temp[4];
        uint8_t i = 1;

        for (int j = 32; j < 240; j += 4) {
            memcpy(temp, roundKeys + j - 4, 4);

            if (j % 32 == 0) {
                RotWord(temp);
                SubWord(temp);
                temp[0] ^= rcon[i++];
            } else if (j % 32 == 16) {
                SubWord(temp);
            }

            for (int k = 0; k < 4; ++k) {
                roundKeys[j + k] = roundKeys[j + k - 32] ^ temp[k];
            }
        }
    }

    void SubBytes(uint8_t * block) {
        for (int i = 0; i < 16; ++i) {
            block[i] = sbox[block[i]];
        }
    }

    void ShiftRows(uint8_t * block) {
        uint8_t temp;

        temp = block[1];
        block[1] = block[5];
        block[5] = block[9];
        block[9] = block[13];
        block[13] = temp;

        temp = block[2];
        block[2] = block[10];
        block[10] = temp;
        temp = block[6];
        block[6] = block[14];
        block[14] = temp;

        temp = block[3];
        block[3] = block[15];
        block[15] = block[11];
        block[11] = block[7];
        block[7] = temp;
    }
    void MixColumns(uint8_t * block) {
        for (int i = 0; i < 16; i += 4) {
            uint8_t a = block[i];
            uint8_t b = block[i + 1];
            uint8_t c = block[i + 2];
            uint8_t d = block[i + 3];

            block[i] = gfmult(a, 2) ^ gfmult(b, 3) ^ c ^ d;
            block[i + 1] = a ^ gfmult(b, 2) ^ gfmult(c, 3) ^ d;
            block[i + 2] = a ^ b ^ gfmult(c, 2) ^ gfmult(d, 3);
            block[i + 3] = gfmult(a, 3) ^ b ^ c ^ gfmult(d, 2);
        }
    }

    void AddRoundKey(uint8_t * block,
        const uint8_t * roundKey) {
        for (int i = 0; i < 16; ++i) {
            block[i] ^= roundKey[i];
        }
    }

    void InvSubBytes(uint8_t * block) {
        for (int i = 0; i < 16; ++i) {
            block[i] = sbox[block[i]];
        }
    }

    void InvShiftRows(uint8_t * block) {
        uint8_t temp;

        temp = block[13];
        block[13] = block[9];
        block[9] = block[5];
        block[5] = block[1];
        block[1] = temp;

        temp = block[10];
        block[10] = block[2];
        block[2] = temp;
        temp = block[14];
        block[14] = block[6];
        block[6] = temp;

        temp = block[7];
        block[7] = block[11];
        block[11] = block[15];
        block[15] = block[3];
        block[3] = temp;
    }

    void InvMixColumns(uint8_t * block) {
        for (int i = 0; i < 16; i += 4) {
            uint8_t a = block[i];
            uint8_t b = block[i + 1];
            uint8_t c = block[i + 2];
            uint8_t d = block[i + 3];

            block[i] = gfmult(a, 0x0e) ^ gfmult(b, 0x0b) ^ gfmult(c, 0x0d) ^ gfmult(d, 0x09);
            block[i + 1] = gfmult(a, 0x09) ^ gfmult(b, 0x0e) ^ gfmult(c, 0x0b) ^ gfmult(d, 0x0d);
            block[i + 2] = gfmult(a, 0x0d) ^ gfmult(b, 0x09) ^ gfmult(c, 0x0e) ^ gfmult(d, 0x0b);
            block[i + 3] = gfmult(a, 0x0b) ^ gfmult(b, 0x0d) ^ gfmult(c, 0x09) ^ gfmult(d, 0x0e);
        }
    }

    void RotWord(uint8_t * word) {
        uint8_t temp = word[0];
        word[0] = word[1];
        word[1] = word[2];
        word[2] = word[3];
        word[3] = temp;
    }

    void SubWord(uint8_t * word) {
        for (int i = 0; i < 4; ++i) {
            word[i] = sbox[word[i]];
        }
    }

    uint8_t gfmult(uint8_t a, uint8_t b) {
        uint8_t p = 0;
        uint8_t hi_bit_set;
        for (int i = 0; i < 8; ++i) {
            if (b & 1)
                p ^= a;
            hi_bit_set = a & 0x80;
            a <<= 1;
            if (hi_bit_set)
                a ^= 0x1b;
            b >>= 1;
        }
        return p;
    }
};

int main() {
    uint8_t key[32] = {
        0x60, 0x3d, 0xeb, 0x10, 0x15, 0xca, 0x71, 0xbe,
        0x2b, 0x73, 0xae, 0xf0, 0x85, 0x7d, 0x77, 0x81,
        0x1f, 0x35, 0x2c, 0x07, 0x3b, 0x61, 0x08, 0xd7,
        0x2d, 0x98, 0x10, 0xa3, 0x09, 0x14, 0xdf, 0xf4
    };
    uint8_t plaintext[16] = {
        0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
        0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34
    };

    AES256 aes(key);

    aes.EncryptBlock(plaintext);
    aes.DecryptBlock(plaintext);

    return 0;
}