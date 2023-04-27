#ifndef TAPE
#define TAPE

#include <list>
#include <fstream>

enum class Direction : short
{
	forward = -1,
	backward = 1
};

struct Delay
{
	unsigned move;
	unsigned roll;
	unsigned readWrite;
};

class Tape
{
public :
	void	move(Direction direction);
	void	roll(Direction direction, long int lenght);
	__int32 read();
	void	write(__int32 data);

private :
	Delay			   delay_;
	std::list<__int32> data_;
};

#endif // !TAPE
