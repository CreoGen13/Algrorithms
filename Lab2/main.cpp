#include <iostream>
#include <string>

#include "DynamicArray.h"

using namespace std;

int main() {
    DynamicArray <std::string> arr;
    for (int i = 0; i < 30; i++)
        arr.insert("good");
    arr.insert(29, "morning");
    std::cout << arr[28] << "\t" << arr[29];
}
