#include "../Headers/SYBD.h"


void InsertInto(string nameTable, string values)
{
    if(nameTable == "Таблица1" || nameTable == "Таблица2")
    {
        stringstream strStream(values);

        string action;

        strStream >> action;

        if(action == "VALUES")
        {
            
            WorkWithCSV(TruncateInputCommand(strStream), nameTable);
        }
        else 
        {
            cerr<<"Unknown command"<<endl;
            return;
        }

    }
    else 
    {
        cerr<<"Такой таблицы нет"<<endl;
    }
}


string TruncateInputCommand(stringstream& ss)
{
    string remainingCommand;

    getline(ss,remainingCommand);

    remainingCommand.erase(0, remainingCommand.find_first_not_of(' '));

    return remainingCommand;
}


void SYBD()
{
   while(true)
    {
    string command;
    cout << "Enter SQL command: ";
    getline(cin, command);

    stringstream ss(command);

    string action;
    ss >> action; 

    if (action == "SELECT")
    {
        cout << "Обработка команды SELECT..." << endl;
        
    }
    else if (action == "INSERT")
    {
        string insertAction;
        ss >> insertAction; // Получаем вторую часть команды (INTO)
        if (insertAction == "INTO")
        {
            string nameTable;  
            ss >> nameTable;
           
            InsertInto(nameTable, TruncateInputCommand(ss));
        }
        else
        {
            cerr<<"Unknown command"<<endl;
        }
        
    }
    else if (action == "DELETE")
    {
        string deleteAction;
        ss >> deleteAction; // Получаем вторую часть команды (FROM)
        if (deleteAction == "from")
        {
            cout << "Обработка команды DELETE FROM..." << endl;
            // Здесь вы можете добавить логику для обработки DELETE FROM
        }
    }
    else
    {
        cout << "Неизвестная команда." << endl;
        ss.clear();
    }
}




}
