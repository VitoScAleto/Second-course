#include "../Headers/FList.h"

template <typename T>

void LinkedList<T>::readingConfiguration(string nameFile)
    {
        string valueConfiguration;

        ifstream inputFile(nameFile);

        if (!inputFile) {
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

void LinkedList<T>::writeToConfiguration(string nameFile)
{
        string valueConfiguration;

        ifstream inputFile(nameFile);

        if (!inputFile) {
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

void LinkedList<T>::printList()
    {
        Node* current = head;

        if (current == nullptr)
        {
            cout << "Empty list" << endl;

        }
        while (current != nullptr)
        {
            cout << current->value << " ";
            current = current->next;

        }
        cout << endl;
    }


template <typename T>

void LinkedList<T>::delete_by_value(T item)
    {
        if (!isValidValue(item))
        {
            cerr << "Error. Value not found" << endl;
            return;
        }

        Node* currentPtr = head;
        Node* prevPtr = nullptr;

        if (currentPtr == nullptr)
        {
            cerr << "Empty list" << endl;
            return;
        }

        while (currentPtr != nullptr && currentPtr->value == item)
        {
            Node* temp = currentPtr;
            currentPtr = currentPtr->next;
            delete temp;
            head = currentPtr;
            sizeList--;
        }


        prevPtr = head;
        while (currentPtr != nullptr)
        {
            if (currentPtr->value == item)
            {
                prevPtr->next = currentPtr->next;
                delete currentPtr;
                currentPtr = prevPtr->next;
                sizeList--;
            }
            else
            {
                prevPtr = currentPtr;
                currentPtr = currentPtr->next;
            }
        }
    }

template <typename T>

void LinkedList<T>::pop_front()
    {
        Node* currentPtr = head;

        if (currentPtr == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }
        Node* nextHead = currentPtr->next;

        head = nextHead;
        delete currentPtr;
        sizeList--;
    }

template <typename T>

void LinkedList<T>::pop_back()
    {
        Node* currentPtr = head;
        Node* prevPtr = nullptr;
        if (currentPtr == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }
        else if (currentPtr->next == nullptr)
        {
            delete currentPtr;
            head = nullptr;
            sizeList--;
            return;
        }
        while (currentPtr->next != nullptr)
        {
            prevPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
        free(currentPtr);
        prevPtr->next = nullptr;
        sizeList--;
    }

template <typename T>

void LinkedList<T>::search_by_value(T item)
    {

        if (isValidValue(item) == false)
        {
            cerr << "Error. Value not found" << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr)
        {
            if (current->value == item)
            {
                cout << "Found value: " << current->value << "Index: " << index << endl;
            }
            current = current->next;
            index++;
        }

    }

template <typename T>

void LinkedList<T>::push_front(T item)
    {
        if (head == nullptr)
        {
            head = new Node(item);
            sizeList++;
        }
        else
        {
            Node* newNode = new Node(item);
            newNode->next = head;
            head = newNode;
            sizeList++;
        }

    }

template <typename T>

void LinkedList<T>::push_back(T item)
    {
        if (head == nullptr)
        {
            head = new Node(item);
            sizeList++;
        }
        else
        {
            Node* current = head;
            while (current->next != nullptr)
            {
                current = current->next;

            }
            current->next = new Node(item);
            sizeList++;
        }
    }

template <typename T>

int LinkedList<T>::GetIndex()
    {
        return index;
    }

template <typename T>

int LinkedList<T>::getSize()
    {
        return sizeList;
    }

template <typename T>

bool LinkedList<T>::isValidValue(T item)
    {

        Node* currentPtr = head;

        while (currentPtr != nullptr)
        {
            if (currentPtr->value == item)
            {
                return true;
            }
            currentPtr = currentPtr->next;
        }
        return false;
    }

int FunFList()
{
    LinkedList <string> List;

    List.readingConfiguration("test.txt");

    char c;
    cout << "--------------------------------- Linked List ---------------------------------" << endl;
    cout << endl;

    while (true)
    {
        cout << "0 - exit, 1 - print list, 2 - push_front, 3 - push_back, 4 - pop_back, 5 - pop_front, 6 - search by value, 7 - delete by value, 8 - get size\n<<< ";
        cin >> c;

        switch (c)
        {
        case '1':
            cout << endl;
            List.printList();
            cout << endl;
            break;
        case '2':
        {
            cout << endl;
            string valueInList;
            
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            List.push_front(valueInList);
            cout << endl;
            break;
        }
        case '3':
        {
            cout << endl;
            string valueInList;
        
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            
            List.push_back(valueInList);
            cout << endl;
            break;
        }
        case '4':
            cout << endl;
            List.pop_back();
            cout << endl;
            break;
        case '5':
            cout << endl;
            List.pop_front();
            cout << endl;
            break;
        case '6':
        {
            cout << endl;
            string valueInList;
            
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            
            List.search_by_value(valueInList);
            cout << endl;
            break;
        }
        case '7':
        {
            cout << endl;
            string valueInList;
            
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            
            List.delete_by_value(valueInList);
            cout << endl;
            break;
        }
        case '8':
            cout << endl;
            cout << "Size list: " << List.getSize() << endl;
            cout << endl;
            break;
        case '0':
            List.writeToConfiguration("test.txt");
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }

    
}