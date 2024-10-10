#include "../Headers/ReadingConfigurationJSON.h"
 
string ReadingJSON::GetNameTable1JSON()
{
    return nameTable1;
}
 
string ReadingJSON::GetNameTable2JSON()
{
    return nameTable2;
}
string ReadingJSON::GetPathToTable1JSON()
{
    return pathToTable1;
}
    
string ReadingJSON::GetPathToTable2JSON()
{
    return pathToTable2;
}


string ReadingJSON::ReturnNameObjectFromStructure(int indexObj, json& j)
{
    string nameObj;

    json structureField = j["structure"];

    auto it = structureField.items().begin();

    advance(it,indexObj);

    nameObj = it.key();

    return nameObj;
}



void ReadingJSON::ReadingConfigurationJSON(string pathShemaJSON)
{
    

    json j = ParseJSON();

    tuples_limit = j["tuples_limit"];

    CreateMainDir(j);
    CreateTable1(j);
    CreateTable2(j);
    CreateCSVFile(j, 1);
    CreateCSVFile(j,2);
  
}


void ReadingJSON::CreateMainDir(json& j)
{
    name = j["name"];
    
    fs::path mainDir = name;

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

void ReadingJSON::CreateTable1(json& j)
{
    name = j["name"];
    
    fs::path mainDir = name;

    nameTable1 = ReturnNameObjectFromStructure(0, j);

    fs::path table1 = mainDir/ReturnNameObjectFromStructure(0, j);

    pathToTable1 = table1;

    try
    {
        if (fs::create_directory(table1)) 
        {
            cout << "Директория '" << table1 << "' успешно создана.\n";
        } 
        else 
        {
            cout << "Директория '" << table1 << "' уже существует.\n";
        }
    }
    catch (const fs::filesystem_error& e) 
    {
        cerr << "Ошибка создание директории: "<< table1 << e.what() << '\n';
    }
}

void ReadingJSON::CreateTable2(json& j)
{
    name = j["name"];
    
    fs::path mainDir = name;

    nameTable2 = ReturnNameObjectFromStructure(1, j);

    fs::path table2 = mainDir/ReturnNameObjectFromStructure(1, j);

    pathToTable2 = table2;

    try
    {
        if (fs::create_directory(table2)) 
        {
            cout << "Директория '" << table2 << "' успешно создана.\n";
        } 
        else 
        {
            cout << "Директория '" << table2 << "' уже существует.\n";
        }
    }
    catch (const fs::filesystem_error& e) 
    {
        cerr << "Ошибка создание директории: " << table2 << e.what() << '\n';
    }
    
    
}

template <typename T>
Queue<T> ReadingJSON::GetColumnsFromSchema(string nameTable)
{
    if (!(nameTable == nameTable1 || nameTable == nameTable2)) 
    {
        std::cerr << "Unknown table. Function(GetColumnsFromSchema)" << std::endl;
        throw std::invalid_argument("This table not found");
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

void ReadingJSON::CreateCSVFile(json& j, int n)
{
    json structure = j["structure"];

    string nameTable;

    if(n == 1)
    {
        nameTable = nameTable1;
    }
    else if(n == 2)
    {
        nameTable = nameTable2;

    }
    else
    {
        throw invalid_argument("This table not found");
    }
    Queue<string> ColumnsForCSV = GetColumnsFromSchema<string>(nameTable);

    string fileCSVName = "../Source/Схема 1/" + nameTable + "/1.csv";
    
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