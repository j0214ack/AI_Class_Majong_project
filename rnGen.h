/******************************************************************************
  FileName     [ rnGen.h ]
  PackageName  [ util ]
  Synopsis     [ Random number generator ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2007-2011 LaDs(III), GIEE, NTU, Taiwan ]
******************************************************************************/
#ifndef RN_GEN_H
#define RN_GEN_H

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>  
#include <limits.h>

#define my_srandom  srandom
#define my_random   random

class RandomNumGen
{
   public:
      RandomNumGen() { my_srandom(getpid()); }
      RandomNumGen(unsigned seed) { my_srandom(seed); }
      const int operator() (const int range) const {
         return int(range * (double(my_random()) / INT_MAX));
      }
};

class UnsignRnNumGen
{
   public:
      UnsignRnNumGen() { my_srandom(getpid()); }
      UnsignRnNumGen(unsigned seed) { my_srandom(seed); }
      const unsigned operator() (const unsigned range) const {
         return unsigned(range * (double(my_random()) / UINT_MAX));
      }
};

#endif // RN_GEN_H

