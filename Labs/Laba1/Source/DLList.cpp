#include "../Headers/DLList.h"

template <typename T>

DLinkedList<T>::DLinkedList() : sizeList(0), head{nullptr}, tail{nullptr} {};


template <typename T>

void DLinkedList<T>::writeToConfiguration(string nameFile)
    {
        ofstream outputFile(nameFile);

        if (!outputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }

        NodeDLL* currentPtr = head;

        while (currentPtr != nullptr)
        {
            outputFile << currentPtr->value << " ";
            currentPtr = currentPtr->next;

        }

        outputFile.close();
    }

template <typename T>

void DLinkedList<T>::readingConfiguration(string nameFile)
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

void DLinkedList<T>::search_by_value(T item)
    {
        if (isValidValue(item) == false)
        {
            cerr << "Error. Value not found" << endl;
            return;
        }

        NodeDLL* currentPtr = head;

        while (currentPtr != nullptr)
        {
            if (currentPtr->value == item)
            {
                cout << "Value: " << currentPtr->value << " index: " << index;
                cout << endl;
            }

            currentPtr = currentPtr->next;
            index++;
        }
    }
template <typename T>

void DLinkedList<T>::printList()
    {
        if (head == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }

        NodeDLL* currentPtr = head;

        while (currentPtr != nullptr)
        {
            cout << currentPtr->value << " ";
            currentPtr = currentPtr->next;
        }
        cout << endl;
    }
template <typename T>

void DLinkedList<T>::delete_by_value(T item)
    {
        if (isValidValue(item) == false)
        {
            cerr << "Error. Value not found" << endl;
            return;
        }

        NodeDLL* currentPtr = head;


        while (currentPtr != nullptr)
        {
            if (currentPtr->value == item)
            {

                if (currentPtr->prevToNode)
                {
                    currentPtr->prevToNode->next = currentPtr->next;
                }
                else
                {
                    head = currentPtr->next;
                }
                if (currentPtr->next)
                {
                    currentPtr->next->prevToNode = currentPtr->prevToNode;
                }
                NodeDLL* toDelete = currentPtr;
                currentPtr = currentPtr->next;
                delete toDelete;
                sizeList--;
            }
            else
            {
                currentPtr = currentPtr->next;
            }
        }


    }
template <typename T>

void DLinkedList<T>::pop_front()
    {

        if (tail == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }

        if (tail == head)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            NodeDLL* currentPtr = head;
            head = head->next;
            head->prevToNode = nullptr;
            delete currentPtr;
        }
        sizeList--;


    }
template <typename T>

void DLinkedList<T>::pop_back()
    {
        if (tail == nullptr)
        {
            cerr << "Error. Empty list" << endl;
            return;
        }

        if (tail == head)
        {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            NodeDLL* currentPtr = tail;
            tail = tail->prevToNode;
            tail->next = nullptr;
            delete currentPtr;
        }
        sizeList--;
    }
template <typename T>

void DLinkedList<T>::push_front(T item)
    {
        NodeDLL* currentPtr = new NodeDLL(item);

        if (head == nullptr)
        {
            head = currentPtr;
            tail = currentPtr;
        }
        else
        {
            currentPtr->next = head;
            head->prevToNode = currentPtr;
            head = currentPtr;
        }
        sizeList++;
    }
template <typename T>

void DLinkedList<T>::push_back(T item)
    {
        NodeDLL* currentPtr = new NodeDLL(item);
        if (head == nullptr)
        {
            head = currentPtr;
            tail = currentPtr;
        }
        else
        {
            tail->next = currentPtr;
            currentPtr->prevToNode = tail;
            tail = currentPtr;
        }
        sizeList++;
    }
template <typename T>

void DLinkedList<T>::getSize()
    {
        cout << "Size list: " << sizeList << endl;
    }
template <typename T>

bool DLinkedList<T>::isValidValue(T item)
    {

        NodeDLL* currentPtr = head;

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



int FunDLList()
{
    DLinkedList <string> DList;

    DList.readingConfiguration("test.txt");

    char c;

    cout << "\t\t--------------------------Doubly Linked List--------------------------" << endl;
    cout << endl;

    while (true)
    {
        cout << "0 - exit, 1 - print list, 2 - push_front, 3 - push_back, 4 - pop_back, 5 - pop_front, 6 - search by value, 7 - delete by value, 8 - get size\n\n<<< ";
        cin >> c;

        switch (c)
        {
        case '1':
            cout << endl;
            DList.printList();
            cout << endl;
            break;
        case '2':
        {
            cout << endl;
            string valueInList;
            
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

          
            DList.push_front(valueInList);
            cout << endl;
            break;
        }
        case '3':
        {
            cout << endl;
            string valueInList;
            
            
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

      
            DList.push_back(valueInList);
            cout << endl;
            break;
        }
        case '4':
            cout << endl;
            DList.pop_back();
            cout << endl;
            break;
        case '5':
            cout << endl;
            DList.pop_front();
            cout << endl;
            break;
        case '6':
        {
            cout << endl;
            string valueInList;
           
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

           
            DList.search_by_value(valueInList);
            cout << endl;
            break;
        }
        case '7':
        {
            cout << endl;
            string valueInList;
           
                cout << "Enter value\n\n<<< ";
                cin >> valueInList;

            
            DList.delete_by_value(valueInList);
            cout << endl;
            break;
        }
        case '8':
            cout << endl;
            DList.getSize();
            cout << endl;
            break;
        case '0':
            DList.writeToConfiguration("test.txt");
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }

}
