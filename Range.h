#pragma once
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Range
{
   public:
   typedef ::std::map<string, int> T_RangeMap;
   T_RangeMap checkRange(::std::vector<int> input, int rangeValue);

   
};
