#include "../Headers/Array.h"
#include "../Headers/DLList.h"
#include "../Headers/ComBinTree.h"
#include "../Headers/queue.h"
#include "../Headers/stack.h"
#include "../Headers/FList.h"

int main()
{
   
     char c;
    cout << "---------------------------------  ---------------------------------" << endl;
    cout << endl;

    while (true)
    {
        cout << "0 - exit, 1 - Complete Binary Tree, 2 - Stack, 3 - Queue, 4 - Forward List, 5 - DLList, 6 - Array\n<<< ";
        cin >> c;

        switch (c)
        {
        case '1':
            FunComBinTree();
            break;
        case '2':
        {
          FunStack();
            break;
        }
        case '3':
        {
          FunQueue();
        
            break;
        }
        case '4':
           FunFList();
            break;
        case '5':
            FunDLList();
            break;
        case '6':
        {
            FunArray();
            break;
        }
        
        case '0':
            
            return 0;
        default:
            cout << "Unknown command. Re-enter\n" << endl;
            break;
        }
    }

}

