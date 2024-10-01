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


    void readingConfiguration(string nameFile)
    {
        string valueConfiguration;

        ifstream inputFile(nameFile);

        if (!inputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }
        while (inputFile >> valueConfiguration)
        {
            push(valueConfiguration);
        }

        inputFile.close();
    }

    void writeToConfiguration(string nameFile)
    {
        ofstream outputFile(nameFile);

        if (!outputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }
        clearingTheQueue();

        queue.push_front(root);

        while (queue.getSize() != 0)
        {

            NodeTree<T>* currentPtr = queue.getFront(); // Получаем указатель на текущий узел
            queue.pop_back(); // Удаляем его из очереди

            outputFile << currentPtr->value << " "; // Печатаем значение текущего узла

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


        outputFile.close();
    }
    bool isComplete() 
    {
        if (root == nullptr) return true;

        Queue<NodeTree<T>*> queue;
        queue.push_front(root);
        bool end = false;

        while (queue.getSize() != 0) 
        {
            NodeTree<T>* currentPtr = queue.getFront();
            queue.pop_back();

            if (currentPtr->left != nullptr) 
            {
                if (end) return false; // Если уже встретили узел без потомков
                queue.push_front(currentPtr->left);
            }
            else 
            {
                end = true; // Нет левого потомка, значит, все последующие должны быть листьями
            }

            if (currentPtr->right) 
            {
                if (end) return false; // Если уже встретили узел без потомков
                queue.push_front(currentPtr->right);
            }
            else 
            {
                end = true; // Нет правого потомка
            }
        }

        return true;
    }
    int find(T item) 
    {
        clearingTheQueue();
        if (root == nullptr) 
        {
            return -1; // Дерево пустое
        }
        queue.push_front(root);
        int index = 0; 
        while (queue.getSize() != 0) 
        {
            NodeTree<T>* currentPtr = queue.getFront();
            queue.pop_back();

            if (currentPtr->value == item) 
            {
                return index; // Возвращаем индекс найденного элемента
            }
            index++;

            if (currentPtr->left != nullptr) 
            {
                queue.push_front(currentPtr->left);
            }
            if (currentPtr->right != nullptr) 
            {
                queue.push_front(currentPtr->right);
            }
        }
        return -1; // Элемент не найден
    }


};


int main()
{
    ComBinTree <string> tree;

    tree.readingConfiguration("test1.txt");

    char c;

    cout << "\t\t-------------------------- Complete Binary Tree -------------------------" << endl;
    cout << endl;

    while (true)
    {
        cout << "0 - exit, 1 - print tree, 2 - push, 3 - complete tree, 4 - search value\n\n<<< ";
        cin >> c;

        switch (c)
        {
        case '1':
            cout << endl;
            tree.print();
            cout << endl;
            break;
        case '2':
        {
            cout << endl;
            string valueInList;

            cout << "Enter value\n\n<<< ";
            cin >> valueInList;


            tree.push(valueInList);
            cout << endl;
            break;
        }
        case '3':
            cout << endl;
            if (tree.isComplete() == true)
            {
                cout << "Tree is  complete" << endl;
            }
            else
            {
                cout << "Tree is not complete" << endl;
            }
            break;
        case '4':
        {
            cout << endl;
            string valueInList;
            cout << "Enter value\n\n<<< ";
            cin >> valueInList;

            if (tree.find(valueInList) == -1)
            {
                cout << "Value not found" << endl;
            }
            else
            {
                cout << "Index: " << tree.find(valueInList) << endl;
            }
        }
            break;
        case '0':
            tree.writeToConfiguration("test1.txt");
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;

        }
    }
}
