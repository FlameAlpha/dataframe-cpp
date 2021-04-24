# dataframe-cpp
dataframe class for c++ language
- read from csv file
- write into csv file and lib_svm file
- min max scaler and standard scaler for each column's data
- append one row from std::vector<T> & remove row
- insert one column from std::vector<T> & remove column
- get a row of data  by index of the row 
- get a column of data  by string of the column 
- concat & add double dataFrame object (horizontally & vertically) 
- support single variable with multiple types, including char, int, long int, float, double, std::string


**Build requirements:** c++ 11 to 17

## Quick start

```cpp
#include "dataframe.hpp"

int main() {
    using namespace flame;
    // create an empty dataframe object
    dataframe d1;

    // recreate a dataframe object from csv file or another
    d1.read_csv("../test"); // d1 = std::move(dataframe<double>("../test.txt"));

    // create a dataframe object from csv file
    dataframe d2("../test");

    // concat double dataframe object vertically
    auto d3 = d1 + d2;

    // insert one column from std::vector<T>
    /* Note: only the column will be added automatically when name string of its is not detected.
    This feature does not exist for rows */
    d3["h"] = d3["f"] = d3["g"] = {6, 7, 8, 9};

    // remove one column by str
    std::cout << ((d3.remove("g") ? "successfully" : "unsuccessfully") + std::string(" deleted a colunm!"))
              << std::endl;

    // append one row from std::vector<T>
    d3.append(std::vector<user_variant>(d3.column_num()));

    // change data in ith row
    d3[4] = {6, 7, 8, 9, 10};

    // concat double dataframe object horizontally
    d3.concat_row(d3);

    // change one item
    d3["f"][3] = 2;

    // insert std::vector<T> into dataframe directly
    d3.insert("i", {6.6f, '7', 8, "hello", 10});

    // remove one row by index
    std::cout << ((d3.remove(2) ? "successfully" : "unsuccessfully") + std::string(" deleted a row!")) << std::endl;

    // print dataframe
    std::cout << d3;

    // min_max_scaler<double> scaler(d3); // min max scaler
    toolbox::standard_scaler scaler(d3); // standard scaler

    // save scaler into file
    scaler.save_scaler("../scaler");

    // load scaler from file
    scaler.load_scaler("../scaler");

    // transform dataset
    scaler.transform(d3);

    std::cout << "after scaler : " << std::endl << d3;

    // write into csv file
    d3.to_csv("../final", ',');

    return 0;
}
```