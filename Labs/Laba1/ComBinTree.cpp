#include <iostream>
#include <fstream>

using namespace std;

template <typename T>

struct NodeQueue
{
    T value;
    NodeQueue* next;
    NodeQueue(T val) : value(val), next(nullptr) {}; // Конструктор для инициализации значения
};

template <typename T>

struct Queue
{
private:

    NodeQueue<T>* head{ nullptr };
    int sizeList = 0;

public:
    int getSize()
    {
        return sizeList;
    }

    void push_front(T item)
    {
        if (head == nullptr)
        {
            head = new NodeQueue<T>(item);
            sizeList++;
        }
        else
        {
            NodeQueue<T>* newNode = new NodeQueue<T>(item);
            newNode->next = head;
            head = newNode;
            sizeList++;
        }

    }

    T getFront()
    {
        NodeQueue<T>* currentPtr = head;
        NodeQueue<T>* prevPtr = nullptr;

        while (currentPtr->next != nullptr)
        {
            currentPtr = currentPtr->next;
        }
        return currentPtr->value;
    }

    void pop_back()
    {
        NodeQueue<T>* currentPtr = head;
        NodeQueue<T>* prevPtr = nullptr;
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

};

template <typename T>

struct NodeTree
{
    T value;
    NodeTree* left;
    NodeTree* right;
    NodeTree(T val) : value(val), left(nullptr), right(nullptr) {}; // Конструктор для инициализации значения
};

template <typename T>

class ComBinTree
{
private:

    NodeTree<T>* root{ nullptr };
    Queue <NodeTree<T>*> queue;// хранит указатели на узлы дерева

    void clearingTheQueue()
    {
        while (queue.getSize() != 0)
        {
            queue.pop_back();
        }
    }

public:

    void push(T item)
    {
        NodeTree<T>* newNodeTree = new NodeTree<T>(item);

        if (root == nullptr)
        {
            root = newNodeTree;
            return;
        }

        queue.push_front(root);

        while (queue.getSize() != 0)
        {
            NodeTree<T>* currentPtr = queue.getFront();

            queue.pop_back();

            if (currentPtr->left == nullptr)
            {
                currentPtr->left = newNodeTree;
                return;
            }
            else
            {
                queue.push_front(currentPtr->left);
            }


            if (currentPtr->right == nullptr)
            {
                currentPtr->right = newNodeTree;
                return;
            }
            else
            {
                queue.push_front(currentPtr->right);
            }

        }
    }

    void print() 
    {
        clearingTheQueue();

        if (root == nullptr) 
        {
            cout << "Tree empty" << endl;
            return;
        }

        queue.push_front(root); // Начинаем с корня

        while (queue.getSize() != 0) 
        {

            NodeTree<T>* currentPtr = queue.getFront(); // Получаем указатель на текущий узел
            queue.pop_back(); // Удаляем его из очереди
      
            cout << currentPtr->value << " "; // Печатаем значение текущего узла
            
           
            // Если у текущего узла есть левый потомок, добавляем его в очередь
            if (currentPtr->left != nullptr) 
            {
                queue.push_front(currentPtr->left);
            }

            // Если у текущего узла есть правый потомок, добавляем его в очередь
            if (currentPtr->right != nullptr) 
            {
                queue.push_front(currentPtr->right);
            }
        }
        
    }

};


int main()
{
    ComBinTree <int> tree;
    tree.push(5);
    tree.push(6);
    tree.push(7);
    tree.push(8);
    tree.push(9);
    tree.push(10);

    tree.print();

    return 0;
}