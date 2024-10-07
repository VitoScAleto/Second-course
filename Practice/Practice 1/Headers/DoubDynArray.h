#ifndef DOUBLE_DYNAMIC_ARRAY_H
#define DOUBLE_DYNAMIC_ARRAY_H

#include "Headers.h"

template <typename T>
class DoubDynArray 
{
private:
    int sizeArr;
    int forPrint; // Текущий размер массива
    int tuples;    // Количество строк
    int columns;  // Количество столбцов
    T** array;   // Двумерный массив

public:
    DoubDynArray(int r, int c);
    ~DoubDynArray();
    
    T& operator()(int rowsF, int columnsF);
    void deleteValue(const T& value);
    T get(int r, int c);
    void push_back(T value);
    void printArray();
};



#include "../Source/DoubDynArray.cpp"

#endif
