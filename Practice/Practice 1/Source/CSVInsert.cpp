#include "../Headers/CSVInsert.h"


CSVInsert::CSVInsert(ReadingJSON& JSON) : JSON(JSON) 
{
    numberElementInCSV = 0;
}

string TruncateInputCommand(stringstream& stream)
{
    string remainingCommand;

    getline(stream,remainingCommand);

    remainingCommand.erase(0, remainingCommand.find_first_not_of(' '));

    return remainingCommand;
}

void CSVInsert::GetNameTableFromQuery(string nameTable)
{
    nameTableFromQuery = nameTable;
}

template <typename T>

void CSVInsert::extractDataFromQuery(LinkedList<T>& listQuery, string input) 
{

    size_t start = 0, end = 0;

    // Найти первую открывающую скобку
    if (input.front() != '(' || input.back() != ')') 
    {

        throw invalid_argument("Function(extractDataFromQuery()) -> Input must start with '(' and end with ')'");
    }

    // Пропустить первую и последнюю скобки
    start = 1;
    end = input.find("'", start);

    while (end != string::npos) 
    {
        size_t nextEnd = input.find("'", end + 1);
        if (nextEnd == string::npos) break; // Если нет закрывающей кавычки

        // Извлечь значение между кавычками
        listQuery.push_back(input.substr(end + 1, nextEnd - end - 1));
        // Обновить start для поиска следующего значения
        end = input.find(",", nextEnd + 1);
        if (end == string::npos) break; // Если нет запятой, выходим из цикла
        start = end + 1; // Пропускаем запятую
        end = input.find("'", start);
    }

}


void CSVInsert:: WriteToCSV(stringstream& stream)
{
    string nameTable;

    stream >> nameTable;

    if(JSON.IsValidTable(nameTable) == true) GetNameTableFromQuery(nameTable);
    else
    {
        cerr<<"Unknown table"<<endl;
        return;
    }

    string action;
    stream >> action;

    if(action == "VALUES");
    else
    {
        cerr<<"Ожидалась команда VALUES, получена "<< action <<endl;
        return;
    }
    
    InsertValuesFromQuery(TruncateInputCommand(stream));
}



void CSVInsert::InsertValuesFromQuery(string data)
{
    LinkedList <string> ListQuery;

    extractDataFromQuery(ListQuery, data);

    if(JSON.IsValidTable(nameTableFromQuery))
    {
        LinkedList <string> ColumnsFromJSON; 
        JSON.GetColumnsFromSchema(ColumnsFromJSON,nameTableFromQuery);

        string pathToCSVInsert = "../Source/" + JSON.GetNameMainDir()+"/"+nameTableFromQuery + "/1.csv";

        ofstream outFile(pathToCSVInsert, ios::app);
        
        if(!outFile.is_open())
        {
        throw ios_base::failure("Function(WriteToCSVInsert()) -> Failed to open file: " + pathToCSVInsert);
        }

        while(ListQuery.getSize() != 0)
        {    
            outFile.close();
            ofstream outFile(pathToCSVInsert, ios::app);

            int quantityElementInCSVInsertFileT = CountElementInCSV(nameTableFromQuery);

            quantityElementInCSVInsertFileT %= ColumnsFromJSON.getSize();

            if(quantityElementInCSVInsertFileT == 0)
            {
                outFile<<"\n"<<WorkWithFile_pk_sequence(nameTableFromQuery)<<",";
                quantityElementInCSVInsertFileT++;
            }
            for(int i = 0; i < ColumnsFromJSON.getSize() - quantityElementInCSVInsertFileT && ListQuery.getSize() != 0; i++)
            {
                outFile << ListQuery.getHead()<<",";
                ListQuery.pop_front();
                
            }

        }

        outFile.close();
        ListQuery.~LinkedList();

        return;
    }
    throw invalid_argument("Function(WriteToCSVInsert()) -> Invalid table name: " + nameTableFromQuery);
}

int CSVInsert::CountElementInCSV(string nameTable)
{
    numberElementInCSV = 0;

    if(JSON.IsValidTable(nameTable) == true)
    {
        string pathToCSVInsert = "../Source/" + JSON.GetNameMainDir()+"/"+nameTable + "/1.csv";

        ifstream outFile(pathToCSVInsert);
        
        if(!outFile.is_open())
        {
        
        throw ios_base::failure("Function(CountElementInCSV()) -> Failed to open file: " + pathToCSVInsert);
        }

        string line;

        while (getline(outFile, line)) 
        {
           stringstream ss(line);
           string item;

            while (getline(ss, item, ',')) 
            {
                numberElementInCSV++;
            }

        }
        outFile.close();
        return numberElementInCSV;
    }

    throw invalid_argument("Function(CountElementInCSVInsert()) -> Invalid table name: " + nameTable);
}


int CSVInsert::WorkWithFile_pk_sequence(string nameTable)
{
    string pkFilePath = "../Source/" + JSON.GetNameMainDir()+"/" + nameTable + "/" + nameTable + "_pk_sequence.txt";

    int currentPk = 0;

    ifstream pkFile(pkFilePath);

    if (pkFile.is_open()) 
    {
        pkFile >> currentPk; 
        pkFile.close();
    } 
    else 
    {
        ofstream createFile(pkFilePath);
        if (createFile.is_open()) 
        {
            createFile << currentPk; // Записываем начальное значение
            createFile.close();
        }
        else 
        {
            throw ios_base::failure("Function(WorkWithFile_pk_sequence()) -> Failed to сreate file: " + pkFilePath);
        }
    }

    currentPk++;

    ofstream outPkFile(pkFilePath);
    if (outPkFile.is_open()) 
    {
        outPkFile << currentPk; 
        outPkFile.close();
    } 
    else 
    {
        cerr << "File " << pkFilePath << " is not open for writing." << endl;
    }
    return currentPk;
}