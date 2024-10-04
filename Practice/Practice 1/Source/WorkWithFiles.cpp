#include "../Headers/WorkWithFiles.h"

<<<<<<< HEAD
string ReturnNameObjectFromStructure(int indexObj, json& j)
{
    string nameObj;

    json structureField = j["structure"];

    auto it = structureField.items().begin();

    advance(it,indexObj);

    nameObj = it.key();

    return nameObj;
}

void WorkWithCSVFile(fs::path pathCSV, json& j)
{
    ofstream outFile(pathCSV);

    if (outFile.is_open()) 
    {
        outFile << "Hello, World!\n";
        outFile.close();
        
        cout << "Файл успешно создан: "<< endl;
    } else {
        cerr << "Ошибка при создании файла." << endl;
    }


}
=======
>>>>>>> 392672e (Added WorkWithFiles.h. Added functionality for working with files)



void ReadingConfigurationJSON()
{
<<<<<<< HEAD
    string pathFileSchemaJson = "/home/pushk/VSCODE/Second-course/Practice/Practice 1/JSON/schema.json";

    json j;

    ifstream file(pathFileSchemaJson);
=======
    string filePath = "/home/pushk/VSCODE/Second-course/Practice/Practice 1/JSON/schema.json";

    json j;

    ifstream file(filePath);
>>>>>>> 392672e (Added WorkWithFiles.h. Added functionality for working with files)
    if (file.is_open()) 
    {
        // Парсим содержимое файла
        j = json::parse(file);

    
        file.close();
    } 
    else 
    {
<<<<<<< HEAD
        cerr << "Не удалось открыть файл: " << pathFileSchemaJson << endl;
        return; // Возвращаем код ошибки
    }
    
=======
        cerr << "Не удалось открыть файл: " << filePath << endl;
        return; // Возвращаем код ошибки
    }


>>>>>>> 392672e (Added WorkWithFiles.h. Added functionality for working with files)

    string jsonField = j["name"];

    fs::path mainDir = jsonField;

<<<<<<< HEAD
    fs::path table1 = mainDir/ReturnNameObjectFromStructure(0, j);

    fs::path table2 = mainDir/ReturnNameObjectFromStructure(1, j);

    WorkWithCSVFile(table1, j);
    WorkWithCSVFile(table2, j);
    
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
=======
    jsonField = j["structure"];

    fs::path table1 = mainDir/"jsonField";

    jsonField = j["structure"]["Таблица2"];

    fs::path table2 = mainDir/"jsonField";

    try {
        // Создание главной директории
        if (fs::create_directory(mainDir)) {
            std::cout << "Директория '" << mainDir << "' успешно создана.\n";
        } else {
            std::cout << "Директория '" << mainDir << "' уже существует.\n";
        }

        // Создание поддиректорий
        if (fs::create_directory(table1)) {
            std::cout << "Директория '" << table1 << "' успешно создана.\n";
        } else {
            std::cout << "Директория '" << table1 << "' уже существует.\n";
        }

        if (fs::create_directory(table2)) {
            std::cout << "Директория '" << table2 << "' успешно создана.\n";
        } else {
            std::cout << "Директория '" << table2 << "' уже существует.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка: " << e.what() << '\n';
>>>>>>> 392672e (Added WorkWithFiles.h. Added functionality for working with files)
    }
}

