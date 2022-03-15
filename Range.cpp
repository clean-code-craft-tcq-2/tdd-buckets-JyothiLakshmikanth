#include "Range.h"
 using namespace std;

::string Range::checkTheRangeAndReadings(::std::vector<int> sequence, int key)
{
     ::string outputCSVFormat = "-";
    Range::BreachType breachType = validateTheData(sequence, key);
    if(breachType == Range::VALID)
    {
        breachType = Range::VALID;
        Range::BoundaryValues values = getMaxAndMinValue(sequence);
        Range::T_RangeList range = getRanges(values, key);
        Range::T_RangeBasedReadingsList readingsList = getTheReadings(range, sequence);
        outputCSVFormat = prepareOutputInCSVFormat( range, readingsList);
    }

 return outputCSVFormat;
}

Range::BoundaryValues Range::getMaxAndMinValue(::vector<int> input)
{
 Range::BoundaryValues boundaryValues;
    boundaryValues.max =  *max_element(input.begin(), input.end());
    boundaryValues.min =  *min_element(input.begin(), input.end());
 return boundaryValues;
}

::string Range::prepareOutputInCSVFormat(Range::T_RangeList range, Range::T_RangeBasedReadingsList readingsList)
{
  ::string outputCSVFormat;
    char delimiter = ',';
    char separator = '-';
    outputCSVFormat.append("RANGE");
    outputCSVFormat = outputCSVFormat+delimiter;
    outputCSVFormat.append("READINGS");
    outputCSVFormat.append("\n");
    for(int i = 0; i<range.size();++i)
    {
        outputCSVFormat.append(std::to_string(range[i].first));
        outputCSVFormat = outputCSVFormat + separator;
        outputCSVFormat.append(std::to_string(range[i].second));
        outputCSVFormat = outputCSVFormat+delimiter;
        outputCSVFormat.append(std::to_string(readingsList[i].size()));
        outputCSVFormat.append("\n");
    }
  return outputCSVFormat;
}

Range::T_RangeBasedReadingsList Range::getTheReadings(Range::T_RangeList range, ::vector<int> sequence)
{
 Range::T_RangeBasedReadingsList rangeBasedReadingsList;
    for(size_t i = 0; i < range.size(); ++i)
    {
        ::vector<int> readingList;
//         cout << range[i].first << "\t" << range[i].second << endl;
        ::vector<int>::const_iterator sequenceIt = sequence.begin();
        for(; sequenceIt != sequence.end(); ++sequenceIt)
        {
            if(*sequenceIt >= range[i].first && *sequenceIt <= range[i].second)
            {
                readingList.push_back(*sequenceIt);
            }
        }
        rangeBasedReadingsList.push_back(readingList);
    }
//     for (size_t i = 0; i < rangeListReadings.size(); i++)
//     {
//         ::cout<<"rangeListReadings["<<i<<"] size - "<<rangeListReadings[i].size()<<endl;
//         for(size_t j=0;j<rangeListReadings[i].size();j++)
//         {
//             cout << "rangeListReadings["<<i<<"]"<<rangeListReadings[i][j]<< endl;
//         }
//     }

 return rangeBasedReadingsList;
}

Range::T_RangeList Range::getRanges(Range::BoundaryValues values, int key)
{
 Range::T_RangeList rangList;
    
//     ::cout<<"min - "<<values.min<< "\t" <<"max - "<<values.max<< "\t" <<"key - "<<key<<endl;
    for (size_t i = values.min; i < values.max; )
    {
        rangList.push_back(make_pair(i,i+key-1));
        i=i+key;
    }
  //  ::std::cout<<"result size - "<<rangList.size()<<endl;
 return rangList;
}

Range::BreachType Range::validateTheData(::vector<int> sequence, int key)
{
    Range::BreachType breachType = VALID;
    if(key < 0)
    {
        breach = INVALID;
    }
    for(::vector<int>::const_iterator sequenceIt = sequence.begin(); sequenceIt!=sequence.end(); ++sequenceIt)
    {
        if(*sequenceIt<0)
        {
            breach = INVALID;
            break;
        }
    }
    return breach;
}
