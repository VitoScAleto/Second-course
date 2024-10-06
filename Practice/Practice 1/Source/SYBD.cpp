#include "../Headers/SYBD.h"


void InsertInto(string nameTable, string insertTable)
{
    stringstream strStream(insertTable);

    string action;

    strStream >> action;

    if(action == "VALUES")
    {
        string remainingCommand;
        strStream >> remainingCommand;

        getline(strStream,remainingCommand);

        InsertToCSV(remainingCommand, nameTable);

    }
    else 
    {
        cerr<<"Unknown command"<<endl;
        return;
    }


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
            string remainingCommand;
            string nameTable;  
            ss >> nameTable;
            getline(ss,remainingCommand);
            InsertInto(nameTable, remainingCommand);
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
