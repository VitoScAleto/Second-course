#include "../Headers/ReadingConfigurationJSON.h"

string ReturnNameObjectFromStructure(int indexObj, json& j)
{
    string nameObj;

    json structureField = j["structure"];

    auto it = structureField.items().begin();

    advance(it,indexObj);

    nameObj = it.key();

    return nameObj;
}

void ConfigurationForCSVFile(json& j)
{
    json structure = j["structure"];

    for(auto& table : structure.items())
    {
        for(auto& column : table.value())
        {
            cout<<column.get<string>()<<" ";
        }
    }


}



void CreationCSVFile(fs::path pathToDir)
{
    
    string fileCSVName = "1.csv";
    
    fs::path filePathCSV =  pathToDir/fileCSVName;

    ofstream outFile(filePathCSV);

    if (outFile.is_open()) 
    {
       
        outFile.close();
        
        cout << "Файл CSV успешно создан: "<< endl;
    } else 
    {
        cerr << "Ошибка при создании файла CSV." << endl;
    }


}



void ReadingConfigurationJSON()
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
        return; // Возвращаем код ошибки
    }
    
    ConfigurationForCSVFile(j);

    string jsonField = j["name"];

    fs::path mainDir = jsonField;

    fs::path table1 = mainDir/ReturnNameObjectFromStructure(0, j);

    fs::path table2 = mainDir/ReturnNameObjectFromStructure(1, j);

    try 
    {
        
        if (fs::create_directory(mainDir)) 
        {
            cout << "Директория '" << mainDir << "' успешно создана.\n";
        } else 
        {
            cout << "Директория '" << mainDir << "' уже существует.\n";
        }

        
        if (fs::create_directory(table1)) 
        {
            cout << "Директория '" << table1 << "' успешно создана.\n";
        } else 
        {
            cout << "Директория '" << table1 << "' уже существует.\n";
        }

        if (fs::create_directory(table2)) 
        {
            cout << "Директория '" << table2 << "' успешно создана.\n";
        } else 
        {
            cout << "Директория '" << table2 << "' уже существует.\n";
        }
    } 
    catch (const fs::filesystem_error& e) 
    {
        cerr << "Ошибка: " << e.what() << '\n';
    }

    CreationCSVFile(table1);
    CreationCSVFile(table2);
}

