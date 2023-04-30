#include "Tape.h"

Tape::Tape()
{
	delay_ = { 0,0,0 };
	tapeNo_++;
}

Tape::Tape(Delay delays)
{
	delay_ = delays;
	tapeNo_++;
}

Tape::~Tape()
{
	data_.clear();
	head_ = data_.end();
	tapeNo_--;
}

void Tape::writeToFile()
{
	std::ofstream file(std::to_string(tapeNo_) + ".txt");

	if (file.is_open())
	{
		unsigned i = 1;
		roll(Destination::begin);
		while (!isAtEnd())
		{
			file << read();
			if (i != data_.size())
				file << '\n';

			move(Direction::forward);
			i++;
		}

		file.close();
	}
	roll(Destination::begin);
}

void Tape::readFromFile()
{
	std::ifstream file(std::to_string(tapeNo_) + ".txt");

	if (file.is_open())
	{
		__int32 line;
		while (!file.eof())
		{
			file >> line;
			pushBack(line);
		}

		file.close();
	}
}

void Tape::readFromFile(unsigned long size)
{
	if (size == 0)
		return;

	std::ifstream file(std::to_string(tapeNo_) + ".txt");

	if (file.is_open())
	{
		unsigned long count = 0;
		__int32 line;
		while (!file.eof() || count != size)
		{
			file >> line;
			pushBack(line);
			count++;
		}

		file.close();
	}
}

void Tape::sort()
{
	if (data_.size() < 2)
		return;

	roll(Destination::begin);

	unsigned bufPos = 1;
	unsigned curPos, minPos;
	__int32 buf, curBuf, min;
	bool hasMin;
	while (bufPos != data_.size())
	{
		hasMin = false;
		buf = read();
		min = buf;
		curBuf = buf;
		curPos = bufPos;
		minPos = bufPos;
		move(Direction::forward);
		curPos++;
		while (!isAtEnd())
		{
			curBuf = read();
			if (curBuf < buf)
			{
				hasMin = true;
				min = curBuf;
				minPos = curPos;
			}
				
			move(Direction::forward);
			curPos++;
		}
		//счас проблема вот тут, надо правильно высчитывать куда двигать голову.
		if (hasMin)
		{
			roll(minPos - curPos);
			curPos -= curPos - minPos;
			write(buf);
			roll(bufPos - curPos);
			curPos -= curPos - bufPos;
			write(min);
		}
		
		roll(bufPos - curPos);
		bufPos++;
	}

	roll(Destination::begin);

	writeToFile();
}

void Tape::move(Direction direction)
{
	Sleep(delay_.move);

	if (direction == Direction::forward && head_ != data_.end())
		head_++;
	else if (direction == Direction::backward && head_ != data_.begin())
		head_--;
}

void Tape::roll(Destination destination)
{
	Sleep(delay_.roll);

	if (destination == Destination::begin)
		head_ = data_.begin();
	else if(destination == Destination::end)
		head_ = data_.end();
}

void Tape::roll(int step)
{
	Sleep(delay_.roll);
	std::advance(head_, step);
}

void Tape::pushBack(__int32 element)
{
	Sleep(delay_.roll);
	Sleep(delay_.readWrite);
	data_.push_back(element);
	head_ = data_.end();
	std::advance(head_, -1);
}

void Tape::pushFront(__int32 element)
{
	Sleep(delay_.roll);
	Sleep(delay_.readWrite);
	data_.push_front(element);
	head_ = data_.begin();
}

__int32 Tape::read() const
{
	if (!data_.empty() && head_ != data_.end())
	{
		Sleep(delay_.readWrite);
		return *head_;
	}
}

void Tape::write(__int32 data)
{
	if (!data_.empty())
	{
		Sleep(delay_.readWrite);
		*head_ = data;
	}
}

__int32 Tape::getMinElement()
{
	__int32 min = read();

	if (data_.size() == 1)
		return min;

	roll(Destination::begin);
	__int32 tmp;
	while (!isAtEnd())
	{
		tmp = read();
		if (tmp < min)
			min = tmp;
		move(Direction::forward);
	}

	roll(Destination::begin);

	return min;
}

size_t Tape::getElementCount()
{
	return data_.size();
}

bool Tape::isAtEnd() const
{
	return head_ == data_.end();
}
