#include "../Headers/WorkWithFiles.h"




void ReadingConfigurationJSON()
{
    string filePath = "/home/pushk/VSCODE/Second-course/Practice/Practice 1/JSON/schema.json";

    json j;

    ifstream file(filePath);
    if (file.is_open()) 
    {
        // Парсим содержимое файла
        j = json::parse(file);

    
        file.close();
    } 
    else 
    {
        cerr << "Не удалось открыть файл: " << filePath << endl;
        return; // Возвращаем код ошибки
    }



    string jsonField = j["name"];

    fs::path mainDir = jsonField;

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
    }
}

