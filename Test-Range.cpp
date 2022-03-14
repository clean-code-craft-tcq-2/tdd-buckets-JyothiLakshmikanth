#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"

#include <vector>
#include <map>
#include <string>
#define private public
#include "Range.h"

using namespace std;
Range range;
TEST_CASE("OnCheckRange_CheckForOutput_FordifferentKeyValue")
{
  int key = 3;
  ::std::vector<int> input = {2,4,3,6,1,6,7,8,9,3};
  ::std::vector<::std::vector<int>> actualOutput,expectedOutput;
  actualOutput = range.checkRange(input,key);

  expectedOutput.push_back({2,3,1,3});
  expectedOutput.push_back({4,6,6});
  expectedOutput.push_back({7,8,9});

  SECTION("Check for the size of maps")
  {
    REQUIRE(expectedOutput.size() == actualOutput.size());
  }
  SECTION("compare entries in rangeMap and expectedMap")
  {
    REQUIRE(actualOutput == expectedOutput);
  }
}
