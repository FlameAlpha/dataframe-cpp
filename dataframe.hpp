/**
 * @file     DataFrame.h
 * @class    DataFrame
 * @brief    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *           read from csv file
 *           write to csv file
 *           append one row from std::vector<T>
 *           concat & add double DataFrame object (horizontally & vertically)
 *           insert one column from std::vector<T> & remove column
 *           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @details
 * @author   Flame
 * @date     03.13.2019
**/

#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <exception>
#include <sstream>

template <typename T = double>
class DataFrame
{
    class Array
    {
        typedef typename std::vector<T>::const_iterator iter;
        std::vector<T> * array = nullptr;
    public:
        explicit Array(int n = 0){
            array = new std::vector<T>(n);
        }

        Array (const Array & _array){
            array = new std::vector<T>(_array.size());
            if(_array.size()==array->size()){
                array->clear();
                array->insert(array->begin(),_array.begin(),_array.end());
            }
        }

        explicit Array (const Array * _array){
            if(array != nullptr)
                delete array;
            array = new std::vector<T>(_array->size());
            if(_array->size()==array->size()){
                array->clear();
                array->insert(array->begin(),_array->begin(),_array->end());
            }
        }

        ~Array(){
            delete array;
        }

        void insert(iter position,iter start,iter end){
            array->insert(position,start,end);
        }

        [[nodiscard]] unsigned long long int size() const{
            if(array == nullptr)
                return 0;
            return array->size();
        }

        [[nodiscard]] typename std::vector<T>::const_iterator begin() const{
            return array->begin();
        }

        [[nodiscard]] typename std::vector<T>::const_iterator end() const{
            return array->end();
        }

        void emplace_back(const T & item){
            array->emplace_back(item);
        }

        Array & operator = (const Array & _array){
            if(_array.size()==array->size()){
                array->clear();
                array->insert(array->begin(),_array.begin(),_array.end());
            }
            return *this;
        }

        Array & operator = (const std::vector<T> & _array){
            if(_array.size()==array->size()){
                array->clear();
                array->insert(array->begin(),_array.begin(),_array.end());
            }
            return *this;
        }

        const T & operator [](unsigned long long int index) const {
            if( index < array->size())
                return (*array)[index];
            else{
                std::stringstream ssTemp;
                ssTemp << index;
                throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
            }
        }

        T & operator [](unsigned long long int index) {
            if(index < array->size())
                return (*array)[index];
            else{
                std::stringstream ssTemp;
                ssTemp << index;
                throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
            }
        }
    };

    typedef std::vector<Array *> Matrix;
    typedef std::vector<std::string> Column;
    typedef std::vector<std::string> StringVector;
public:
    DataFrame(){
        width = 0;
        length = 0;
    }

    DataFrame(const DataFrame & dataframe){
        width = dataframe.width;
        length = dataframe.length;
        column.insert(column.begin(),dataframe.column.begin(),dataframe.column.end());
        for (auto i = dataframe.matrix.begin(); i < dataframe.matrix.end(); ++i) {
            matrix.emplace_back(new Array(*i));
        }
    }

    ~DataFrame(){
        for(auto i = 0; i < matrix.size(); ++ i){
            delete matrix[i];
        }
    }

    //init the column
    bool column_paste(const Column & _column){
        if(!_column.empty()) {
            width = _column.size();
            column.clear();
            for(auto item : _column){
                column.emplace_back(item);
                matrix.emplace_back(new Array(0));
            }
            return true;
        } else return false;
    }

    bool contain(const std::string & col){
        for(int i = 0;i<column.size();i++){
            if(col==column[i]){
                return true;
            }
        }
        return false;
    }

    // insert one column
    bool insert(const std::string & col){
        ++ width;
        column.emplace_back(col);
        matrix.emplace_back(new Array(length));
        return true;
    }

    // insert one column from std::vector<T>
    bool insert(const std::string & col,const Array & array){
        if(array.size() == row_num()){
            if(!contain(col)){
                ++ width;
                column.emplace_back(col);
                matrix.emplace_back(new Array(array));
            }else{
                Array & row = this->operator[](col);
                row.insert(row.begin(),array.begin(),array.end());
            }
            return true;
        }else return false;
    }

    //remove one column from str
    bool remove(const std::string & col){
        for(int i = 0;i<column.size();i++){
            if(col==column[i]){
                -- width;
                column.erase(column.begin()+i);
                delete *(matrix.begin()+i);
                matrix.erase(matrix.begin()+i);
                return true;
            }
        }
        return false;
    }

    //get one column data from column str
    Array & operator [](const std::string & col){
        for(int i = 0;i<column.size();i++){
            if(col==column[i]){
                return *(matrix[i]);
            }
        }
        insert(col);
        return *(matrix.back());
    }

    //get one column data from index of column
    Array & operator [](const int & index){
        if(index < matrix.size())
            return *(matrix[index]);
        std::stringstream ssTemp;
        ssTemp << index;
        throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
    }

    //append one row from std::vector<T>
    bool append(Array array){
        if(array.size() == column.size()){
            length ++;
            for (int i = 0; i < array.size(); ++i) {
                matrix[i]->emplace_back(array[i]);
            }
            return true;
        }else return false;
    }

    bool append(const std::vector<T> & array){
        if(array.size() == width){
            length ++;
            for (int i = 0; i < array.size(); ++i) {
                matrix[i]->emplace_back(array[i]);
            }
            return true;
        }else return false;
    }

    [[nodiscard]] const long long int & column_num() const {
        return width;
    }

    [[nodiscard]] const long long int & row_num() const {
        return length;
    }

    //concat double DataFrame object vertically
    bool concat_line(DataFrame & dataframe){
        if(dataframe.width==width){
            length += dataframe.length;
            for (int i = 0; i < width; ++i) {
                matrix[i]->insert(matrix[i]->end(),dataframe[i].begin(),dataframe[i].end());
            }
            return true;
        }else return false;
    }

    //concat double DataFrame object horizontally
    bool concat_row(DataFrame & dataframe){
        if(dataframe.length==length){
            width += dataframe.column_num();
            std::string repeat = "";
            for (int i = 0; i < dataframe.width; ++i) {
                repeat = contain(dataframe.column[i]) ? "_1" : "";
                column.emplace_back(dataframe.column[i] + repeat);
                matrix.emplace_back(new Array(dataframe.matrix[i]));
            }
            return true;
        }else return false;
    }

    // is empty or not
    bool empty(){
        return width == 0;
    }

    //concat double DataFrame object vertically
    friend DataFrame operator + (DataFrame & dataframe1,DataFrame & dataframe2){
        DataFrame dataFrame;
        if(!dataframe1.empty() && !dataframe2.empty() &&
        dataframe1.column_num() == dataframe2.column_num()){
            dataFrame.column_paste(dataframe1.column);
            dataFrame.concat_line(dataframe1);
            dataFrame.concat_line(dataframe2);
        }
        return std::move(dataFrame);
    }

    //read from csv file
    void read_csv(const std::string & filename, const char & delimiter) {
        bool convert = false;
        std::ifstream Reader(filename.data());
        if(!Reader){
            throw (std::invalid_argument("filename is invalid!"));
        }

        std::string strLine;
        StringVector vecValue;
        if(getline(Reader, strLine)){
            vecValue.clear();
            if(splite_line(strLine, vecValue ,delimiter)) {
                column_paste(vecValue);
            }
        }

        while (getline(Reader, strLine)){
            vecValue.clear();
            if(splite_line(strLine, vecValue ,delimiter)) {
                append_from_str(vecValue);
            }
        }
        Reader.close();
    }

    //write into csv file
    void to_csv(const std::string & filename, const char & delimiter) const {
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
    friend std::ostream &operator<<(std::ostream &cout, DataFrame &dataFrame) {
        for (int j = 0; j < dataFrame.width; ++j) {
            cout << dataFrame.column[j] << "\t";
        }
        cout << '\n';
        for (int i = 0; i < dataFrame.length; ++i) {
            for (int j = 0; j < dataFrame.width; ++j) {
                cout << (*dataFrame.matrix[j])[i] << "\t";
            }
            cout << '\n';
        }
        return cout;
    }
private:
    bool splite_line(const std::string & strLine, StringVector & stringVector, const char & delimiter) {
        unsigned long long nBegin = 0;
        unsigned long long nEnd = 0;
        unsigned int iter = 0;
        bool flag = false;
        std::string strtemp;
        while ((nEnd = strLine.find_first_of(delimiter, nBegin)) != std::string::npos)
        {
            strtemp = strLine.substr(nBegin, nEnd - nBegin);
            stringVector.emplace_back(strtemp);
            nBegin = nEnd + 1;
        }
        if ((nBegin = strLine.find_last_of(delimiter, strLine.length() - 1)) != std::string::npos)
        {
            strtemp = strLine.substr(nBegin + 1, strLine.length() - nBegin -1);
            stringVector.emplace_back(strtemp);
            flag = true;
        }
        return flag;
    }

    bool append_from_str(StringVector array){
        if(array.size() == column.size()){
            length ++;
            std::stringstream stream;
            T item;
            for (unsigned int i = 0; i < array.size(); ++i) {
                stream.clear();
                stream << array[i];
                stream >> item;
                matrix[i]->emplace_back(item);
            }
            return true;
        }else return false;
    }

    Column column;
    Matrix matrix;
    long long int width;
    long long int length;
};

#endif // DATAFRAME_H
