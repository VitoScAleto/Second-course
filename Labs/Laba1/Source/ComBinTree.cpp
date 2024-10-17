#include "../Headers/ComBinTree.h"




template <typename T>

void QueueForTree<T>::pop_back()
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

T QueueForTree<T>::getFront()
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

void QueueForTree<T>::push_front(T item)
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

int QueueForTree<T>::getSize()
    {
        return sizeList;
    }




template <typename T>

bool ComBinTree<T>::find(T item) 
    {
        clearingTheQueue();
        if (root == nullptr) 
        {
            return false; // Дерево пустое
        }
        queue.push_front(root);
        int index = 0; 
        while (queue.getSize() != 0) 
        {
            NodeTree* currentPtr = queue.getFront();
            queue.pop_back();

            if (currentPtr->value == item) 
            {
                return true; // Возвращаем индекс найденного элемента
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
        return false; // Элемент не найден
    }

template <typename T>

bool ComBinTree<T>::isComplete() 
    {
        if (root == nullptr) return true;

        QueueForTree<NodeTree*> queue;
        queue.push_front(root);
        bool end = false;

        while (queue.getSize() != 0) 
        {
            NodeTree* currentPtr = queue.getFront();
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

template <typename T>

void ComBinTree<T>::writeToConfiguration(string nameFile)
    {
        ofstream outputFile(nameFile);

        if (!outputFile) {
            cerr << "Не удалось открыть файл!" << endl;
            return;
        }
        clearingTheQueue(); 
        if(root == nullptr)
        {
            return;
        }
        queue.push_front(root);

        while (queue.getSize() != 0)
        {

            NodeTree* currentPtr = queue.getFront(); // Получаем указатель на текущий узел
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

template <typename T>

void ComBinTree<T>::readingConfiguration(string nameFile)
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
            push(valueConfiguration);
        }

        inputFile.close();
    }

template <typename T>

void ComBinTree<T>::print_CBT(NodeTree* current, int level) 
{
        if (current) {
            print_CBT(current->right, level + 1);
            for (int i = 0; i < level; i++) {
                cout << "   ";
            }

            cout << current->value << endl; 
            print_CBT(current->left, level + 1);
        }
    }


template <typename T>

 void ComBinTree<T>:: display() 
 {
        if (root == nullptr) {
            cout << "Tree is empty.\n";
            return;
        }
        print_CBT (root, 0);
    }
template <typename T>

void ComBinTree<T>::push(T item)
    {
        NodeTree* newNodeTree = new NodeTree(item);

        if (root == nullptr)
        {
            root = newNodeTree;
            return;
        }

        queue.push_front(root);

        while (queue.getSize() != 0)
        {
            NodeTree* currentPtr = queue.getFront();

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

template <typename T>

void ComBinTree<T>::clearingTheQueue()
    {
        while (queue.getSize() != 0)
        {
            queue.pop_back();
        }
    }




