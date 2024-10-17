#include "../Headers/queue.h"


template <typename T>
void Queue<T>::push_back(T item)
{
    NodeQueue* newNode = new NodeQueue(item);
    if (tail == nullptr) {
        head = tail = newNode; // Если очередь пуста, новый узел становится и головой, и хвостом
    } else {
        tail->next = newNode; // Текущий хвост указывает на новый узел
        tail = newNode; // Новый узел становится хвостом
    }
    sizeList++;
}

template <typename T>
void Queue<T>::pop_front()
{
    if (head == nullptr) {
        cerr << "Ошибка. Очередь пуста." << endl;
    }
    NodeQueue* temp = head; // Сохраняем указатель на голову
    T value = head->value; // Сохраняем значение для возврата
    head = head->next; // Перемещаем голову на следующий узел
    delete temp; // Освобождаем память
    sizeList--;
    if (head == nullptr) {
        tail = nullptr; // Если очередь пуста, сбрасываем хвост
    }
    
}

template <typename T>
T Queue<T>::getFront()
{
    if (head == nullptr) {
        cerr << "Ошибка. Очередь пуста." << endl;
        throw std::runtime_error("Очередь пуста");
    }
    return head->value; // Возвращаем значение переднего узла
}

template <typename T>
int Queue<T>::getSize()
{
    return sizeList; // Возвращаем размер очереди
}