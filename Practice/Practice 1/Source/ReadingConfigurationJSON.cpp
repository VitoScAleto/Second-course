#include "../Headers/ReadingConfigurationJSON.h"

string ReadingJSON::GetNameMainDir()
{
    return nameMainDirJSON;

}


bool ReadingJSON::IsValidTable(const string nameTable)
{
    for(int i = 0; i < nameTablesJSON.getSize();i++)
    {
        if(nameTable == nameTablesJSON[i])
        { 
            return true;

        }
    }
    return false;
}

bool ReadingJSON::IsValidColumns(const string nameTable, const string nameColumn)
{
    nameColumnsJSON.~LinkedList();
    FillingTheListColumnsFromTheSchema(nameTable);

    for(int i = 0; i < nameColumnsJSON.getSize(); i++)
    {
        if(nameColumnsJSON[i] == nameColumn)
        {
            return true;
        }
    }
    return false;
}

template <typename T>
void ReadingJSON::GetColumnsFromSchema(LinkedList<T>& List,const string nameTable)
{
     json j = ParseJSON();

    json structure = j["structure"];
    
    if (structure.contains(nameTable))
    {
        string columnsPk_sequence = nameTable + "_pk";
        List.push_back(columnsPk_sequence);

        for (auto& column : structure[nameTable])
        {
            List.push_back(column.get<string>());
        }
           
    }

    
}

void ReadingJSON::FillingTheListTableFromTheSchema()
{   
    string tableName;
    json j = ParseJSON();

    for (auto& JTable : j["structure"].items()) 
    {
        tableName = JTable.key();
        nameTablesJSON.push_back(tableName);
    }

}

void ReadingJSON::FillingTheListColumnsFromTheSchema(string nameTable)
{   
    json j = ParseJSON();

    json structure = j["structure"];

    if (structure.contains(nameTable))
    {
        string columnsPk_sequence = nameTable + "_pk";
        nameColumnsJSON.push_back(columnsPk_sequence);

        for (auto& column : structure[nameTable])
        {
            nameColumnsJSON.push_back(column.get<string>());
        }
           
    }

}

void ReadingJSON::ReadingConfigurationJSON(const string pathShemaJSON)
{
    json j = ParseJSON();

    tuples_limit = j["tuples_limit"];
    FillingTheListTableFromTheSchema();

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
    nameMainDirJSON = j["name"];
    
    fs::path mainDir =  nameMainDirJSON;

    for(int i = 0; i < nameTablesJSON.getSize(); i++)
    {
        fs::path table = mainDir/nameTablesJSON[i];

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
        
    }
    
}


void ReadingJSON::CreateCSVFile(json& j)
{
    json structure = j["structure"];


    for(int i = 0; i < nameTablesJSON.getSize(); i++)
    {
        FillingTheListColumnsFromTheSchema(nameTablesJSON[i]);

        string fileCSVName = "../Source/Схема 1/" + nameTablesJSON[i] + "/1.csv";
        
        ifstream inFile(fileCSVName);
        
        if(inFile.is_open())
        {
            return;
        }

        ofstream outFile(fileCSVName);

        if (outFile.is_open()) 
        {
            for(int i = 0; i < nameColumnsJSON.getSize(); i++)
            {
                outFile<<nameColumnsJSON[i]<<",";
                
            }
            outFile.close();
            
            cout << "Файл CSV успешно создан: "<< endl;
        } 
        else 
        {
            throw ios_base::failure("Failed to create file: " + fileCSVName );
        }
        nameColumnsJSON.~LinkedList();
    }
}



json ReadingJSON::ParseJSON()
{
    string pathFileSchemaJson = "../JSON/schema.json";

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

