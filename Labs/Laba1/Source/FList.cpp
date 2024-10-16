#include "../Headers/FList.h"
template <typename T>

LinkedList<T>::~LinkedList(){};

template <typename T>

void LinkedList<T>::readingConfiguration(string nameFile)
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

void LinkedList<T>::writeToConfiguration(string nameFile)
{
        ofstream outputFile(nameFile);

        if (!outputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }

        Node* current = head;
        while (current != nullptr)
        {
            outputFile << current->value<<" ";
            current = current->next;
        }

        outputFile.close();
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
