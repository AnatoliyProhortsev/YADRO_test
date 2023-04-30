#include "Sorter.h"

void Sorter::sort(const std::string& inputFileName,
			   const std::string& outputFileName,
			   long long N, const Delay& tapeDelay,
			   std::ostream& debugStream)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		debugStream << "-- Не удалось открыть входной файл.\n";
		return;
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		debugStream << "-- Не удалось создать выходной файл.\n";
		return;
	}

	//Посмотреть про асинхронную работу с файлами -> done
	//Если можно будет прикрутить, сделать чтение с файла с std::async()
	// ^ а мне кажется, что можно.

	std::list<Tape>			  tmpTapes; //list потому что при реаллокации съезжает итератор
	std::list<Tape>::iterator tapesIter;
	__int32				dataLine;
	while (!inputFile.eof())
	{
		tmpTapes.emplace_back(tapeDelay);
		for (int i = 0; i < N; i++)
		{
			if (inputFile.eof())
				break;

			inputFile >> dataLine;
			tmpTapes.back().pushBack(dataLine);
		}

		tmpTapes.back().sort();
	}
	inputFile.close();
	
	std::vector<__int32>			column;
	std::vector<__int32>::iterator	minElement;

	unsigned	index = 0;

	for (auto iter: tmpTapes)
	{
		iter.roll(Destination::begin);
		column.push_back(iter.read());
		iter.move(Direction::forward);
	}

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
			(*tapesIter).move(Direction::forward);
			if (!(*tapesIter).isAtEnd())
				*minElement = (*tapesIter).read();
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
}
