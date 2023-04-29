#include "Tape.h"

Tape::Tape()
{
	delay_ = { 0,0,0 };
	head_ = data_.begin();
}

Tape::Tape(Delay delays)
{
	delay_ = delays;
	head_ = data_.begin();
}

Tape::~Tape()
{
	data_.clear();
	head_ = data_.begin();
}

void Tape::move(Direction direction)
{
	_sleep(delay_.move);

	if (direction == Direction::forward && head_ != data_.end())
		head_++;
	else if (direction == Direction::backward && head_ != data_.begin())
		head_--;
}

void Tape::roll(Destination destination)
{
	_sleep(delay_.roll);

	if (destination == Destination::begin)
		head_ = data_.begin();
	else
		head_ = data_.end();
}

void Tape::pushBack(__int32 element)
{
	if (!data_.empty())
	{
		if (head_ == data_.end())
			_sleep(delay_.move);
		else
			_sleep(delay_.roll);
	}
	
	_sleep(delay_.readWrite);

	data_.push_back(element);
	head_ = data_.end();
}

void Tape::pushFront(__int32 element)
{
	if (!data_.empty())
	{
		if (head_ == data_.begin())
			_sleep(delay_.move);
		else
			_sleep(delay_.roll);
	}

	_sleep(delay_.readWrite);

	data_.push_front(element);
	head_ = data_.begin();
}

__int32 Tape::read() const
{
	if (!data_.empty())
	{
		_sleep(delay_.readWrite);
		return *head_;
	}
}

void Tape::write(__int32 data)
{
	if (!data_.empty())
	{
		_sleep(delay_.readWrite);
		*head_ = data;
	}
}

void Tape::sort()
{

}

bool Tape::isAtEnd() const
{
	return head_ == data_.end();
}
