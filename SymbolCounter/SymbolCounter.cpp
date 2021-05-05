#include <iostream>

int SymbolsCounter(const std::string& stringX, const char& charX) {
    int res = 0;
    for (int i = 0; i < stringX.size(); ++i) {
        if (stringX[i] == charX) {
            res = ++res;
        }
    };
    return res;
};

int main()
{

    std::string symbs = "Hellol";
    char check = 'l';
    int myRes = SymbolsCounter(symbs, check);
    std::cout << myRes << std::endl;
}