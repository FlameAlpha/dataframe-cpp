# dataframe-cpp
dataframe class for c++ language
- read from csv file
- write into csv file
- append one row from std::vector<T> & remove row
- insert one column from std::vector<T> & remove column
- get a row of data  by index of the row 
- get a column of data  by string of the column 
- concat & add double dataFrame object (horizontally & vertically) 


**Build requirements:** c++ 11 to 17

## Quick start

```cpp
#include "dataframe.hpp"

int main() {
    // create a dataframe object from csv file
    dataframe<double> d1("../test.txt");
    dataframe<double> d2("../test.txt");

    // concat double dataframe object vertically
    auto d3 = d1 + d2;

    // insert one column from std::vector<T>
    /* Note: only the column will be added automatically when name string of its is not detected.
    This feature does not exist for rows */
    d3["h"] = d3["f"]  = d3["g"] = std::vector<double>{6,7,8,9};

    // remove one column by str
    std::cout << ((d3.remove("g") ? "successfully": "unsuccessfully") + std::string(" deleted a colunm!")) << std::endl;

    // append one row from std::vector<T>
    d3.append(std::vector<double>(d3.column_num()));

    // change data in ith row
    d3[4] = std::vector<double>{6,7,8,9,10};

    // concat double dataframe object horizontally
    d3.concat_row(d3);

    // change one item
    d3["f"][3] = 2;

    // insert std::vector<T> into dataframe directly
    d3.insert("i",std::vector<double>{6,7,8,9,10});

    // remove one row by index
    std::cout << ((d3.remove(2) ? "successfully": "unsuccessfully") + std::string(" deleted a row!")) << std::endl;

    // print dataframe
    std::cout << d3;

    // write into csv file
    d3.to_csv("../final.txt",',');
    return 0;
}
```
