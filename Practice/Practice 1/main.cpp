#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void readCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> row;

        // Считывание строки и разделение на элементы
        while (std::getline(ss, item, ',')) {
            
            row.push_back(item);
        }

        // Формирование строки в нужном формате
        std::string output;
        for (size_t i = 0; i < row.size(); ++i) {
            output += row[i];
            if (i < row.size() - 1) {
                output += ","; // Добавляем запятую между элементами
            }
        }

        // Вывод считанных значений в нужном формате
        std::cout << output << std::endl;
    }

    file.close();
}

int main() {
    std::string filename = "1.csv"; // Укажите имя вашего файла
    readCSV(filename);
    return 0;
}