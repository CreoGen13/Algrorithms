#ifndef LAB1_SORT_H
#define LAB1_SORT_H
#include <fstream>

constexpr int kSwitchToInsertion = 8;

class Sort {

public:
    template<typename T,typename Compare>
    void insertionSort(T* first, T* last, Compare comp)
    {
        if (first == last)
            return;
        for (T* i = first + 1; i <= last; ++i)
        {
            T tempValue = std::move(*i);
            T* j = i - 1;
            while (j >= first && comp(tempValue, *j))
            {
                *(j + 1) = std::move(*j);
                j --;
            }
            *(j + 1) = std::move(tempValue);
        }
    }

    template<typename T, typename Compare>
    void quickSort(T* first, T* last, Compare comp) {
        T* p;
        while (last - first > 0)
        {
            p = partition(first, last, comp);

            if (p - first < last - p - 1)
            {
                quickSort(first, p, comp);
                first = p + 1;
            }
            else
            {
                quickSort(p + 1, last, comp);
                last = p;
            }
        }
    }

    template<typename T, typename Compare>
    void mixedSort(T* first, T* last, Compare comp) {
        T* p;
        while (last - first > 0)
        {
            if (last - first <= kSwitchToInsertion)
            {
                insertionSort(first, last, comp);
                return;
            }

            p = partition(first, last, comp);

            if (p - first < last - p)
            {
                mixedSort(first, p, comp);
                first = p + 1;
            }
            else
            {
                mixedSort(p + 1, last, comp);
                last = p;
            }
        }
    }

private:
    template<typename T, typename Compare>
    T* partition(T* first, T* last, Compare comp)
    {
        T pivot = choosePivot(first, (first + (last - first) / 2), last, comp);

        T* left = first;
        T* right = last;
        while (true)
        {
            while (comp(*left, pivot))
                left += 1;
            while (comp(pivot, *right))
                right -= 1;
            if (left >= right)
                break;
            std::swap(*left, *right);
            left += 1;
            right -= 1;
        }
        return right;
    }

    template<typename T, typename Compare>
    T choosePivot(T* left, T* middle, T* right, Compare comp)
    {
        if (comp(*right, *left))
            std::swap(*left, *right);
        if (comp(*middle, *left))
            std::swap(*left, *middle);
        if (comp(*right, *middle))
            std::swap(*right, *middle);
        return *middle;
    }
};


#endif //LAB1_SORT_H
