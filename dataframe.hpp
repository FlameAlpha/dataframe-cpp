/**
 * @file     dataframe.h
 * @class    dataframe
 * @brief    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *           read from csv file
 *           write into csv file
 *           append one row from std::vector & remove row
 *           insert one column from std::vector & remove column
 *           get a row of data by index of the row
 *           get a column of data by string of the column
 *           concat & add double dataFrame object (horizontally & vertically)
 *           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @details
 * @author   Flame
 * @date     10.01.2020
**/

#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <sstream>
#include <unordered_map>

template<typename T = double>
class dataframe {
public:
    class column_array {
        typedef typename std::vector<T>::const_iterator iter;
        std::vector<T> *array = nullptr;
    public:
        explicit column_array(int n = 0) {
            array = new std::vector<T>(n);
        }

        column_array(const column_array &_array) {
            array = new std::vector<T>(*_array.array);
        }

        column_array(column_array &&_array) noexcept {
            array = new std::vector<T>(std::move(*_array.array));
        }

        explicit column_array(std::vector<T> &&_array) {
            array = new std::vector<T>(_array);
        }

        explicit column_array(const std::vector<T> &_array) {
            array = new std::vector<T>(_array);
        }

        ~column_array() {
            delete array;
        }

        void insert(iter position, iter start, iter end) {
            array->insert(position, start, end);
        }

        [[nodiscard]] unsigned long long int size() const {
            if (array == nullptr)
                return 0;
            return array->size();
        }

        [[nodiscard]] iter begin() const {
            return array->begin();
        }

        [[nodiscard]] iter end() const {
            return array->end();
        }

        void erase(iter i) {
            array->erase(i);
        }

        void emplace_back(const T &item) {
            array->emplace_back(item);
        }

        column_array &operator=(const column_array &_array) {
            if (_array.size() == array->size()) {
                array->clear();
                array->insert(array->begin(), _array.begin(), _array.end());
                return *this;
            }
            throw (std::invalid_argument("The length of the two is not the same"));
        }

        column_array &operator=(const std::vector<T> &_array) {
            if (_array.size() == array->size()) {
                array->clear();
                array->insert(array->begin(), _array.begin(), _array.end());
                return *this;
            }
            throw (std::invalid_argument("The length of the two is not the same"));
        }

        column_array &operator=(std::vector<T> &&_array) {
            if (_array.size() == array->size()) {
                *array = _array;
                return *this;
            }
            throw (std::invalid_argument("The length of the two is not the same"));
        }

        const std::vector<T> & get_std_vector(){
            return *array;
        }

        const T &operator[](unsigned long long int i) const {
            if (i < array->size())
                return (*array)[i];
            else {
                std::stringstream ssTemp;
                ssTemp << i;
                throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
            }
        }

        T &operator[](unsigned long long int i) {
            if (i < array->size())
                return (*array)[i];
            else {
                std::stringstream ssTemp;
                ssTemp << i;
                throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
            }
        }

        friend std::ostream &operator<<(std::ostream &cout, column_array &arr) {
            for (const auto &item : *arr.array) {
                cout << item << ' ';
            }
            return cout;
        }
    };

    class row_array {
        typedef typename std::vector<T *>::const_iterator iter;
        std::vector<T *> *array = nullptr;
    public:
        explicit row_array(int n = 0) {
            array = new std::vector<T *>(n);
        }

        row_array(const row_array &_array) {
            array = new std::vector<T *>(*_array.array);
        }

        row_array(row_array &&_array) noexcept {
            array = new std::vector<T *>(std::move(*_array.array));
        }

        explicit row_array(std::vector<T *> &&_array) {
            array = new std::vector<T *>(_array);
        }

        explicit row_array(const std::vector<T *> &_array) {
            array = new std::vector<T *>(_array);
        }

        ~row_array() {
            delete array;
        }

        void insert(iter position, iter start, iter end) {
            array->insert(position, start, end);
        }

        [[nodiscard]] unsigned long long int size() const {
            if (array == nullptr)
                return 0;
            return array->size();
        }

        [[nodiscard]] iter begin() const {
            return array->begin();
        }

        [[nodiscard]] iter end() const {
            return array->end();
        }

        row_array &operator=(const row_array &_array) {
            if (_array.size() == array->size()) {
                for (int i = 0; i < _array.size(); ++i) {
                    *(*array)[i] = _array[i];
                }
                return *this;
            }
            throw (std::invalid_argument("The length of the two is not the same"));
        }

        row_array &operator=(const std::vector<T> &_array) {
            if (_array.size() == array->size()) {
                for (int i = 0; i < _array.size(); ++i) {
                    *(*array)[i] = _array[i];
                }
                return *this;
            }
            throw (std::invalid_argument("The length of the two is not the same"));
        }

        row_array &operator=(std::vector<T> &&_array) {
            if (_array.size() == array->size()) {
                for (int i = 0; i < _array.size(); ++i) {
                    *(*array)[i] = _array[i];
                }
                return *this;
            }
            throw (std::invalid_argument("The length of the two is not the same"));
        }

        void push_back(T *item) {
            array->emplace_back(item);
        }

        const T &operator[](unsigned long long int i) const {
            if (i < array->size())
                return *((*array)[i]);
            else {
                std::stringstream ssTemp;
                ssTemp << i;
                throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
            }
        }

        T &operator[](unsigned long long int i) {
            if (i < array->size())
                return *((*array)[i]);
            else {
                std::stringstream ssTemp;
                ssTemp << i;
                throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
            }
        }

        friend std::ostream &operator<<(std::ostream &cout, row_array &arr) {
            for (const auto &item : *arr.array) {
                cout << item << ' ';
            }
            return cout;
        }
    };

private:
    typedef std::vector<std::string> string_vector;

public:
    // constructed by file name
    explicit dataframe(const std::string &filename, const char &delimiter = ',') : width(0), length(0) {
        read_csv(filename, delimiter);
    }

    // constructed by width and length
    explicit dataframe(long long int _width = 0, long long int _length = 0) : width(_width), length(_length) {
        string_vector temp;
        for (int i = 0; i < width; i++)
            temp.emplace_back(std::to_string(i));
        column_paste(temp);
    }

    // constructed by string vector
    explicit dataframe(const string_vector &columns) : width(columns.size()), length(0) {
        column_paste(columns);
    }

    // copy constructor
    dataframe(const dataframe &dataframe) :
            width(dataframe.width),
            length(dataframe.length),
            column(dataframe.column),
            index(dataframe.index) {
        matrix.clear();
        for (auto i = dataframe.matrix.begin(); i < dataframe.matrix.end(); ++i) {
            matrix.emplace_back(new column_array(**i));
        }
    }

    // move constructor
    dataframe(dataframe &&dataframe) noexcept :
            width(dataframe.width),
            length(dataframe.length),
            column(std::move(dataframe.column)),
            index(std::move(dataframe.index)) {
        matrix.clear();
        for (auto i = dataframe.matrix.begin(); i < dataframe.matrix.end(); ++i) {
            matrix.emplace_back(new column_array(std::move(**i)));
        }
    }

    ~dataframe() {
        for (auto i = 0; i < matrix.size(); ++i) {
            delete matrix[i];
        }
    }

    // determine whether the column is included
    bool contain(const std::string &col) {
        return index.find(col) != index.end();
    }

    // insert one column
    bool insert(const std::string &col) {
        ++width;
        column.emplace_back(col);
        index.emplace(col, index.size());
        matrix.emplace_back(new column_array(length));
        return true;
    }

    // insert one column from std::vector<T>
    bool insert(const std::string &col, column_array &&array) {
        if (array.size() == row_num()) {
            if (!contain(col)) {
                ++width;
                column.emplace_back(col);
                index.emplace(col, index.size());
                matrix.emplace_back(new column_array(array));
            } else {
                column_array &line = this->operator[](col);
                if (line.size() == array.size()) {
                    line = array;
                } else throw (std::invalid_argument("The length of the two is not the same"));
            }
            return true;
        } else return false;
    }

    // insert one column from std::vector<T>
    bool insert(const std::string &col, const column_array &array) {
        if (array.size() == row_num()) {
            if (!contain(col)) {
                ++width;
                column.emplace_back(col);
                index.emplace(col, index.size());
                matrix.emplace_back(new column_array(array));
            } else {
                column_array &line = this->operator[](col);
                if (line.size() == array.size()) {
                    line = array;
                } else throw (std::invalid_argument("The length of the two is not the same"));
            }
            return true;
        } else return false;
    }

    // insert one column from std::vector<T>
    bool insert(const std::string &col, std::vector<T> &&array) {
        if (array.size() == row_num()) {
            if (!contain(col)) {
                ++width;
                column.emplace_back(col);
                index.emplace(col, index.size());
                matrix.emplace_back(new column_array(array));
            } else {
                column_array &line = this->operator[](col);
                if (line.size() == array.size()) {
                    line = array;
                } else throw (std::invalid_argument("The length of the two is not the same"));
            }
            return true;
        } else return false;
    }

    // insert one column from std::vector<T>
    bool insert(const std::string &col, const std::vector<T> &array) {
        if (array.size() == row_num()) {
            if (!contain(col)) {
                ++width;
                column.emplace_back(col);
                index.emplace(col, index.size());
                matrix.emplace_back(new column_array(array));
            } else {
                column_array &line = this->operator[](col);
                if (line.size() == array.size()) {
                    line = array;
                } else throw (std::invalid_argument("The length of the two is not the same"));
            }
            return true;
        } else return false;
    }

    //remove one column from str
    bool remove(const std::string &col) {
        auto item = index.find(col);
        if (item != index.end()) {
            --width;
            column.erase(column.begin() + item->second);
            delete *(matrix.begin() + item->second);
            matrix.erase(matrix.begin() + item->second);
            for (auto &index_item : index) {
                if (index_item.second > item->second) {
                    index_item.second--;
                }
            }
            index.erase(item);
            return true;
        }
        return false;
    }

    //remove one row from index
    bool remove(int i) {
        if (i < length) {
            for (auto &item : matrix) {
                item->erase(item->begin() + i);
            }
            --length;
            return true;
        } else {
            return false;
        }
    }

    //get one row data from index of row
    row_array operator[](int i) {
        if (i < length) {
            row_array row_array;
            for (auto &item : matrix) {
                row_array.push_back(&((*item)[i]));
            }
            return std::move(row_array);
        } else {
            std::stringstream ssTemp;
            ssTemp << i;
            throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
        }
    }

    //get one row data from index of row
    const row_array &operator[](int i) const {
        if (i < length) {
            row_array row_array;
            for (auto &item : matrix) {
                row_array.push_back(&((*item)[i]));
            }
            return std::move(row_array);
        } else {
            std::stringstream ssTemp;
            ssTemp << i;
            throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
        }
    }

    //get one column data from column str
    column_array &operator[](const std::string &col) {
        auto item = index.find(col);
        if (item != index.end()) {
            return *(matrix[item->second]);
        }
        insert(col);
        return *(matrix.back());
    }

    //get one column data from column str
    const column_array &operator[](const std::string &col) const {
        auto item = index.find(col);
        if (item != index.end()) {
            return *(matrix[item->second]);
        }
        insert(col);
        return *(matrix.back());
    }

    //append one row from std::vector<T>
    bool append(const std::vector<T> &array) {
        if (array.size() == width) {
            length++;
            for (int i = 0; i < array.size(); ++i) {
                matrix[i]->emplace_back(array[i]);
            }
            return true;
        } else return false;
    }

    //append one row from std::vector<T>
    bool append(std::vector<T> &&array) {
        if (array.size() == width) {
            length++;
            for (int i = 0; i < array.size(); ++i) {
                matrix[i]->emplace_back(std::move(array[i]));
            }
            return true;
        } else return false;
    }

    [[nodiscard]] const long long int &column_num() const {
        return width;
    }

    [[nodiscard]] const long long int &row_num() const {
        return length;
    }

    //concat double dataframe object vertically
    bool concat_line(const dataframe &dataframe) {
        if (dataframe.width == width) {
            length += dataframe.length;
            for (int i = 0; i < width; ++i) {
                matrix[i]->insert(matrix[i]->end(), dataframe.get_column(i).begin(), dataframe.get_column(i).end());
            }
            return true;
        } else return false;
    }

    //concat double dataframe object horizontally
    bool concat_row(const dataframe &dataframe) {
        if (dataframe.length == length) {
            std::string repeat;
            auto last_width = dataframe.width;
            for (int i = 0; i < last_width; ++i) {
                repeat = contain(dataframe.column[i]) ? "_r" : "";
                index.insert({dataframe.column[i] + repeat, index.size()});
                column.emplace_back(dataframe.column[i] + repeat);
                matrix.emplace_back(new column_array(*dataframe.matrix[i]));
            }
            width += dataframe.column_num();
            return true;
        } else return false;
    }

    //concat double dataframe object horizontally
    bool concat_row(dataframe &&dataframe) {
        if (dataframe.length == length) {
            std::string repeat;
            auto last_width = dataframe.width;
            for (int i = 0; i < last_width; ++i) {
                repeat = contain(dataframe.column[i]) ? "_r" : "";
                index.insert({dataframe.column[i] + repeat, index.size()});
                column.emplace_back(dataframe.column[i] + repeat);
                matrix.emplace_back(new column_array(std::move(*dataframe.matrix[i])));
            }
            width += dataframe.column_num();
            return true;
        } else return false;
    }

    // is empty or not
    bool empty() const {
        return width == 0;
    }

    //concat double dataframe object vertically
    friend dataframe operator+(const dataframe &dataframe1, const dataframe &dataframe2) {
        if (!dataframe1.empty() && !dataframe2.empty() &&
            dataframe1.column_num() == dataframe2.column_num()) {
            dataframe dataFrame(dataframe1.column);
            dataFrame.concat_line(dataframe1);
            dataFrame.concat_line(dataframe2);
            return std::move(dataFrame);
        } else throw (std::invalid_argument("The column length of the two is not the same"));
    }

    // move by equal sign
    dataframe &operator=(dataframe &&dataframe) noexcept {
        clear();
        width = dataframe.width;
        length = dataframe.length;
        column = std::move(dataframe.column);
        index = std::move(dataframe.index);
        matrix.clear();
        for (auto i = dataframe.matrix.begin(); i < dataframe.matrix.end(); ++i) {
            matrix.emplace_back(new column_array(std::move(**i)));
        }
        return *this;
    }

    // copy by equal sign
    dataframe &operator=(const dataframe &dataframe) {
        clear();
        width = dataframe.width;
        length = dataframe.length;
        column = dataframe.column;
        index = dataframe.index;
        matrix.clear();
        for (auto i = dataframe.matrix.begin(); i < dataframe.matrix.end(); ++i) {
            matrix.emplace_back(new column_array(**i));
        }
        return *this;
    }

    //read from csv file
    void read_csv(const std::string &filename, const char &delimiter = ',') {
        clear();
        std::ifstream reader(filename.data());
        if (!reader) {
            throw (std::invalid_argument(filename + " is invalid!"));
        }

        std::string str_line;
        string_vector value_str_vector;
        if (getline(reader, str_line)) {
            value_str_vector.clear();
            if (splite_line(str_line, value_str_vector, delimiter)) {
                column_paste(value_str_vector);
            }
        }

        while (getline(reader, str_line)) {
            value_str_vector.clear();
            if (splite_line(str_line, value_str_vector, delimiter)) {
                append_from_str(value_str_vector);
            }
        }
        reader.close();
    }

    //write into csv file
    void to_csv(const std::string &filename, const char &delimiter = ',') const {
        std::ofstream cout = std::ofstream(filename.data(), std::ios::out | std::ios::trunc);
        for (auto item = column.begin(); item < column.end() - 1; ++item) {
            cout << *item << delimiter;
        }
        cout << column.back() << '\n';
        for (int i = 0; i < row_num(); ++i) {
            for (auto array = matrix.begin(); array < matrix.end() - 1; ++array) {
                cout << (**array)[i] << delimiter;
            }
            cout << (*matrix.back())[i] << '\n';
        }
        cout.close();
    }

    //print dataframe
    friend std::ostream &operator<<(std::ostream &cout, const dataframe &dataframe) {
        cout << "width : " << dataframe.width << std::endl;
        cout << "length : " << dataframe.length << std::endl;
        for (int j = 0; j < dataframe.width; ++j) {
            cout << dataframe.column[j] << "\t";
        }
        cout << '\n';
        for (int i = 0; i < dataframe.length; ++i) {
            for (int j = 0; j < dataframe.width; ++j) {
                cout << (*dataframe.matrix[j])[i] << "\t";
            }
            cout << '\n';
        }
        return cout;
    }

    // get name vector of columns
    const std::vector<std::string> &get_column_str() {
        return column;
    }

private:
    // clear all data, generate an empty dataframe
    void clear() {
        length = 0;
        width = 0;
        for (auto i = 0; i < matrix.size(); ++i) {
            delete matrix[i];
        }
        matrix.clear();
        column.clear();
        index.clear();
    }

    //init the column
    bool column_paste(const string_vector &_column) {
        if (!_column.empty()) {
            width = _column.size();
            column.clear();
            index.clear();
            matrix.clear();
            for (const auto &item : _column) {
                column.emplace_back(item);
                index.emplace(item, index.size());
                matrix.emplace_back(new column_array(0));
            }
            return true;
        } else return false;
    }

    // print name of column
    void show_columns() {
        for (const auto &item : index) {
            std::cout << item.first << ',' << item.second << std::endl;
        }
    }

    //get one column data from index of column
    const column_array &get_column(const int &i) const {
        if (i < matrix.size())
            return *(matrix[i]);
        std::stringstream ssTemp;
        ssTemp << i;
        throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
    }

    //get one column data from index of column
    column_array &get_column(const int &i) {
        if (i < matrix.size())
            return *(matrix[i]);
        std::stringstream ssTemp;
        ssTemp << i;
        throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
    }

    //get one row data from index of row
    row_array get_row(int i) {
        if (i < length) {
            row_array row_array;
            for (auto &item : matrix) {
                row_array.push_back(&((*item)[i]));
            }
            return std::move(row_array);
        } else {
            std::stringstream ssTemp;
            ssTemp << i;
            throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
        }
    }

    //get one row data from index of row
    const row_array &get_row(int i) const {
        if (i < length) {
            row_array row_array;
            for (auto &item : matrix) {
                row_array.push_back(&((*item)[i]));
            }
            return std::move(row_array);
        } else {
            std::stringstream ssTemp;
            ssTemp << i;
            throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
        }
    }

    // separate strings by delimiter
    bool splite_line(const std::string &str_line, string_vector &value_str_vector, const char &delimiter) {
        unsigned long long begin_iter = 0;
        unsigned long long end_iter = 0;
        bool flag = false;
        std::string str_temp;
        while ((end_iter = str_line.find_first_of(delimiter, begin_iter)) != std::string::npos) {
            str_temp = str_line.substr(begin_iter, end_iter - begin_iter);
            value_str_vector.emplace_back(str_temp);
            begin_iter = end_iter + 1;
        }
        if ((begin_iter = str_line.find_last_of(delimiter, str_line.length() - 1)) != std::string::npos) {
            str_temp = str_line.substr(begin_iter + 1, str_line.length() - begin_iter - 1);
            value_str_vector.emplace_back(str_temp);
            flag = true;
        }
        return flag;
    }

    // append data from string vector
    bool append_from_str(const string_vector &value_str_vector) {
        if (value_str_vector.size() == column.size()) {
            length++;
            std::stringstream stream;
            T item;
            for (unsigned int i = 0; i < value_str_vector.size(); ++i) {
                stream.clear();
                stream << value_str_vector[i];
                stream >> item;
                matrix[i]->emplace_back(item);
            }
            return true;
        } else return false;
    }

    std::vector<std::string> column;
    std::vector<column_array *> matrix;
    long long int width;
    long long int length;
    std::unordered_map<std::string, unsigned long long int> index;
};

#endif // DATAFRAME_H
