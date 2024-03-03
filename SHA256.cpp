#include <iostream>
#include <vector>
#include <string>
#include <bitset>

using namespace std;

string charToBinaryString(char c) {
    string binary = "";
    for (int i = 7; i >= 0; --i) {
        binary += ((c >> i) & 1) ? '1' : '0';
    }
    return binary;
}

vector<string> stringToAsciiBinary(const string& str) {
    vector<string> binaryStrings;
    for (char c : str) {
        binaryStrings.push_back(charToBinaryString(c));
    }
    return binaryStrings;
}

string getAsciiBinary(int value) {
    if (value < 0 || value > 127) {
        throw std::invalid_argument("Value must be between 0 and 127");
    }
    char asciiChar = static_cast<char>(value);

    std::bitset<8> binary(asciiChar);
    return binary.to_string();
}

unsigned int getFractionalPartOfCubeRootOfPrime(int prime) {
	double root = cbrt(prime);
	double fractionalPart = root - floor(root);
	return static_cast<unsigned int>(fractionalPart * UINT_MAX);
}

vector<int> getAllPrimesTo(int n) {
	vector<int> primes;
    for (int i = 2; i <= n; i++) {
		bool isPrime = true;
        for (int j = 2; j <= i / 2; j++) {
            if (i % j == 0) {
				isPrime = false;
				break;
			}
		}
        if (isPrime) {
			primes.push_back(i);
		}
	}
	return primes;
}

int main() {

#pragma region Constants
    //Initial hash values
    // (first 32 bits of the fractional parts of the square roots of the first 8 primes 2..19):
    unsigned int h0 = 0x6a09e667;
    unsigned int h1 = 0xbb67ae85;
    unsigned int h2 = 0x3c6ef372;
    unsigned int h3 = 0xa54ff53a;
    unsigned int h4 = 0x510e527f;
    unsigned int h5 = 0x9b05688c;
    unsigned int h6 = 0x1f83d9ab;
    unsigned int h7 = 0x5be0cd19;

    //Calculation of K0 to K63
    // (first 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311):

    vector<int> primes = getAllPrimesTo(311);
    vector<unsigned int> KSequence;

    for (int i = 0; i < 64; i++) {
        KSequence.push_back(getFractionalPartOfCubeRootOfPrime(primes[i]));
    }

    primes.clear();
#pragma endregion

    string text = "RedBlockBlue";
    vector<string> binaryStrings = stringToAsciiBinary(text);

    string binaryString = "";

    for (const auto& binStr : binaryStrings) {
        binaryString += binStr;
    }

    string binaryStringPadded = binaryString;

    int binaryStringLength = binaryString.length();

    int i = 1;

    while (binaryStringLength > 512 * i) {
        i++;
	}

    int paddedLength = 512 * i - 64 - binaryStringLength;

    binaryStringPadded += "1";

    for (int i = 0; i < paddedLength - 1; i++) {
		binaryStringPadded += "0";
	}

    int length = 0;

    string asciiValueOfBinaryStringLength = getAsciiBinary(length);

    int zeros = 64 - asciiValueOfBinaryStringLength.length();

    for (int i = 0; i < zeros; i++) {
		length = binaryStringLength;
		binaryStringPadded += (length >> i) & 1 ? '1' : '0';
	}

    binaryStringPadded += asciiValueOfBinaryStringLength;

    //Splitt padded input into 512-bit chunks
    vector<string> chunks;

    for (int i = 0; i < binaryStringPadded.length(); i += 512) {
		chunks.push_back(binaryStringPadded.substr(i, 512));
	}

    //Splitt each chunk into 16 32-bit words
    vector<vector<string>> words;

    for (const auto& chunk : chunks) {
		vector<string> chunkWords;
        for (int i = 0; i < chunk.length(); i += 32) {
			chunkWords.push_back(chunk.substr(i, 32));
		}
		words.push_back(chunkWords);
	}

    return 0;
}