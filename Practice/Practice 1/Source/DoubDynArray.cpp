#include "../Headers/DoubDynArray.h"

template <typename T>
DoubDynArray<T>::DoubDynArray(int r, int c) : tuples(r), columns(c), forPrint(0) 
{
    array = new T*[tuples];
    for (int i = 0; i < tuples; ++i) 
    {
        array[i] = new T[columns](); // Инициализация нулями
    }
}

template <typename T>
DoubDynArray<T>::~DoubDynArray() 
{
    for (int i = 0; i < tuples; ++i) 
    {
        delete[] array[i];
    }
    delete[] array;
}

template <typename T>
T& DoubDynArray<T>::operator()(int tuplesF, int columnsF) 
{
    if (tuplesF < 0 || tuplesF >= tuples || columnsF < 0 || columnsF >= columns) 
    {
        throw out_of_range("Index out of range");
    }
    return array[tuplesF][columnsF]; // Исправлено на tuplesF
}

template <typename T>
void DoubDynArray<T>::deleteValue(const T& value) 
{
    for (int i = 0; i < tuples; ++i) 
    {
        for (int j = 0; j < columns; ++j)
        {
            if (array[i][j] == value) 
            {
                array[i][j] = T(); 
            }
        }
    }
}

template <typename T>
T DoubDynArray<T>::get(int r, int c) 
{
    if (r < 0 || r >= tuples || c < 0 || c >= columns) 
    {
        throw out_of_range("Index out of range");
    }
    return array[r][c];
}

template <typename T>
void DoubDynArray<T>::push_back(T value) 
{
    if (forPrint >= tuples) 
    {
        throw overflow_error("Array is full");
    }
    for (int j = 0; j < columns; ++j) 
    {
        if (array[forPrint][j] == T()) 
        {
            array[forPrint][j] = value;
            sizeArr++;
            return;
        }
    }
    forPrint++; 
    if (forPrint < tuples) 
    { 
        array[forPrint][0] = value; 
        sizeArr++;
    } else 
    {
        throw overflow_error("Array is full");
    }
}

template <typename T>
void DoubDynArray<T>::printArray() 
{
    for (int i = 0; i < tuples; i++) 
    {
        for (int j = 0; j < columns; j++) 
        {
            cout << array[i][j] << " ";
        }
        cout << endl;
    }
}
