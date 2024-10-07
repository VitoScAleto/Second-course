#include "../Headers/WorkWithFiles.h"

template <typename T>

Queue<T> extractDataFromQuery(string input) 
{
    Queue <string> queue;
    size_t start = 0, end = 0;

    // Найти первую открывающую скобку
    if (input.front() != '(' || input.back() != ')') 
    {
        throw invalid_argument("Input must start with '(' and end with ')'");
    }

    // Пропустить первую и последнюю скобки
    start = 1;
    end = input.find("'", start);

    while (end != string::npos) 
    {
        size_t nextEnd = input.find("'", end + 1);
        if (nextEnd == string::npos) break; // Если нет закрывающей кавычки

        // Извлечь значение между кавычками
        queue.push_back(input.substr(end + 1, nextEnd - end - 1));
        // Обновить start для поиска следующего значения
        end = input.find(",", nextEnd + 1);
        if (end == string::npos) break; // Если нет запятой, выходим из цикла
        start = end + 1; // Пропускаем запятую
        end = input.find("'", start);
    }

    
    return queue;
}


int ConfigurationForArrayFromJSON()
{
    string pathFileSchemaJson = "/home/pushk/VSCODE/Second-course/Practice/Practice 1/JSON/schema.json";

    json j;

    ifstream file(pathFileSchemaJson);
    if (file.is_open()) 
    {
        // Парсим содержимое файла
        j = json::parse(file);

    
        file.close();
    } 
    else 
    {
        cerr << "Не удалось открыть файл: " << pathFileSchemaJson << endl;
        return 0; // Возвращаем код ошибки
    }

    int tuples_limit = j["tuples_limit"];
    
    return tuples_limit;
}

template <typename T>

DoubDynArray<T>ReadingCSVFileIntoArray(string data, string nameTable)
{
    if(nameTable == "Таблица1")
    {
        string pathToCSV = "../Source/Схема 1/" + nameTable + "/1.csv";

        DoubDynArray <string> FromCSVArray(ConfigurationForArrayFromJSON(),5);

        ifstream outFile(pathToCSV);
        if(!outFile.is_open())
        {
        cerr << "Error: Could not open the file " << pathToCSV << endl;
        throw ios_base::failure("Failed to open file: " + pathToCSV);
        }

        string line;
        while (std::getline(outFile, line)) 
        {
            std::stringstream ss(line);
            std::string item;

            while (std::getline(ss, item, ',')) 
            {
                FromCSVArray.push_back(item);
            }

        }
        outFile.close();
        return FromCSVArray;

    }

    if(nameTable == "Таблица2")
    {
        string pathToCSV = "../Source/Схема 1/" + nameTable + "/1.csv";

        DoubDynArray <string> FromCSVArray(ConfigurationForArrayFromJSON(),3);

        ifstream outFile(pathToCSV);
        if(!outFile.is_open())
        {
        cerr << "Error: Could not open the file " << pathToCSV << endl;
        throw ios_base::failure("Failed to open file: " + pathToCSV);
        }

        string line;
        while (std::getline(outFile, line)) 
        {
            std::stringstream ss(line);
            std::string item;

            while (std::getline(ss, item, ',')) 
            {
                FromCSVArray.push_back(item);
            }

        }
        outFile.close();
        return FromCSVArray;
    }
    throw invalid_argument("Invalid table name: " + nameTable);
}


void WriteToCSVFileIntoArray(string data, string nameTable)
{
    Queue <string> queueForArray = extractDataFromQuery<string>(data);

    if(nameTable == "Таблица1")
    {
        string pathToCSV = "../Source/Схема 1/" + nameTable + "/1.csv";

        DoubDynArray <string> ArrayToInsert = ReadingCSVFileIntoArray<string>(data, nameTable);

        ofstream outFile(pathToCSV);
        
        if(!outFile.is_open())
        {
        cerr << "Error: Could not open the file " << pathToCSV << endl;
        throw ios_base::failure("Failed to open file: " + pathToCSV);
        }




       

    }

    if(nameTable == "Таблица2")
    {
        string pathToCSV = "../Source/Схема 1/" + nameTable + "/1.csv";

        DoubDynArray <string> ArrayToInsert = ReadingCSVFileIntoArray<string>(data, nameTable);

        ofstream outFile(pathToCSV);

        if(!outFile.is_open())
        {
            cerr << "Error: Could not open the file " << pathToCSV << endl;
            throw ios_base::failure("Failed to open file: " + pathToCSV);
        }



    }






}

void WorkWithCSV(string data, string nameTable)
{
    
    WriteToCSVFileIntoArray(data, nameTable);







}





void WorkWithFile_pk_sequence(string nameTable)
{
    string pkFilePath = "../Source/Схема 1/" + nameTable +"/" + nameTable + "_pk_sequence.txt";

    int currentPk = 0;

    ifstream pkFile(pkFilePath);

    if (pkFile.is_open()) 
    {
        pkFile >> currentPk; 
        pkFile.close();
    } 
    else 
    {
        cerr << "File " << pkFilePath << " is not open. Initializing primary key to 0." << endl;
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

  
}