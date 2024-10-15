#include "../Headers/ParseQuery.h"

int main(void)
{
    ParseQuery parseQuery;

    while(true)
    {
        string command;

        cout << ">>> ";

        getline(cin, command);


        parseQuery.parseCommand(command);

        command.clear();
    }


    return 0;
}