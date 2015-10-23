// +-------------------------------------------------------------------------
// | prelude.h
// | 
// | Author: Gilbert Bernstein
// +-------------------------------------------------------------------------
// | COPYRIGHT:
// |    Copyright Gilbert Bernstein 2013
// |    See the included COPYRIGHT file for further details.
// |    
// |    This file is part of the Cork library.
// |
// |    Cork is free software: you can redistribute it and/or modify
// |    it under the terms of the GNU Lesser General Public License as
// |    published by the Free Software Foundation, either version 3 of
// |    the License, or (at your option) any later version.
// |
// |    Cork is distributed in the hope that it will be useful,
// |    but WITHOUT ANY WARRANTY; without even the implied warranty of
// |    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// |    GNU Lesser General Public License for more details.
// |
// |    You should have received a copy 
// |    of the GNU Lesser General Public License
// |    along with Cork.  If not, see <http://www.gnu.org/licenses/>.
// +-------------------------------------------------------------------------
#pragma once

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>




#ifndef uint
typedef unsigned int uint;
#endif

#ifndef byte
typedef unsigned char byte;
#endif



// ***********
// * Logging

// error log -- silent; will not stop program
std::ostream &err();

#ifdef CORK_DEBUG
	#ifndef ENSURE
	#define ENSURE(STATEMENT) { \
		if(!(STATEMENT)) { \
			std::cerr << "ENSURE FAILED at " \
					  << __FILE__ << ", line #" << __LINE__ << ":\n" \
					  << "    " << #STATEMENT << std::endl; \
			err()     << "ENSURE FAILED at " \
					  << __FILE__ << ", line #" << __LINE__ << ":\n" \
					  << "    " << #STATEMENT << std::endl; \
			__debugbreak(); \
		} \
	}
	#endif // ENSURE
#else
	#define ENSURE(STATEMENT)
#endif

// Use ERROR to print an error message tagged with the given file/line #
#ifndef CORK_ERROR
#define CORK_ERROR(message) { \
    std::cerr << "error at " \
              << __FILE__ << ", line #" << __LINE__ << ": " \
              << (message) << std::endl; \
    err()     << "error at " \
              << __FILE__ << ", line #" << __LINE__ << ": " \
              << (message) << std::endl; \
}
#endif // CORK_ERROR

// Use MARKER for debugging to create a trace of control flow...
#ifndef MARKER
#define MARKER(message) { \
    std::cout << "marker at " \
              << __FILE__ << ", line #" << __LINE__ << ": " \
              << (message) << std::endl; \
}
#endif // MARKER

// ***********
// * Assorted

// snap the value a into the specified range

inline double clamp(double a, double mina, double maxa)
{
    return std::min(maxa, std::max(mina, a));
}

inline float  clamp(float  a, float  mina, float  maxa)
{
    return std::min(maxa, std::max(mina, a));
}

// modulo the value a into the specified range

inline double wrap(double a, double mina, double maxa)
{
    double val = std::fmod(a - mina, maxa - mina);
    if(val < 0.0) val += maxa-mina;
    return val + mina;
}

inline float  wrap(float  a, float  mina, float  maxa)
{
    float val = std::fmod(a - mina, maxa - mina);
    if(val < 0.0) val += maxa-mina;
    return val + mina;
}

inline double deg2rad(double deg)
{
    return (M_PI/180.0) * deg;
}

inline double rad2deg(double rad)
{
    return (180.0/M_PI) * rad;
}




// ***********
// * Random

// need functions that allow for the random source
// to be made more deterministic for replays...

inline void initRand()
{
    // currently none!  Should seed using clock
    srand(uint(time(0)));
}


inline double drand(double min, double max)
{
    const double invMAX = 1.0/double(RAND_MAX);
    double rand0to1 = double(std::rand())*invMAX;

    return( ((max-min) * rand0to1) + min );
}


inline size_t randMod( size_t		range )
{
    return std::rand() % range;
}



