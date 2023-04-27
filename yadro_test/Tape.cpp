#include "Tape.h"

void Tape::move(Direction direction)
{
	_sleep(delay_.move);

}

void Tape::roll(Direction direction, long int lenght)
{
	_sleep(delay_.roll);

}

__int32 Tape::read()
{
	_sleep(delay_.readWrite);
	return 0;
}

void Tape::write(__int32 data)
{
	_sleep(delay_.readWrite);
}
