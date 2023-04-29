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

	Tape tmpTape(tapeDelay);
	unsigned curTmpFile = 1;
	__int32 dataLine;
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
	}


}
