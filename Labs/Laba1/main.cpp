#include <iostream>

using namespace std;

template <typename anytype>

struct Node
{
    anytype value;
    Node* next;
};

template <typename AnytypeForFunction>

class LinkedList
{
private:

    Node* head{nullptr};

public:

    void InsertToStart(AnytypeForFunction item)
    {
        Node* newNode = new Node;
        if(head == nullptr)
        {
            newNode->value = item;
            
        }
    }

};

void main()
{



}

