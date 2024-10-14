#include "../Headers/ReadingConfigurationJSON.h"

string ReadingJSON::GetNameMainDir()
{
    return nameMainDirJSON;

}


bool ReadingJSON::IsValidTable(const string nameTable)
{
    FillingTheListFromTheSchema();

    while(nameTables.getSize() != 0)
    {
        if(nameTable == nameTables.getHead())
        { 
            nameTables.~LinkedList();
            return true;

        }
        nameTables.pop_front();
    }
    nameTables.~LinkedList();
    return false;
}



void ReadingJSON::FillingTheListFromTheSchema()
{   
    string tableName;
    json j = ParseJSON();

    for (auto& JTable : j["structure"].items()) 
    {
     tableName = JTable.key();
     nameTables.push_back(tableName);
    }

}

void ReadingJSON::ReadingConfigurationJSON(const string pathShemaJSON)
{
    json j = ParseJSON();

    tuples_limit = j["tuples_limit"];

    CreateMainDir(j);
    CreateTable(j);
    CreateCSVFile(j);
  
}


void ReadingJSON::CreateMainDir(json& j)
{
    nameMainDirJSON = j["name"];
    
    fs::path mainDir =  nameMainDirJSON;

    try 
    {
        
        if (fs::create_directory(mainDir)) 
        {
            cout << "Директория '" << mainDir << "' успешно создана.\n";
        } 
        else 
        {
            cout << "Директория '" << mainDir << "' уже существует.\n";
        } 
    }
    catch (const fs::filesystem_error& e) 
    {
        cerr << "Ошибка создания: " << mainDir << e.what() << '\n';
    }

}

void ReadingJSON::CreateTable(json& j)
{
    FillingTheListFromTheSchema();

    nameMainDirJSON = j["name"];
    
    fs::path mainDir =  nameMainDirJSON;

    while(nameTables.getSize()!=0)
    {
        fs::path table = mainDir/nameTables.getHead();

        try
        {
            if (fs::create_directory(table)) 
            {
                cout << "Директория '" << table << "' успешно создана.\n";
            } 
            else 
            {
                cout << "Директория '" << table << "' уже существует.\n";
            }
        }
        catch (const fs::filesystem_error& e) 
        {
            cerr << "Ошибка создание директории: "<< table << e.what() << '\n';
        }
        nameTables.pop_front();
    }
    nameTables.~LinkedList();
}


template <typename T>
Queue<T> ReadingJSON::GetColumnsFromSchema(const string nameTable)
{
    FillingTheListFromTheSchema();
    
    bool tableFound = false; 

    while (nameTables.getSize() != 0)
    {
        if (nameTable == nameTables.getHead())
        {
            tableFound = true; 
            break; 
        }
        nameTables.pop_front(); 
    }
    
    
    if (!tableFound)
    {
        cerr << "Unknown table. Function(GetColumnsFromSchema)" << endl;
        throw invalid_argument("This table not found");
    }
    
    

    json j = ParseJSON();
    
    Queue<string> queueColumnsFromSchema;

    json structure = j["structure"];

    if (structure.contains(nameTable))
        {
            string columnsPk_sequence = nameTable + "_pk";
            queueColumnsFromSchema.push_back(columnsPk_sequence);

            for (auto& column : structure[nameTable])
            {
               queueColumnsFromSchema.push_back(column.get<string>());
            }
           
        }

    return queueColumnsFromSchema;
}

void ReadingJSON::CreateCSVFile(json& j)
{
    json structure = j["structure"];

    FillingTheListFromTheSchema();

    while(nameTables.getSize()!=0)
    {
        Queue<string> ColumnsForCSV = GetColumnsFromSchema<string>(nameTables.getHead());

        string fileCSVName = "../Source/Схема 1/" + nameTables.getHead() + "/1.csv";
        
        ifstream inFile(fileCSVName);
        if(inFile.is_open())
        {
            return;
        }

        ofstream outFile(fileCSVName);

        if (outFile.is_open()) 
        {
        
            while(ColumnsForCSV.getSize()!=0)
            {
                outFile<<ColumnsForCSV.getFront()<<",";
                ColumnsForCSV.pop_front();
            }
            outFile.close();
            
            cout << "Файл CSV успешно создан: "<< endl;
        } else 
        {
            throw ios_base::failure("Failed to create file: " + fileCSVName );
        }
        nameTables.pop_front();
    
    }
    nameTables.~LinkedList();
}



json ReadingJSON::ParseJSON()
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
        throw ios_base::failure("Failed to open file: " + pathFileSchemaJson );
    }
    

    return j;
}

// string ReadingJSON::IsValidTuplesLimitInCSV(string nameTable)
// {
    



// }


// int CountElementInCSV(string nameTable)
// {
//     numberElementInCSV = 0;

//     if(JSON.IsValidTable(nameTable) == true)
//     {
//         string pathToCSVInsert = "../Source/Схема 1/"+nameTable + "/1.csv";

//         ifstream outFile(pathToCSVInsert);
        
//         if(!outFile.is_open())
//         {
        
//         throw ios_base::failure("Function(CountElementInCSV()) -> Failed to open file: " + pathToCSVInsert);
//         }

//         string line;

//         while (getline(outFile, line)) 
//         {
//            stringstream ss(line);
//            string item;

//             while (getline(ss, item, ',')) 
//             {
//                 numberElementInCSV++;
//             }

//         }
//         outFile.close();
//         return numberElementInCSV;
//     }

//     throw invalid_argument("Function(CountElementInCSVInsert()) -> Invalid table name: " + nameTable);
// }


// string ReadingJSON::listFilesInDirectory(const string nameTable) 
// {
//     string directoryPath = "../Source/" + GetNameMainDir()+"/" + nameTable;
//     try {
//         for (const auto& entry : fs::directory_iterator(directoryPath)) 
//         {
//             if (fs::is_regular_file(entry.status())) 
//             {
//                 entry.path().filename().string();
//             }
//         }
//     } catch (const fs::filesystem_error& e) 
//     {
//         cerr << "Ошибка доступа к директории: " << e.what() << endl;
//     }
// }