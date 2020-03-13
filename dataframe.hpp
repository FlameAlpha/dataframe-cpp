/**
* @file     DataFrame.h
* @class    DataFrame
* @brief    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @details
* @author   Flame
* @date     03.13.2019
*/

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
    typedef std::vector<T> Array;
    typedef std::vector<Array> Matrix;
    typedef std::vector<std::string> Column;
    typedef std::vector<std::string> StringVector;
public:
    DataFrame(){
        width = 0;
        length = 0;
    }

    bool column_paste(const Column & _column){
        if(!_column.empty()) {
            width = _column.size();
            column.clear();
            for(auto item : _column){
                column.emplace_back(item);
                matrix.emplace_back(Array{});
            }
            return true;
        } else return false;
    }

    const Array & operator [](const std::string& col){
        for(int i = 0;i<column.size();i++){
            if(col==column[i]){
                return matrix[i];
            }
        }
        throw (std::out_of_range("the index \'" + col + "\' is out of range!"));
    }

    const Array & operator [](int index){
        if(index < matrix.size())
            return matrix[index];
        std::stringstream ssTemp;
        ssTemp << index;
        throw (std::out_of_range("the index \'" + ssTemp.str() + "\' is out of range!"));
    }

    bool append(Array array){
        if(array.size() == column.size()){
            length ++;
            for (int i = 0; i < array.size(); ++i) {
                matrix[i].emplace_back(array[i]);
            }
            return true;
        }else return false;
    }

    const long long int & column_num(){
        return width;
    }

    const long long int & row_num(){
        return length;
    }

    bool concat(DataFrame & dataframe){
        if(dataframe.column_num()==column_num()){
            length += dataframe.row_num();
            for (int i = 0; i < column_num(); ++i) {
                matrix[i].insert(matrix[i].end(),dataframe[i].begin(),dataframe[i].end());
            }
            return true;
        }else return false;
    }

    void read_csv(const std::string & filename, const char & delimiter)
    {
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

        while (getline(Reader, strLine))
        {
            vecValue.clear();
            if(splite_line(strLine, vecValue ,delimiter)) {
                append_from_str(vecValue);
            }
        }
        Reader.close();
    }

    bool to_csv(const std::string & filename, const char & delimiter) {
        std::ofstream cout = std::ofstream(filename.data(), std::ios::out | std::ios::trunc);
        for (auto item = column.begin(); item < column.end() - 1; ++item) {
            cout << *item << delimiter;
        }
        cout << column.back() << '\n';
        for (int i = 0; i < row_num(); ++i) {
            for (auto array = matrix.begin(); array < matrix.end() - 1; ++array) {
                cout << (*array)[i] << delimiter;
            }
            cout << matrix.back()[i] << '\n';
        }
        cout.close();
        return true;
    }

    friend std::ostream &operator<<(std::ostream &cout, DataFrame &dataFrame) {
        for(auto item : dataFrame.column){
            cout << item << "\t";
        }
        cout << '\n';
        for (int i = 0; i < dataFrame.row_num(); ++i) {
            for(auto array : dataFrame.matrix){
                cout << array[i] << "\t";
            }
            cout << '\n';
        }
        return cout;
    }
private:
    bool splite_line(const std::string & strLine, StringVector & stringVector, const char & delimiter)
    {
        unsigned long long nBegin = 0;
        unsigned long long nEnd = 0;
        unsigned int iter = 0;
        bool flag = false;
        while ((nEnd = strLine.find_first_of(delimiter, nBegin)) != std::string::npos)
        {
            std::string strtemp = strLine.substr(nBegin, nEnd - nBegin);
            stringVector.push_back(strtemp);
            nBegin = nEnd + 1;
        }
        if ((nBegin = strLine.find_last_of(delimiter, strLine.length() - 1)) != std::string::npos)
        {
            std::string strtemp = strLine.substr(nBegin + 1, strLine.length() - nBegin -1);
            stringVector.push_back(strtemp);
            flag = true;
        }
        return flag;
    }

    bool append_from_str(StringVector array){
        if(array.size() == column.size()){
            length ++;
            std::stringstream stream;
            T item;
            for (int i = 0; i < array.size(); ++i) {
                stream.clear();
                stream << array[i];
                stream >> item;
                matrix[i].emplace_back(item);
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
