#include "../Headers/Queue.h"


template <typename T>

void Queue<T>::pop_back()
    {
        NodeQueue* currentPtr = head;
        NodeQueue* prevPtr = nullptr;
        if (currentPtr == nullptr)
        {
            cerr << "Error. Empty queue" << endl;
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

T Queue<T>::getFront()
   {
        NodeQueue* currentPtr = head;
        NodeQueue* prevPtr = nullptr;

        while (currentPtr->next != nullptr)
        {
            currentPtr = currentPtr->next;
        }
        return currentPtr->value;
    }


template <typename T>

void Queue<T>::push_front(T item)
    {
        if (head == nullptr)
        {
            head = new NodeQueue(item);
            sizeList++;
        }
        else
        {
            NodeQueue* newNode = new NodeQueue(item);
            newNode->next = head;
            head = newNode;
            sizeList++;
        }

    }




template <typename T>

int Queue<T>::getSize()
    {
        return sizeList;
    }