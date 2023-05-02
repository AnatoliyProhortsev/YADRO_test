#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <random>
#include <limits>

#include "Sorter.h"

//Юнит тесты:
#define UNIT_TEST_ENABLE 1
#if UNIT_TEST_ENABLE
bool randomNumsTest();  //Не проходит, чисел на выходе меньше, чем на входе
bool delayTest();       //Не проходит, бросает 1 число(что в выход, что в временной файл)
#endif

int main()
{
    setlocale(0, "");

#if UNIT_TEST_ENABLE
    unsigned testsCompleted = 0;
    testsCompleted += delayTest();
    testsCompleted += randomNumsTest();
    std::cout << "\n- Завершено тестов: (" << testsCompleted << '/' << 2 << ")\n\n";
#endif

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

    Sorter sorter;
    sorter.sort(inputFileName, outputFileName, 2, configDelay, std::cout);

    return 0;
}

#if UNIT_TEST_ENABLE
bool randomNumsTest()
{

#undef min
#undef max

    std::cout << "- Тест на случайных числах(1000 без задержек)\n";

    std::ofstream t1("t1.txt");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, std::numeric_limits<int>::max());

    std::vector<__int32> arr(1000);

    std::cout << "-- Генерация чисел\n";
    __int32 tmp;
    for (int i = 1; i <= 1000; i++)
    {
        tmp = dist(gen);
        t1 << tmp;
        arr.push_back(tmp);
        if (i != 1000)
            t1 << '\n';
    }

    std::cout << "-- Сортировка массива чисел\n";
    std::sort(arr.begin(), arr.end());

    std::cout << "-- Сортировка лентами\n";
    Sorter sorter;
    sorter.sort("t1.txt", "t1_o.txt", 250, { 0, 0, 0 }, std::cout);

    std::cout << "-- Сравнение результатов\n";
    std::ifstream t1_o("t1_o.txt");
    int i = 0;
    while(!t1_o.eof())
    {
        t1_o >> tmp;
        if (tmp != arr[i])
        {
            std::cout << "-- Тест не пройден\n";
            return false;
        }
        i++;
    }
    std::cout << "-- Тест пройден\n";
    return true;
}
#endif

#if UNIT_TEST_ENABLE
bool delayTest()
{

#undef min
#undef max

    std::cout << "\n- Тест задержки (40 чисел, задержки{25, 25, 25})\n";

    std::ofstream t1("t2.txt");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, std::numeric_limits<int>::max());

    std::vector<__int32> arr(40);

    std::cout << "-- Генерация чисел\n";
    __int32 tmp;
    for (int i = 1; i <= 40; i++)
    {
        tmp = dist(gen);
        t1 << tmp;
        arr.push_back(tmp);
        if (i != 40)
            t1 << '\n';
    }

    std::cout << "-- Сортировка массива чисел\n";
    std::sort(arr.begin(), arr.end());

    std::cout << "-- Сортировка лентами\n";
    Sorter sorter;
    sorter.sort("t2.txt", "t2_o.txt", 10, { 25, 25, 25 }, std::cout);

    std::cout << "-- Сравнение результатов\n";
    std::ifstream t1_o("t2_o.txt");
    int i = 0;
    while (!t1_o.eof())
    {
        t1_o >> tmp;
        if (tmp != arr[i])
        {
            std::cout << "-- Тест не пройден\n";
            return false;
        }
        i++;
    }
    std::cout << "-- Тест пройден\n";
    return true;
}
#endif


