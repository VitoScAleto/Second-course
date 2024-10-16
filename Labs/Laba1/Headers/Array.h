#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

template <typename T>

class MyArray
{
private:
    T* arr;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity);
    
public:
    MyArray();
    MyArray(size_t init_capacity);
    
    T& operator[](size_t index);
    
    void push_back(T element);
  
    void insert(size_t indexInput, T element);
    
    void delete_by_index(size_t indexInput);
    
    void replace_by_index(size_t indexInput, T element);
  
    size_t getSize();
    
    void print();
  
    void readingConfiguration(string nameFile);
    
    void writeToConfiguration(string nameFile);
   
};



    #include "../Source/Array.cpp"

#endif