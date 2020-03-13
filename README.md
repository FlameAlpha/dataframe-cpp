# dataframe-cxx
dataframe class for c++ language
- read from csv file
- write into csv file
- append one row from std::vector<T>
- get one column data by string of the column 
- insert one column from std::vector<T> & remove column
- concat & add double DataFrame object (horizontally & vertically) 


**Build requirements:** c++ 11^+^ 

## Quick start

```cpp
#include <iostream>
#include <vector>
#include <string>
#include "dataframe.hpp"

int main() {
    
    DataFrame<int> d1;
    DataFrame<int> d2;

    //read from csv file
    d1.read_csv("../test.txt",',');
    d2.read_csv("../test.txt",',');
    //concat double DataFrame object vertically
    auto d3 = d1 + d2;
    // insert one column from std::vector<T>
    d3["h"] = d3["f"]  = d3["g"] = std::vector<int>{6,7,8,9};
    // change data
    d3["f"][3] = 2;
    //remove one column by str
    d3.remove("g");
    //append one row from std::vector<T>
    d3.append(std::vector<int>(d3.column_num()));
    //concat double DataFrame object horizontally
    d3.concat_row(d3);
    //print dataframe
    std::cout << d3;
    //write into csv file
    d3.to_csv("../final.txt",',');
    return 0;
}
```
