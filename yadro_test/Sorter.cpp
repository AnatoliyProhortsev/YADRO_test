#include "Sorter.h"

void Sorter::sort(const std::string& inputFileName,
			   const std::string& outputFileName,
			   long long N, const Delay& tapeDelay,
			   std::ostream& debugStream)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		debugStream << "-- �� ������� ������� ������� ����.\n";
		return;
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		debugStream << "-- �� ������� ������� �������� ����.\n";
		return;
	}

	//���������� ��� ����������� ������ � ������� -> done
	//���� ����� ����� ����������, ������� ������ � ����� � std::async()
	// ^ � ��� �������, ��� �����.

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
