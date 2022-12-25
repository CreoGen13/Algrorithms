#include <iostream>

template <typename T>
class DynamicArray final {
public:
    // Iterator classes
    class Iterator
    {
        public:
            T& get() const;
            void set(const T& value);
            void next();
            bool hasNext() const;

            // To get iterators
            friend DynamicArray;
        private:
            DynamicArray* _itemsArray;
            int _direction;
            int _index;
    };
    class ConstIterator {
        public:
            const T &get() const;
            void next();
            bool hasNext() const;

            // To get iterators
            friend DynamicArray;
        private:
            const DynamicArray *_itemsArray;
            int _direction;
            int _index;
    };

    // Standard Constructors
    DynamicArray();
    DynamicArray(int capacity);

    // Constructors with other array
    DynamicArray(const DynamicArray& otherArray);
    DynamicArray(DynamicArray&& otherArray);

    // Destructor
    ~DynamicArray();

    int insert (const T& value);
    int insert (int index, const T& value);

    void remove (int index);

    // Overwriting operator []
    const T& operator[](int index) const;
    T& operator[](int index);

    // Overwriting operator =
    DynamicArray& operator=(DynamicArray otherArray);
    DynamicArray& operator=(DynamicArray&& otherArray);

    int size() const;

    Iterator iterator();
    ConstIterator iterator() const;
    Iterator reverseIterator();
    ConstIterator reverseIterator() const;

private:
    T* _itemsArray;
    int _currentCapacity;
    int _currentSize;
};

#include "DynamicArrayDefinition.hpp"