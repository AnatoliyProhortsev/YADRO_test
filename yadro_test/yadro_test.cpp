#include <iostream>
#include <string>

#include "Sorter.h"

//Добавить юнит-тесты
//https://helpercode.com/2015/03/04/catch-multi-paradigm-automated-test-framework-for-c/
// 
//Сделать сначала тест-кейс в мейне -> done!
//Обернуть задачу в классы -> 
//

int main()
{
    setlocale(0, "");

    Delay configDelay = { 0,0,0 };
    std::ifstream configFile("cfg.txt");
    if (configFile.is_open())
    {
        configFile >> configDelay.move
            >> configDelay.readWrite
            >> configDelay.roll;

        configFile.close();
    }

    std::string inputFileName;
    std::cout << "Введите название входного файла:\n> ";
    std::cin >> inputFileName;

    std::string outputFileName;
    std::cout << "Введите название выходного файла:\n> ";
    std::cin >> outputFileName;

    Sorter sort;
    sort.sort(inputFileName, outputFileName, 2, configDelay, std::cout);

    return 0;
}

