#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"

#include <vector>
#include <map>
#include <string>
#define private public
#include "Range.h"

using namespace std;
Range range;
Range::T_RangeList prepareExpectedRangeList(::std::vector<int> input, int key)
{

  return rangelist;
}
TEST_CASE("OnCheckRange_CheckForBreachType_IsValidOrNot")
{
  int key = 3;
  ::std::vector<int> input = {2,4,3,6,1,6,7,8,9,3};
  BreachType breach = range.checkRange(input,key);
  REQUIRE(breach == VALID);
  input = {2,4,3,6,-1,6,7,8,-9,3};
  REQUIRE(breach == INVALID);
}

TEST_CASE("ForTheGivenSequence_FindTheMaxAndMinValues")
{
  ::std::vector<int> input = {2,4,3,6,1,6,7,8,9,3};
  BoundaryValues values = range.getMaxAndMinValue(input);
  REQUIRE(values.min == 1);
  REQUIRE(values.max == 9);
}

TEST_CASE("ForTheGivenSequence_FindTheValidRanges")
{
  int key = 3;
  ::std::vector<int> input = {2,4,3,6,1,6,7,8,9,3};
  Range::T_RangeList actualRangelist, expectedRangeList;
  expectedRangeList.push_back(make_pair(1,3));
  expectedRangeList.push_back(make_pair(4,6));
  expectedRangeList.push_back(make_pair(7,9));
  actualRangelist = range.getRanges(input, key);
  SECTION("Check the size")
  {
    REQUIRE(expectedRangeList.size() == actualRangelist.size())
    SECTION("check the list")
    {
      REQUIRE(expectedRangeList == actualRangelist);
    }
    SECTION("Check the content")
    {
      for(int i = 0; i<expectedRangeList.size();++i)
      {
        REQUIRE(expectedRangeList[i].first == actualRangelist[i].first);
        REQUIRE(expectedRangeList[i].second == actualRangelist[i].second);
      }
    }
  }
}

TEST_CASE("ForGivenSequenceRange_GetTheReadings")
{
  int key = 3;
  ::std::vector<int> input = {2,4,3,6,1,6,7,8,9,3};
  Range::T_RangeList rangelist;
  rangelist.push_back(make_pair(1,3));
  rangelist.push_back(make_pair(4,6));
  rangelist.push_back(make_pair(7,9));
  Range::T_RangeBasedReadingsList expectedRangeBasedReadingsList, actualRangeBasedReadingsList;
  expectedRangeBasedReadingsList.push_back({2,1,3,1});
  expectedRangeBasedReadingsList.push_back({4,5,6,4});
  expectedRangeBasedReadingsList.push_back({7,9});
  actualRangeBasedReadingsList = range.getTheReadings(rangelist, input);
  SECTION("Check the size")
  {
    REQUIRE(expectedRangeBasedReadingsList.size() == actualRangeBasedReadingsList.size())
    SECTION("check the list")
    {
      REQUIRE(expectedRangeBasedReadingsList == actualRangeBasedReadingsList);
    }
    SECTION("Check the content")
    {
      for (size_t i = 0; i < actualRangeBasedReadingsList.size(); i++)
      {
        for(size_t j=0;j<actualRangeBasedReadingsList[i].size();j++)
        {
            REQUIRE(actualRangeBasedReadingsList[i][j] == expectedRangeBasedReadingsList[i][j]);
        }
      }
    }
  }
}
