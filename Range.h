#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

typedef enum
{
    VALID,
    INVALID
}BreachType;

typedef struct
{
    int max;
    int min;
}BoundValues;

class Range
{
   public:
   typedef ::std::vector< ::std::vector<int>> T_RangeBasedReadingsList;
   typedef vector<pair<size_t, size_t> > T_RangeList;

   ::string checkTheRangeAndReadings(::std::vector<int> input, int rangeValue);

   private:
   BoundValues getMaxAndMinValue(::vector<int> input);
   ::string prepareOutputInCSVFormat(T_RangeList range, T_RangeBasedReadingsList readingsList);
   T_RangeBasedReadingsList getTheReadings(T_RangeList range, ::vector<int> input);
   T_RangeList getRanges(BoundValues values, int key);
   BreachType validateTheData(::vector<int> input, int key);
};
