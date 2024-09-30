#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

template <typename T>
class MyArray {
private:
    T* arr;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity)
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

public:
    bool isIntegerInput(int number)
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return false;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    MyArray(size_t init_capacity) : size(0), capacity(init_capacity)
    {
        if (init_capacity == 0)
        {
            cerr<<"length error"<<endl;
            return;
        }
        arr = new T[init_capacity]();
    }

    T& operator[](size_t index)
    {
        if (index >= size)
        {
            cerr<<"Index out of bounds" << endl;
           
        }
        return arr[index];
    }

    void push_back(T element)
    {
        if (size == capacity)
        {
            resize(capacity * 2);
        }
        arr[size] = element;
        size++;
    }

    void insert(size_t indexInput, T element)
    {
        if (indexInput > size)
        {
            cerr<<"there is no such position"<<endl;
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

    void delete_by_index(size_t indexInput)
    {
        if (indexInput >= size)
        {
            cerr<<"Unvalid index "<<endl;
            return;
        }
        for (size_t i = indexInput; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    void replace_by_index(size_t indexInput, T element)
    {
        if (indexInput >= size)
        {
            cerr << "Unvalid index " << endl;
            return;
        }
        arr[indexInput] = element;
    }

    size_t getSize() const
    {
        return size;
    }

    void print()
    {
        for (size_t i = 0; i < size; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    void readingConfiguration(string nameFile)
    {
        int valueConfiguration = 0;
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

    void writeToConfiguration(string nameFile)
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


};

int main()
{
    MyArray<int> intArr{ 5 };

    intArr.readingConfiguration("test1.txt");

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
            int valueInArr;
            do
            {
                cout << "Enter value\n\n<<< ";
                cin >> valueInArr;
            } while (intArr.isIntegerInput(valueInArr) == false);
            intArr.push_back(valueInArr);
            cout << endl;
            break;
        }
        case '3':
        {
            cout << endl;
            int valueInArr, index;
            cout << "Enter index\n<<< ";
     
            cin >> index;

            do
            {
                cout << "Enter value\n<<< ";
                cin >> valueInArr;
            } while (intArr.isIntegerInput(valueInArr) == false);
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
            int index, valueInArr;
            cout << "Enter index to replace\n<<< ";
            cin >> index;
            do
            {
                cout << "Enter new value\n<<< ";
                cin >> valueInArr;
            } while (intArr.isIntegerInput(valueInArr) == false);
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
            intArr.writeToConfiguration("test1.txt");
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }

    return 0;
}
