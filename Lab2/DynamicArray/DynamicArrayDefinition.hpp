#include <iostream>
constexpr int kDefaultArrayCapacity = 8;

#pragma region Constructors
template<typename T>
DynamicArray<T>::DynamicArray() : _currentCapacity(kDefaultArrayCapacity), _currentSize(0) {
    _itemsArray = (T *) std::malloc(_currentCapacity * sizeof(T));
}

template<typename T>
DynamicArray<T>::DynamicArray(int capacity) : _currentCapacity(capacity), _currentSize(0) {
    if (_currentCapacity <= 0)
        _currentCapacity = kDefaultArrayCapacity;
    _itemsArray = (T *) std::malloc(_currentCapacity * sizeof(T));
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &otherArray) : _currentCapacity(otherArray._currentCapacity),
                                                                       _currentSize(otherArray._currentSize) {
    _itemsArray = (T *) std::malloc(_currentCapacity * sizeof(T));
    for (int i = 0; i < _currentSize; i++) {
        new(_itemsArray + i) T(otherArray._itemsArray[i]);
    }
}
template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T> &&otherArray) {
    _currentCapacity = otherArray._currentCapacity;
    _currentSize = otherArray._currentSize;
    _itemsArray = otherArray._itemsArray;
    otherArray._itemsArray = nullptr;
    otherArray._currentCapacity = 0;
    otherArray._currentSize = 0;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    for (int i = 0; i < _currentSize; i++)
        _itemsArray[i].~T();
    std::free(_itemsArray);
}
#pragma endregion
#pragma region MainFunctions
template<typename T>
int DynamicArray<T>::insert(const T &value) {
    if (_currentSize + 1 > _currentCapacity) {
        _currentCapacity *= 2;
        T *newItemsArray = (T *) std::malloc(_currentCapacity * sizeof(T));
        for (int i = 0; i < _currentSize; i++) {
            new(newItemsArray + i) T(std::move(_itemsArray[i]));
            _itemsArray[i].~T();
        }
        std::free(_itemsArray);
        _itemsArray = newItemsArray;
    }

    new(_itemsArray + _currentSize) T(value);
    _currentSize += 1;

    return _currentSize - 1;
}

template<typename T>
int DynamicArray<T>::insert(int index, const T &value) {
    if (index > 0 && index < _currentSize) {
        if (_currentSize + 1 > _currentCapacity) {
            _currentCapacity *= 2;
            T *newItemsArray = (T *) std::malloc(_currentCapacity * sizeof(T));
            for (int i = 0; i < _currentSize; i++) {
                new(newItemsArray + i) T(std::move(_itemsArray[i]));
                _itemsArray[i].~T();
            }
            std::free(_itemsArray);
            _itemsArray = newItemsArray;
        }
        new(_itemsArray + _currentSize) T(_itemsArray[_currentSize - 1]);
        //new(_itemsArray + _currentSize) T{};
        if (_currentSize > index) {
            for (int i = _currentSize; i > index; i--)
                _itemsArray[i] = std::move(_itemsArray[i - 1]);
        }
        _itemsArray[index] = value;
        _currentSize += 1;
        return index;
    }

    return -1;
}

template<typename T>
void DynamicArray<T>::remove(int index) {
    if (_currentSize > 0 && index >= 0 && index < _currentSize) {

        for (int i = index; i < _currentSize - 1; i++)
            _itemsArray[i] = std::move(_itemsArray[i + 1]);
        _itemsArray[_currentSize - 1].~T();
        _currentSize -= 1;
    }
}

template<typename T>
int DynamicArray<T>::size() const {
    return _currentSize;
}
#pragma endregion
#pragma region OverwritingOperators
template<typename T>
const T &DynamicArray<T>::operator[](int index) const {
    return _itemsArray[index];
}

template<typename T>
T &DynamicArray<T>::operator[](int index) {
    return _itemsArray[index];
}

template<typename T>
DynamicArray<T> &DynamicArray<T>::operator=(DynamicArray otherArray) {
    std::swap(_itemsArray, otherArray._itemsArray);
    std::swap(_currentSize, otherArray._currentSize);
    std::swap(_currentCapacity, otherArray._currentCapacity);
    return *this;
}

template<typename T>
DynamicArray<T> &DynamicArray<T>::operator=(DynamicArray &&otherArray) {
    if (this != &otherArray) {
        for (int i = 0; i < _currentSize; i++)
            _itemsArray[i].~T();
        std::free(_itemsArray);
        _currentCapacity = otherArray._currentCapacity;
        _currentSize = otherArray._currentSize;
        _itemsArray = otherArray._itemsArray;
        otherArray._itemsArray = nullptr;
        otherArray._currentCapacity = 0;
        otherArray._currentSize = 0;
    }

    return *this;
}
#pragma endregion
#pragma region IteratorFunctions
template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::iterator() {
    DynamicArray<T>::Iterator iterator;
    iterator._itemsArray = this;
    iterator._index = 0;
    iterator._direction = +1;
    return iterator;
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::reverseIterator() {
    DynamicArray<T>::Iterator iterator;
    iterator._itemsArray = this;
    iterator._index = _currentSize - 1;
    iterator._direction = -1;
    return iterator;
}



template<typename T>
T &DynamicArray<T>::Iterator::get() const {
    return (*_itemsArray)[_index];
}

template<typename T>
void DynamicArray<T>::Iterator::set(const T &value) {
    (*_itemsArray)[_index] = value;
}

template<typename T>
void DynamicArray<T>::Iterator::next() {
    _index += _direction;
}

template<typename T>
bool DynamicArray<T>::Iterator::hasNext() const {
    return (_index + _direction >= 0) && (_index + _direction < _itemsArray->_currentSize);
}
#pragma endregion
#pragma region ConstIteratorFunctions
template<typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::iterator() const {
    DynamicArray<T>::ConstIterator constIterator;
    constIterator._itemsArray = this;
    constIterator._index = 0;
    constIterator._direction = +1;
    return constIterator;
}

template<typename T>
typename DynamicArray<T>::ConstIterator DynamicArray<T>::reverseIterator() const {
    DynamicArray<T>::ConstIterator constIterator;
    constIterator._itemsArray = this;
    constIterator._index = _currentSize - 1;
    constIterator._direction = -1;
    return constIterator;
}



template<typename T>
const T &DynamicArray<T>::ConstIterator::get() const {
    return (*_itemsArray)[_index];
}

template<typename T>
void DynamicArray<T>::ConstIterator::next() {
    _index += _direction;
}

template<typename T>
bool DynamicArray<T>::ConstIterator::hasNext() const {
    return (_index + _direction >= 0) && (_index + _direction < _itemsArray->_currentSize);
}
#pragma endregion



