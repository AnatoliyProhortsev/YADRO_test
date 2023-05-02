#include "Sorter.h"

void Sorter::sort(const std::string& inputFileName,
			   const std::string& outputFileName,
			   unsigned long long N, const Delay& tapeDelay,
			   std::ostream& debugStream)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		debugStream << "--- Не удалось открыть входной файл.\n";
		return;
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		debugStream << "--- Не удалось создать выходной файл.\n";
		return;
	}
	
	/*
	* В блоке ниже используется только одна лента, которая создаёт нужное кол-во временных файлов
	* В память загружается не больше N элементов;
	*/

	debugStream << "--- Разбиение исходного файла на файлы временных лент\n";

	Tape tmpTape(tapeDelay);
	unsigned tapeNo = 1;

	__int32				dataLine;
	while (!inputFile.eof())
	{
		
		for (int i = 0; i < N; i++)
		{
			if (inputFile.eof())
				break;

			inputFile >> dataLine;
			tmpTape.pushBack(dataLine);
		}

		tmpTape.sort();
		tmpTape.writeToFile("tmp/" + std::to_string(tapeNo) + ".txt");
		tmpTape.clearTape();
		tapeNo++;
	}
	inputFile.close();
	
	/*
	* Ниже реализован алгоритм, позволяющий не загружать в память все данные
	* с лент, а только считывать по 1 элементу с файла
	* Этот алгоритм не раскрывает ленту "по-настоящему",
	* Имеет место сказать "костыль"
	* (По файлу нельзя перемещаться назад, только вперёд чтением)
	*/

	std::list<Tape>			  tmpTapes(--tapeNo); //list потому что при реаллокации съезжает итератор
	std::list<Tape>::iterator tapesIter;

	std::vector<__int32>			column;
	std::vector<__int32>::iterator	minElement;

	unsigned	index = 0;

	debugStream << "--- Формирование первой колонны\n";

	for (auto &iter: tmpTapes)
	{
		iter.openFile();
		column.push_back(iter.readRaw());
	}

	debugStream << "--- Вход в основной цикл сортировки\n";

	while (!tmpTapes.empty())
	{
		while (!column.empty())
		{
			minElement = std::min_element(column.begin(), column.end());
			outputFile << *minElement << '\n';

			if (minElement != column.end())
				index = std::distance(column.begin(), minElement);
			else
				index = column.size();

			tapesIter = tmpTapes.begin();
			std::advance(tapesIter, index);
			if (!(*tapesIter).isEof())
				*minElement = (*tapesIter).readRaw();
			else
			{
				if (tmpTapes.size() == 1)
				{
					tmpTapes.clear();
					column.clear();
				}
				else if (index == tmpTapes.size())
				{
					tmpTapes.pop_back();
					column.pop_back();
				}
				else
				{
					tapesIter = tmpTapes.begin();
					std::advance(tapesIter, index);
					tmpTapes.erase(tapesIter);
					column.erase(minElement);
				}
			}
		}
	}

	outputFile.close();

	debugStream << "--- Сортировка завершена\n";
}
