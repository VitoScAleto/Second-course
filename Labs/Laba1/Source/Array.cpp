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
            cerr << "Не удалось открыть файл!" << endl;
            return;
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


    int FunArray()
{

    MyArray<string> intArr{ 5 };

    intArr.readingConfiguration("test.txt");
    char c;
    cout << "--------------------------------- Array ---------------------------------" << endl;
    cout << endl;
    while (true)
    {
        cout << "0 - exit, 1 - print array, 2 - push back, 3 - push by index, 4 - get value by index, 5 - delete value by index, 6 - replace by index, 7 - size array\n<<< ";
        cin >> c;
        switch (c)
        {
        case '1':
            cout << endl;
            intArr.print();
            cout << endl;
            break;
        case '2':
        {
            cout << endl;
            string valueInArr;

            cout << "Enter value\n\n<<< ";
            cin >> valueInArr;

            intArr.push_back(valueInArr);
            cout << endl;
            break;
        }
        case '3':
        {
            cout << endl;
            string valueInArr;
            int index;
            cout << "Enter index\n<<< ";

            cin >> index;


            cout << "Enter value\n<<< ";
            cin >> valueInArr;

            intArr.insert(index, valueInArr);
            cout << endl;
            break;
        }
        case '4':
        {
            cout << endl;
            int index;
            cout << "Enter index\n<<< ";
            cin >> index;
            try
            {
                cout << "Value at index " << index << ": " << intArr[index] << endl;
            }
            catch (const out_of_range& e)
            {
                cerr << e.what() << endl;
            }
            cout << endl;
            break;
        }
        case '5':
        {
            cout << endl;
            int index;
            cout << "Enter index to delete\n<<< ";
            cin >> index;
            try
            {
                intArr.delete_by_index(index);
                cout << "Value at index " << index << " deleted." << endl;
            }
            catch (const invalid_argument& e)
            {
                cerr << e.what() << endl;
            }
            cout << endl;
            break;
        }
        case '6':
        {
            cout << endl;
            int index;
            string valueInArr;
            cout << "Enter index to replace\n<<< ";
            cin >> index;

            cout << "Enter new value\n<<< ";
            cin >> valueInArr;

            try
            {
                intArr.replace_by_index(index, valueInArr);
                cout << "Value at index " << index << " replaced." << endl;
            }
            catch (const invalid_argument& e) {
                cerr << e.what() << endl;
            }
            cout << endl;
            break;
        }
        case '7':
            cout << endl;
            cout << "Size arr: " << intArr.getSize() << endl;
            cout << endl;
            break;
        case '0':
            intArr.writeToConfiguration("test.txt");
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }
    return 0;
}