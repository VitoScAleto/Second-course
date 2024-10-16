#include "../Headers/Array.h"
template <typename T>

MyArray<T>::MyArray(){}


template <typename T>

MyArray<T>::MyArray(size_t init_capacity) : size(0), capacity(init_capacity)
{
        if (init_capacity == 0)
        {
            cerr << "length error" << endl;
            return;
        }
        arr = new T[init_capacity]();
    }

template <typename T>

void MyArray<T>::resize(size_t new_capacity)
{
        if (new_capacity < size)
        {
            cerr << "New capacity is smaller than current size" << endl;
            return;
        }
        T* newArr = new T[new_capacity];
        for (size_t i = 0; i < size; i++)
        {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        capacity = new_capacity;
}

template <typename T>

T& MyArray<T>::operator[](size_t index)
{
        if (index >= size)
        {
            cerr << "Index out of bounds" << endl;

        }
        return arr[index];
}

template <typename T>

void MyArray<T>::push_back(T element)
{
        if (size == capacity)
        {
            resize(capacity * 2);
        }
        arr[size] = element;
        size++;
}
template <typename T>

void MyArray<T>::insert(size_t indexInput, T element)
    {
        if (indexInput > size)
        {
            cerr << "there is no such position" << endl;
            return;
        }
        if (size == capacity)
        {
            resize(capacity * 2);
        }
        for (size_t i = size; i > indexInput; --i)
        {
            arr[i] = arr[i - 1];
        }
        arr[indexInput] = element;
        size++;
    }
template <typename T>

void MyArray<T>::delete_by_index(size_t indexInput)
    {
        if (indexInput >= size)
        {
            cerr << "Unvalid index " << endl;
            return;
        }
        for (size_t i = indexInput; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        size--;
    }
template <typename T>

void MyArray<T>::replace_by_index(size_t indexInput, T element)
    {
        if (indexInput >= size)
        {
            cerr << "Unvalid index " << endl;
            return;
        }
        arr[indexInput] = element;
    }
template <typename T>

size_t MyArray<T>::getSize() 
    {
        return size;
    }
template <typename T>

void MyArray<T>::print()
    {
        if (size == 0) cerr << "Array empty" << endl;
        for (size_t i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
template <typename T>

void MyArray<T>::readingConfiguration(string nameFile)
    {
        string valueConfiguration;
        ifstream inputFile(nameFile);
        if (!inputFile)
        {
            ofstream outputFile(nameFile);
            if(!outputFile)
            {
                cerr<<"Не удалось создать файл "<< nameFile<<endl;
                return;
            }
            outputFile.close();
        }
        
        while (inputFile >> valueConfiguration)
        {
            push_back(valueConfiguration);
        }
        inputFile.close();
    }

template <typename T>

void MyArray<T>::writeToConfiguration(string nameFile)
    {
        ofstream outputFile(nameFile);
        if (!outputFile)
        {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }
        for (size_t i = 0; i < size; i++)
        {
            outputFile << arr[i] << " ";
        }
        outputFile.close();
    }

