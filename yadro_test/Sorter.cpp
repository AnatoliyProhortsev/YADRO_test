#include "Sorter.h"

void Sorter::sort(const std::string& inputFileName,
			   const std::string& outputFileName,
			   unsigned long long N, const Delay& tapeDelay,
			   std::ostream& debugStream)
{
	std::ifstream inputFile(inputFileName);
	if (!inputFile.is_open())
	{
		debugStream << "--- �� ������� ������� ������� ����.\n";
		return;
	}

	std::ofstream outputFile(outputFileName);
	if (!outputFile.is_open())
	{
		debugStream << "--- �� ������� ������� �������� ����.\n";
		return;
	}
	
	/*
	* � ����� ���� ������������ ������ ���� �����, ������� ������ ������ ���-�� ��������� ������
	* � ������ ����������� �� ������ N ���������;
	*/

	debugStream << "--- ��������� ��������� ����� �� ����� ��������� ����\n";

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
	* ���� ���������� ��������, ����������� �� ��������� � ������ ��� ������
	* � ����, � ������ ��������� �� 1 �������� � �����
	* ���� �������� �� ���������� ����� "��-����������",
	* ����� ����� ������� "�������"
	* (�� ����� ������ ������������ �����, ������ ����� �������)
	*/

	std::list<Tape>			  tmpTapes(--tapeNo); //list ������ ��� ��� ����������� �������� ��������
	std::list<Tape>::iterator tapesIter;

	std::vector<__int32>			column;
	std::vector<__int32>::iterator	minElement;

	unsigned	index = 0;

	debugStream << "--- ������������ ������ �������\n";

	for (auto &iter: tmpTapes)
	{
		iter.openFile();
		column.push_back(iter.readRaw());
	}

	debugStream << "--- ���� � �������� ���� ����������\n";

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

	debugStream << "--- ���������� ���������\n";
}
