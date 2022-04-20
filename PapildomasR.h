#ifndef PAPILDOMASR_H_INCLUDED
#define PAPILDOMASR_H_INCLUDED
#include <iostream>
#include <string>
#include <set>
#include <iterator>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>

int getRandomNumber(int min, int max)
	{
		static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
		return static_cast<int>(rand() * fraction * (max - min + 1) + min);
	}


#endif // PAPILDOMASR_H_INCLUDED
