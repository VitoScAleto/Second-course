#include "../Headers/ReadingConfigurationJSON.h"

string ReadingJSON::ReturnNameObjectFromStructure(int indexObj, json& j)
{
    string nameObj;

    json structureField = j["structure"];

    auto it = structureField.items().begin();

    advance(it,indexObj);

    nameObj = it.key();

    return nameObj;
}




void ReadingConfigurationJSON()
{


    ReadingJSON classReadingJSON;

    json j = ParseJSON();

    classReadingJSON.CreateMainDir(j);
    classReadingJSON.CreateTable1(j);
    classReadingJSON.CreateTable2(j);
    classReadingJSON.CreateCSVFile(j, 1);
    classReadingJSON.CreateCSVFile(j,2);
  
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
    string fileCSVName = "../Source/Схема 1/" + nameTable + "/1.csv";
    
    ifstream inFile(fileCSVName);
    if(inFile.is_open())
    {
        return;
    }


    ofstream outFile(fileCSVName);

    if (outFile.is_open()) 
    {
        outFile<< nameTable <<"_pk,";
        if (structure.contains(nameTable))
        {
            for (auto& column : structure[nameTable])
            {
                outFile << column.get<string>() << ",";
            }
           
        }
        outFile.close();
        
        cout << "Файл CSV успешно создан: "<< endl;
    } else 
    {
        throw ios_base::failure("Failed to create file: " + fileCSVName );
    }

}



json ParseJSON()
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