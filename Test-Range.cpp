#pragma
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"

#include <vector>
#include <map>
#include <string>
#define private public
#include "Range.h"

using namespace std;
Range range;

TEST_CASE("ValidateTheData_CheckForBreachType_IsValidOrNot")
{
  ::std::vector<int> validSequence = {2,4,3,6,1,6,7,8,9,3};
  Range::BreachType breach;
  SECTION("Check For Key Value 0")
  {
    int key = 0;
    breach = range.validateTheData(validSequence,key);
    REQUIRE(breach == INVALID);
  }
  SECTION("Check for negative key Value")
  {
    int key = -1;
    breach = range.validateTheData(validSequence,key);
    REQUIRE(breach == INVALID);
  }
  SECTION("check for Positive Key Value and then check for Sequence")
  {
    int key = 3;
    SECTION("Check for Valid Sequence with Valid Key")
    {
       breach = range.validateTheData(validSequence,key);
       REQUIRE(breach == VALID);
    }
    SECTION("Check for Invalid Sequence with Valid Key")
    {
       int key = 3;
       ::std::vector<int> inValidSequence = {2,4,3,6,-1,6,7,8,-9,3};
       breach = range.validateTheData(inValidSequence,key);
       REQUIRE(breach == INVALID);
    }
  }
}

TEST_CASE("ForTheGivenSequence_FindTheMaxAndMinValues")
{
  ::std::vector<int> validSequence = {2,4,3,6,1,6,7,8,9,3};
  Range::BoundaryValues values = range.getMaxAndMinValue(validSequence);
  REQUIRE(values.min == 1);
  REQUIRE(values.max == 9);
}

TEST_CASE("ForTheGivenSequence_FindTheValidRanges")
{
  int key = 3;
  ::std::vector<int> validSequence = {2,4,3,6,1,6,7,8,9,3};
  // prepare expectedRangeList
  Range::T_RangeList actualRangelist, expectedRangeList;
  expectedRangeList.push_back(make_pair(1,3));
  expectedRangeList.push_back(make_pair(4,6));
  expectedRangeList.push_back(make_pair(7,9));
  // get actualRangelist
  actualRangelist = range.getRanges(validSequence, key);
  SECTION("Check the size")
  {
    REQUIRE(expectedRangeList.size() == actualRangelist.size())
    SECTION("check the list")
    {
      REQUIRE(expectedRangeList == actualRangelist);
    }
  }
}

TEST_CASE("ForGivenSequenceRange_GetTheReadings")
{
  ::std::vector<int> validSequence = {2,4,3,6,1,6,7,8,9,3};
  // prepare rangelist
  Range::T_RangeList rangelist;
  rangelist.push_back(make_pair(1,3));
  rangelist.push_back(make_pair(4,6));
  rangelist.push_back(make_pair(7,9));
  Range::T_RangeBasedReadingsList expectedRangeBasedReadingsList, actualRangeBasedReadingsList;
  //prepare expectedRangeBasedReadingsList
  expectedRangeBasedReadingsList.push_back({2,1,3,1});
  expectedRangeBasedReadingsList.push_back({4,5,6,4});
  expectedRangeBasedReadingsList.push_back({7,9});
  // get actualRangeBasedReadingsList
  actualRangeBasedReadingsList = range.getTheReadings(rangelist, validSequence);
  SECTION("Check the size")
  {
    REQUIRE(expectedRangeBasedReadingsList.size() == actualRangeBasedReadingsList.size())
    SECTION("check the list")
    {
      REQUIRE(expectedRangeBasedReadingsList == actualRangeBasedReadingsList);
    }
  }
}

TEST_CASE("checkTheRangeAndReadings_ForGivenSequence_checkTheOutput")
{
  ::string expectedOutput, actualOutput;
  ::std::vector<int> validSequence = {2,4,3,6,1,6,7,8,9,3};
  SECTION("Invalid key")
  {
      int key = 0;
      expectedOutput = "-";
      actualOutput = range.checkTheRangeAndReadings(validSequence, key);
      REQUIRE(actualOutput == expectedOutput);
  }
  int key = 3;
  SECTION("Valid Key and Valid Sequence")
  {
      //prepare rangelist
      Range::T_RangeList rangelist;
      rangelist.push_back(make_pair(1,3));
      rangelist.push_back(make_pair(4,6));
      rangelist.push_back(make_pair(7,9));
    
    //prepare rangeBasedReadingsList
      Range::T_RangeBasedReadingsList rangeBasedReadingsList;
      rangeBasedReadingsList.push_back({2,1,3,1});
      rangeBasedReadingsList.push_back({4,5,6,4});
      rangeBasedReadingsList.push_back({7,9});
    
    //prepare expected output
      char delimiter = ',';
      char separator = '-';
      expectedOutput.append("RANGE");
      expectedOutput = output+delimiter;
      expectedOutput.append("READINGS");
      expectedOutput.append("\n");
      for(size_t i = 0; i<rangelist.size();++i)
      {
        expectedOutput.append(std::to_string(rangelist[i].first));
        expectedOutput = expectedOutput + separator;
        expectedOutput.append(std::to_string(rangelist[i].second));
        expectedOutput = output+delimiter;
        expectedOutput.append(std::to_string(rangeBasedReadingsList[i].size()));
        expectedOutput.append("\n");
      }
    
    // get the actual output
      actualOutput = range.checkTheRangeAndReadings(validSequence, key);
      REQUIRE(actualOutput == expectedOutput);
  }
  SECTION("Valid key and Invalid Sequence")
  {
     ::std::vector<int> inValidSequence = {2,4,3,6,1,6,7,-8,9,3};
      expectedOutput = "-";
        // get the actual output
      actualOutput = range.checkTheRangeAndReadings(inValidSequence, key);
      REQUIRE(actualOutput == expectedOutput);
  }   
}
