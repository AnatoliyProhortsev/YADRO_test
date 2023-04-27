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

    std::string configFileName;
    std::cout << "Введите название файла-конфигурации:\n> ";
    std::cin >> configFileName;

    std::ifstream configFile(configFileName);
    if (configFile.is_open())
    {
        
    }
    else
    {

    }

    return 0;
}

