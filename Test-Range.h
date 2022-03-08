#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"

#include <vector>
#include <map>
#include <string>
#define private public
#include "Range.h"

using namespace std;

TEST_CASE("OnCheckRange_CheckForOutput_FordifferentKeyValue")
{
  int key = 3;
  ::std::vector<int> input = {2,4,3,6,1,6,7,8,9,3};
  ::std::map<string, int> rangeMap, expectedMap;
  rangeMap = checkRange(input,key);
//   prepareExpectedMap(expectedMap, input,key);
  expectedMap["1-3"] = 4;
  expectedMap["4-6"] = 3;
  expectedMap["7-9"] = 3;
  SECTION("Check for the size of maps")
  {
    REQUIRE(rangeMap.size() == expectedMap.size());
  }
  SECTION("compare entries in rangeMap and expectedMap")
  {
    for(int i = 0; i<expectedMap.size() ; ++i)
    {
        REQUIRE(rangeMap[i] == expectedMap[i]);
    }
  }
}
