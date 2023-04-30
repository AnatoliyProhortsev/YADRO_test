#ifndef TAPE
#define TAPE

#include "windows.h"

#include <list>
#include <fstream>
#include <string>

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
public:
			Tape();
			Tape(Delay delays);
			~Tape();
	void	writeToFile();
	void	readFromFile();
	void	readFromFile(unsigned long size);
	void	sort();
	void	move(Direction direction);
	void	roll(Destination destination);
	void	roll(int step);
	void	pushBack(__int32 element);
	void	pushFront(__int32 element);
	void	write(__int32 data);
	__int32 read() const;
	__int32	getMinElement();
	size_t	getElementCount();
	bool	isAtEnd() const;

private:
	Delay						 delay_;
	std::list<__int32>			 data_;
	std::list<__int32>::iterator head_;
	std::string					 fileName_;
	static inline unsigned		 tapeNo_{ 0 }; //Починить, хуйню выдаёт
};

#endif // !TAPE
