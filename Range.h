#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

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
   typedef vector<pair<size_t, size_t> > T_RangeList;

   ::string checkTheRangeAndReadings(::std::vector<int> input, int rangeValue);

   private:
   BoundaryValues getMaxAndMinValue(::vector<int> input);
   ::string prepareOutputInCSVFormat(T_RangeList range, T_RangeBasedReadingsList readingsList);
   T_RangeBasedReadingsList getTheReadings(T_RangeList range, ::vector<int> input);
   T_RangeList getRanges(BoundaryValues boundaryValues, int key);
   BreachType validateTheData(::vector<int> input, int key);
};
