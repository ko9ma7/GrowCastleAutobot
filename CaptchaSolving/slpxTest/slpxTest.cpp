
#include <iostream>
#include <bitset>
#include "Header.h"

void SetConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
std::string intToBinaryString(int number) {
    std::string binary = std::bitset<32>(number).to_string();
    return binary;
}

std::string insertSpacesAtIndexes(const std::string& binaryStr, const std::vector<int>& indexes) {
    std::string spacedBinary = binaryStr;
    int offset = 0;

    for (int index : indexes) {
        if (index + offset <= spacedBinary.size()) {
            spacedBinary.insert(index + offset, " ");
            offset++;
        }
    }

    return spacedBinary;
}

void printResult(int res) {

    std::bitset<32> binary(res);

    std::string binaryStr = intToBinaryString(res);

    std::vector<int> spaceIndexes = { 2, 14, 24, 29 };

    cout << res << endl;
    std::string spacedBinary = insertSpacesAtIndexes(binaryStr, spaceIndexes);
    std::cout << spacedBinary << std::endl;

    cout << "Answer: " << (res & 0b111) + 1 << endl;
    cout << "Resemblance: " << (((res >> 8) & 0b1111111111)) << "" << endl;
    cout << "Duration: " << (((res >> 17) & 0b111111111111)) << "ms." << endl;

}
int main(){


    int arr[] = { 1, 0, 0, 123123 };
    int size = sizeof(arr) / sizeof(int);

    int res = execute(arr, size);

    //int res = execute(arr, size);

    //for (int i = 0; i < 100; i++) {
        //SetConsoleColor(i);
        //cout << i << " TESTTESTTESTTESTTEST" << endl;
    //}
    //SetConsoleColor(7);

    printResult(res);
    getchar();
    return 0;

}