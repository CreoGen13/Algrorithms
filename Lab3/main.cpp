#include <iostream>
#include "profileapi.h"
#include "Sort.h"

double PCFreq = 0.0;
__int64 CounterStart = 0;

constexpr int kLength = 30;
constexpr int kRepeats = 100000;
int arr[kLength];

void countFrequency()
{
    LARGE_INTEGER li;
    if (!QueryPerformanceFrequency(&li))
        std::cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double (li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
}
double getFrequency()
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return double (li.QuadPart - CounterStart) / PCFreq;
}
void unsortArr()
{
    for (int i = 0; i < kLength; ++i)
        arr[i] = kLength - i;
}

int main() {
    Sort sort;

    for (int i = 1; i <= kLength; ++i)
    {
        double insertTime = 0.0, quickTime = 0.0, mixedTime = 0.0;

        for (int k = 0; k < kRepeats; ++k)
        {
            // Insertion
            unsortArr();
            countFrequency();
            sort.insertionSort(arr, arr + i - 1, [](int a, int b) { return a < b; });
            insertTime += getFrequency();

            // Quick
            unsortArr();
            countFrequency();
            sort.quickSort(arr, arr + i - 1, [](int a, int b) { return a < b; });
            quickTime += getFrequency();

            // Mixed
            unsortArr();
            countFrequency();
            sort.mixedSort(arr, arr + i - 1, [](int a, int b) { return a < b; });
            mixedTime += getFrequency();
        }
        std::cout << "Iteration " << i << ": " << "\t" << insertTime << "\t\t" << quickTime << "\t\t" << mixedTime;
        //std::cout << i << ";"<< insertTime << ";" << quickTime << ";" << mixedTime << ";";
        //std::cout << mixedTime;
        std::cout << std::endl;
    }

    return 0;
}
