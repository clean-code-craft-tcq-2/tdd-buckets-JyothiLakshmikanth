#pragma once
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

class Range
{
   public:
    typedef enum
    {
      VALID,
      INVALID
    }BreachType;

    struct BoundaryValues
    {
      int max;
      int min;
    };
   typedef ::std::vector< ::std::vector<int>> T_RangeBasedReadingsList;
   typedef vector<pair<int, int> > T_RangeList;

   ::string checkTheRangeAndReadings(::std::vector<int> sequence, int key);

   private:
   BoundaryValues getMaxAndMinValue(::vector<int> sequence);
   ::string prepareOutputInCSVFormat(T_RangeList range, T_RangeBasedReadingsList readingsList);
   T_RangeBasedReadingsList getTheReadings(T_RangeList range, ::vector<int> sequence);
   T_RangeList getRanges(BoundaryValues boundaryValues, int key);
   BreachType validateTheData(::vector<int> sequence, int key);
};
