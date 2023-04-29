#ifndef TAPE
#define TAPE

#include <list>
#include <fstream>

enum class Direction : short
{
	forward = -1,
	backward = 1
};

enum class Destination : short
{
	begin = -1,
	end = 1
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
			Tape();
			Tape(Delay delays);
			~Tape();
	void	move(Direction direction);
	void	roll(Destination destination);
	void	pushBack(__int32 element);
	void	pushFront(__int32 element);
	__int32 read() const;
	void	write(__int32 data);
	void	sort();
	bool	isAtEnd() const;

private :
	Delay						 delay_;
	std::list<__int32>			 data_;
	std::list<__int32>::iterator head_;
};

#endif // !TAPE
