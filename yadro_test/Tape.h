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

static inline unsigned		 tapesCount{ 0 };

class Tape
{
public:
			Tape();
			Tape(Delay delays);
			~Tape();
	void	writeToFile();
	void	writeToFile(std::string fileName);
	void	readFromFile();
	bool	openFile();
	void	sort();
	void	move(Direction direction);
	void	roll(Destination destination);
	void	roll(int step);
	void	pushBack(__int32 element);
	void	write(__int32 data);
	void	clearTape();
	__int32 read() const;
	__int32 readRaw();
	bool	isAtEnd() const;
	bool	isEof() const;

private:
	Delay						 delay_;
	std::list<__int32>			 data_;
	std::list<__int32>::iterator head_;
	std::ifstream				 file_;
	unsigned					 tapeNo_;
};

#endif // !TAPE
