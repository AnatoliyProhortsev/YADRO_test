#include "Tape.h"

Tape::Tape()
{
	delay_ = { 0,0,0 };
	tapeNo_ = tapesCount++;
}

Tape::Tape(Delay delays)
{
	delay_ = delays;
	tapeNo_ = tapesCount++;
}

Tape::~Tape()
{
	data_.clear();
	head_ = data_.end();
	file_.close();
	tapesCount--;
}

void Tape::writeToFile()
{
	std::ofstream file("tmp/" + std::to_string(tapeNo_) + ".txt");

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

void Tape::writeToFile(std::string fileName)
{
	std::ofstream file(fileName);

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
	std::ifstream file("tmp/" + std::to_string(tapeNo_) + ".txt");

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

bool Tape::openFile()
{
	file_.open("tmp/" + std::to_string(tapeNo_) + ".txt");
	return file_.is_open();
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

__int32 Tape::read() const
{
	if (!data_.empty() && head_ != data_.end())
	{
		Sleep(delay_.readWrite);
		return *head_;
	}
}

__int32 Tape::readRaw()
{
	__int32 tmp;
	file_ >> tmp;
	return tmp;
}

void Tape::write(__int32 data)
{
	if (!data_.empty())
	{
		Sleep(delay_.readWrite);
		*head_ = data;
	}
}

void Tape::clearTape()
{
	data_.clear();
	file_.close();
}

bool Tape::isAtEnd() const
{
	return head_ == data_.end();
}

bool Tape::isEof() const
{
	return file_.eof();
}
