#ifndef SORTER
#define SORTER

#include <vector>
#include <algorithm>

#include "Tape.h"

class Sorter
{
public:
	void sort(const std::string &inputFileName,
			  const std::string &outputFileName,
			  unsigned long long N, const Delay &tapeDelay,
			  std::ostream& debugStream);
};

#endif // !SORTER
