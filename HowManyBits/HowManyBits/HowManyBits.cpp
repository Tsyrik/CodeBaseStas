#include <iostream>

int main()
{
    int counter = 0;
    int num = 247386;
  

    int arr[(sizeof(num) * 8)] = {};

    for (int i = (sizeof(num) * 8); i >0 ; --i) {
        if (num & (1 << i)) {
            ++counter;
            arr[i] = 1;
            std::cout << arr[i];
        }
        else {
            arr[i] = 0;
            std::cout << arr[i];
        }
    }
    std::cout << counter<<std::endl;


    //    unsigned char x = (1 << 2) | (1 << 3) | (1 << 7);
    //    if (x & (1 << 2)) {  /* во второй бит вписана единица */ }
    //    if (x & (1 << 3)) {  /* в третий бит вписана единица */ }
    //    if (x & (1 << 7)) {  /* в седьмой бит вписана единица */ }
}