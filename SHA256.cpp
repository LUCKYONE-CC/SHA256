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

int main() {
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

    for (int i = 0; i < 64; i++) {
		length = binaryStringLength;
		binaryStringPadded += (length >> i) & 1 ? '1' : '0';
	}

    string asciiValueOfBinaryStringLength = getAsciiBinary(length);

    binaryStringPadded += asciiValueOfBinaryStringLength;

    cout << binaryStringPadded << endl;

    return 0;
}