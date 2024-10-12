#include "../Headers/SQLQueryParse.h"

SQLQueryParse::SQLQueryParse(ReadingJSON& JSON, CSVInsert& csvInsert,CSVDelete& csvDelete,CSVSelect& csvSelect) : JSON(JSON), 
csvInsert(csvInsert), csvDelete(csvDelete),csvSelect(csvSelect){}


void SQLQueryParse::SQLInsert(stringstream& stream)
{
    string insertAction;

    stream >> insertAction; 

    if (insertAction == "INTO")
    {
            
        csvInsert.WriteToCSV(stream);

    }
    else
    {
        cerr<<"Ожидалось INTO, получено "<< insertAction <<endl;
        return;
    }
}

void SQLQueryParse::SQLDelete(stringstream& stream)
{
    string nameTable;
    stream >> nameTable;

    if(JSON.IsValidTable(nameTable) == true)
    {
        string action;

        stream >> action;

        if(action == "WHERE")
        {
           csvDelete.DeleteStart(stream);
        }
        else 
        {
            cerr<<"Ожидалась команда WHERE, получена "<< action <<endl;
            return;
        }

    }
    else 
    {
        cerr<<"Unknown table Fun"<< nameTable <<endl;
    }


}


void SQLQueryParse::Start()
{
    while(true)
    {
        string command;

        cout << "Enter SQL command: ";

        getline(cin, command);

        stringstream stream(command);

        string action;
        stream >> action; 

        if (action == "SELECT")
        {
            csvSelect.SelectStart(stream);
        }
        else if (action == "INSERT")
        {
            SQLInsert(stream);
            
        }
        else if (action == "DELETE")
        {
            string deleteAction;
            stream >> deleteAction; 

            if (deleteAction == "FROM")
            {
                SQLDelete(stream);
            }
        }
        else
        {
            cout << "Неизвестная команда" << endl;
            stream.clear();
        }
    }
}





