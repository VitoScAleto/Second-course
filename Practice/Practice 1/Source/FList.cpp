#include "../Headers/FList.h"

template <typename T>
T& LinkedList<T>::operator[](int index) 
{
    if (index < 0 || index >= sizeList) 
    {
        throw std::out_of_range("Index out of range");
    }

    Node* temp = head;
    for (int i = 0; i < index; ++i) 
    {
        temp = temp->next;
    }
    return temp->value;
}

template <typename T>
LinkedList<T>::~LinkedList() 
{ 
    while (head != nullptr) 
    {
        pop_front();
    }
}

template <typename T>
T LinkedList<T>::getHead() 
{
    if (head == nullptr) 
    {
        throw std::runtime_error("List is empty");
    }
    return head->value;
}

template <typename T>
T LinkedList<T>::Get_by_index(int indexValue) 
{
    if (indexValue < 0 || indexValue >= sizeList) 
    {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head;
    for (int i = 0; i < indexValue; ++i) 
    {
        current = current->next;
    }
    return current->value;
}

template <typename T>
void LinkedList<T>::printList() 
{
    Node* current = head;
    if (current == nullptr)
     {
        cout << "Empty list" << endl;
        return;
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
    Node* currentPtr = head;
    Node* prevPtr = nullptr;

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
        } else 
        {
            prevPtr = currentPtr;
            currentPtr = currentPtr->next;
        }
    }
}

template <typename T>
void LinkedList<T>::pop_front() 
{
    if (head == nullptr) 
    {
        cerr << "Error. Empty list" << endl;
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
    sizeList--;
}

template <typename T>
void LinkedList<T>::pop_back() 
{
    if (head == nullptr) 
    {
        cerr << "Error. Empty list" << endl;
        return;
    }

    if (head->next == nullptr) 
    {
        delete head;
        head = nullptr;
        sizeList--;
        return;
    }

    Node* currentPtr = head;
    while (currentPtr->next->next != nullptr) 
    {
        currentPtr = currentPtr->next;
    }
    delete currentPtr->next;
    currentPtr->next = nullptr;
    sizeList--;
}

template <typename T>
int LinkedList<T>::search_by_value(T item) 
{
    Node* current = head;
    int index = 0;
    while (current != nullptr) 
    {
        if (current->value == item) 
        {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1; // Возвращаем -1, если значение не найдено
}

template <typename T>
void LinkedList<T>::push_front(T item) 
{
    Node* newNode = new Node(item);
    newNode->next = head;
    head = newNode;
    sizeList++;
}

template <typename T>
void LinkedList<T>::push_back(T item) 
{
    Node* newNode = new Node(item);
    if (head == nullptr) 
    {
        head = newNode;
    } 
    else 
    {
        Node* current = head;
        while (current->next != nullptr) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
    sizeList++;
}

template <typename T>
int LinkedList<T>::getSize() 
{
    return sizeList;
}