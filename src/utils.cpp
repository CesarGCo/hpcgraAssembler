#include <utils.h>

std::string formatToBinary(int number, int width) {

    std::string binaryString = std::bitset<32>(number).to_string(); 
    binaryString = binaryString.substr(binaryString.size() - width);

    return binaryString;
}

int bitsFunct(int n){

    if(n < 2){
        return 1;
    } else {
        return static_cast<int>(std::ceil(std::log2(n)));
    }
}

int binaryStringToInt(const std::string& binaryStr) {
    return std::bitset<32>(binaryStr).to_ulong();
}

int max(int n1, int n2){
    return (n1 > n2) ? n1 : n2;
}

