#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <ranges>

//Добавить юнит-тесты
//https://helpercode.com/2015/03/04/catch-multi-paradigm-automated-test-framework-for-c/
// 
//Сделать сначала тест-кейс в мейне, потом уйти в классы



//!Пофиксить последний записанный знак перевода каретки в временные файлы!

int main()
{
    std::ifstream inputFile("input.txt");
	std::list<int32_t> tape;
	int tmpSize = 2;
	int curTmp = 1;
	int32_t line = 0;

	while (!inputFile.eof())
	{
		for (int i = 0; i < tmpSize; i++)
		{
			if (inputFile.eof())
				break;

			inputFile >> line;
			tape.push_back(line);
		}

		tape.sort();

		std::ofstream tmpFile(std::to_string(curTmp) + ".txt");
		while (!tape.empty())
		{
			tmpFile << tape.front();
			if (tape.size() != 1)
				tmpFile << '\n';

			tape.pop_front();
		}
		tmpFile.close();
		curTmp++;
	}
	inputFile.close();

	std::ofstream outputFile("output.txt");
	std::vector<std::ifstream> tmpFiles;
	std::vector<std::ifstream>::iterator cFile;

	curTmp--;

	for (curTmp; curTmp != 0; curTmp--)
		tmpFiles.push_back(std::ifstream(std::to_string(curTmp) + ".txt"));

	std::vector<int32_t> column;
	std::vector<int32_t>::iterator cMin;

	line = NULL;
	unsigned index = 0;
	
	for (unsigned i = 0; i < tmpFiles.size(); i++)
	{
		tmpFiles[i] >> line;
		column.push_back(line);
	}

	while (!tmpFiles.empty())
	{
		while (!column.empty())
		{			
			cMin = std::min_element(column.begin(), column.end());
			outputFile << *cMin << '\n';
			
			if (cMin != column.end())
				index = std::distance(column.begin(), cMin);
			else
				index = column.size();

			if (!tmpFiles[index].eof())
			{
				tmpFiles[index] >> line;
				*cMin = line;
			}
			else
			{
				if (tmpFiles.size() == 1)
				{
					tmpFiles.clear();
					column.clear();
				}
				else if (index == tmpFiles.size())
				{
					tmpFiles.pop_back();
					column.pop_back();
				}
				else
				{
					tmpFiles.erase(std::vector<std::ifstream>::iterator(tmpFiles.begin() + index));
					column.erase(cMin);
				}
			}
		}
	}

	outputFile.close();
}

