#include "../Headers/SQLQueryParse.h"

SQLQueryParse::SQLQueryParse(ReadingJSON& JSON, CSVInsert& csvInsert,CSVDelete& csvDelete,CSVSelect& csvSelect, CSVWhere& csvWhere) : JSON(JSON), 
csvInsert(csvInsert), csvDelete(csvDelete),csvSelect(csvSelect), csvWhere(csvWhere){}


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


void SQLQueryParse::SelectAndWhereStart(stringstream& stream)
{
    string nameTable1, nameTable2, nameColumn1, nameColumn2;
   
    if(csvSelect.ParseCommandForSelect(nameTable1, nameTable2, nameColumn1, nameColumn2,stream) == false) 
    {
        
        cerr<<"Ошибка ввода команды SELECT FROM"<<endl;
        return;
    }
    else if(SearcWhereInQuery(stream,"WHERE") == true)
    {
        string action;
        stream >> action;
        csvWhere.StartWhere(nameTable1, nameTable2, nameColumn1, nameColumn2,stream);
    } 
    else if(IsValidQueryForSelect(stream) == true)
    {
        csvSelect.SelectFromCSV(nameTable1, nameTable2, nameColumn1, nameColumn2);
    }

}
bool SQLQueryParse::SearcWhereInQuery(stringstream& stream, const string searchString)
{
    string content = stream.str();
    return content.find(searchString) != string::npos;

}

bool SQLQueryParse::IsValidQueryForSelect(stringstream& stream)
{
    string action;
    stream >> action;
    if(action == " " || action == "") return true;
    else
    {
        string ss;
        getline(stream,ss);
        cerr<<"Ожидалось, что для SELECT FROM дальше ничего не будет, но полученно "<<action<<" "<< ss <<endl;
        return false;
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
            SelectAndWhereStart(stream);
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





